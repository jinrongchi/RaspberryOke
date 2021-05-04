#include "testing.h"
#include "ui_testing.h"
#include "media.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "song.h"
#include <QDir>

using namespace std;



// static size_t Testing::fDownload(void *buffer,size_t size, size_t nmemb, void *stream){
//     struct FtpFile *out = (struct FtpFile*)stream;
//     if(out && !out->stream) {
//         out->stream=fopen(out->filename, "wb");
//         if(!out->stream)
//             return -1;
//     }
//     return fwrite(buffer, size, nmemb, out->stream);

// }

Testing::Testing(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Testing)
    , model(new QStandardItemModel())
{
    ui->setupUi(this);
    // setting up the model
    model->setHorizontalHeaderItem(0, new QStandardItem(QObject:: tr("Song")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QObject:: tr("Artist")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QObject:: tr("Length")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QObject:: tr("  ")));

    // get the songs
    song_vec = this->getSong_Vec();
    for(int i = 0; i<song_vec.count();i++){
        model->setItem(i, 0, new QStandardItem(song_vec[i]->getSongTitle()));
        model->setItem(i, 1, new QStandardItem(song_vec[i]->getSongArtist()));
        model->setItem(i, 2, new QStandardItem(song_vec[i]->getSongTimeLength()));
        ui->tableView->setModel(model);
        playBtn = new QPushButton("Play");
        playBtn->setProperty("song_path", song_vec[i]->getSongFileLocation());
        playBtn->setProperty("lyrics_path", song_vec[i]->getLyricsFileLocation());
        connect(playBtn, SIGNAL(clicked()), this, SLOT(onPlayBtnClicked()));
        ui->tableView->setIndexWidget(model->index(model->rowCount()-1, 3), playBtn);

    }

    ui->tableView->setMinimumSize(700, 500);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,250);
    ui->tableView->setColumnWidth(2,100);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->horizontalHeader ()->setSectionResizeMode (QHeaderView::Stretch);

}

Testing::~Testing()
{
    delete ui;
}

void Testing:: onPlayBtnClicked(){
    QPushButton *button = static_cast<QPushButton*>(sender());
    QString song_path = button->property("song_path").toString();
    QString lyrics_path = button->property("lyrics_path").toString();
    emit hitPlayBtn(song_path, lyrics_path);
}

int Testing::downloadFile(std::string fileAddress, std::string outputAddress){

    CURL *curl;
    CURLcode res;
    std::string path = "cache/"+ outputAddress;
    const char* name = path.c_str();
    struct FtpFile ftpfile={
        name, 
        NULL
    }; /* name to store the file as if succesful */

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {

        // use the ftp address , username and password to create a port
        curl_easy_setopt(curl, CURLOPT_URL, fileAddress.c_str());

        // Define the place for the data to be written
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fDownload);
        // Set a pointer store the struct to pass to the file stream
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);


        // if the file is not downloaded successfully.
        // return the error code, close the local file stream and clean the curl.
        if(CURLE_OK != res) {
        fprintf(stderr, "curl alerted %d\n", res);
        }
    }

    if(ftpfile.stream){
        fclose(ftpfile.stream);
    }

    curl_global_cleanup();
    return 0;
}

QVector<Song*> Testing:: getSong_Vec(){
        QString currentPath = QDir::currentPath();///< the location of the running application
        std::string current_path = currentPath.toUtf8().constData();
        system(qPrintable("mkdir cache"));
        std::string cache ="/cache";
        std::string username = "zhenyan";
        std::string password = "0901";
        std::string ipAddress = "99.242.120.18";
        std::string fileAddress = "ftp://"+username+":"+password+"@"+ipAddress+"/Desktop/ftpStorage/xmlsample.xml";
        std::string outputAddress = "xmlsample.xml";
        downloadFile(fileAddress,outputAddress);

        int count;
        Song* newSong;
        QString temp;
        string outputXml = "/cache/xmlsample.xml";      ///< outputaddress for downloaded xml file
        string xmlAddress = current_path + outputXml;
        QVector<Song*> SongCollection(0);
        TiXmlDocument file(xmlAddress.c_str());


        if(!file.LoadFile()){           ///> Check if the file is xml file is exist
            qDebug("The data file cannot be read.");
            exit(1);
        }

        TiXmlHandle hDoc(&file);
        TiXmlElement* pElem;
        pElem = hDoc.FirstChildElement().Element();
        TiXmlHandle hRoot(pElem);
        TiXmlElement* songElem = hRoot.FirstChild("songs").FirstChild("song").Element();    ///<set pointer to the element of the file
        count = 0;

        for(songElem;songElem;songElem = songElem->NextSiblingElement()){
            TiXmlHandle song(songElem);
            TiXmlElement* name = song.FirstChild("name").Element();
            TiXmlElement* artist = song.FirstChild("artist").Element();
            TiXmlElement* genre = song.FirstChild("format").Element();
            TiXmlElement* locationOfSong = song.FirstChild("locationOfSong").Element();
            TiXmlElement* locationOfLyric = song.FirstChild("locationOfLyrics").Element();
            TiXmlElement* tempo = song.FirstChild("tempo").Element();
            TiXmlElement* length = song.FirstChild("length").Element();

            newSong = new Song();

            temp = name->GetText();
            newSong->setSongTitle(temp);

            temp = artist->GetText();
            newSong->setSongArtist(temp);

            temp = genre->GetText();
            newSong->setSongGenre(temp);

            temp = locationOfSong->GetText();
            QString outputName = newSong->getSongTitle();
            QString songFormat = newSong->getSongGenre();
            outputName = outputName + songFormat;
            downloadFile("ftp://" + username+":" + password + "@" + ipAddress+temp.toUtf8().constData(), outputName.toUtf8().constData());
            // locate the new local song file and store the address
            temp = currentPath + "/cache/"+ outputName;
            newSong->setSongFileLocation(temp);

            // Read the location of the Lyric file and download it from the server
            temp = locationOfLyric->GetText();
            outputName = newSong->getSongTitle();
            outputName = outputName + ".lrc";
            downloadFile("ftp://"+username+":"+password+"@"+ipAddress+temp.toUtf8().constData(),outputName.toUtf8().constData());

            ///locate the new local lyrics file and store the address
            QString newLrc = currentPath + "/cache/"+ outputName;
            newSong->setLyricsFileLocation(newLrc);    // std, qstring needed

            temp = length->GetText();
            newSong->setSongTimeLength(temp);
            newSong->setSongID(count);

            SongCollection.push_back(newSong);

            count++;
        }

    return SongCollection;
}
