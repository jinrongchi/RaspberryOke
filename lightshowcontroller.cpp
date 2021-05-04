/**
* LightShowController.cpp
*
* @brief This class controlls the blinking of the LED lights on the Raspberry Pi's breadboard.
* 
* The class uses the GPIO pins to randomly blink the LED lights to perform a light show for the users of RasberryOke.
* 
*/

#include "lightshowcontroller.h"

using namespace std;

/**
* @brief The class constructor
* 
* Sets up the GPIO pins for blinking the lights
* 
* @param the tempo of the song
*/
LightShowController::LightShowController(int t) {

    // set the tempo
    tempo = t;


    wiringPiSetupGpio();

    //light1 = 17;		// Light one is connected to pin 17 on the Pi
    //light2 = 18;
    //light3 = 22;

    pinMode(LIGHT_ONE, OUTPUT);
    pinMode(LIGHT_TWO, OUTPUT);
    pinMode(LIGHT_THREE, OUTPUT);

    // start the loop
    this->blinking = true;

}

/**
* @brief The class destructor
*/
LightShowController::~LightShowController() {

    // Destruct

}


/**
* @brief Blink the light connected to the specified pin.
* 
* @param the GPIO pin number of the light
*/
void LightShowController::blinkLight(int ledPin) {

    digitalWrite(ledPin, HIGH);
    delay(BLINK_DUR);
    digitalWrite(ledPin, LOW);
    //delay(time);

}

/**
* @brief Return a random number between 0 and 2
* 
* @return a random number between 0 and 2
*/
int LightShowController::randomNumber() {

    random_device randdev;
    mt19937 gen(randdev());
    uniform_int_distribution<int> dist(0,2);

    return dist(gen);

}

/**
* Activate the blinking by calling blinkController
*/
void LightShowController::start() {

    this->blinking = true;
    blinkController();
    //cout << "Control returned to start()" << endl;
//	thread thread_obj(&LightShowController::blinkController, this);
//	thread_obj.join();
}

/**
* @brief Blink light and sleep between beats of the song
* 
* One of the lights will be blinked, determined using a random number
* 
*/
void LightShowController::blinkController() {

//	auto func = async(launch::async, [this] {

//		while(blinking) {

            // Random number between 0 and 2

            int num = randomNumber();

            if (num == 0) {

                // blink one
                blinkLight(LIGHT_ONE);

            } else if (num == 1) {

                // blink two
                blinkLight(LIGHT_TWO);

            } else {

                // blink
                blinkLight(LIGHT_THREE);


            }

//			//sleep(60/this->tempo); // Sleep for time between beats of the song
           // this_thread::sleep_for(chrono::milliseconds((60/tempo) * 1000));
//		}

//	});

    //cout << "Control Returned" << endl;

}


/**
*  @brief Stop the blinking and turn off the lights
*/
void LightShowController::stop() {

    this->blinking = false;
    digitalWrite(LIGHT_ONE, LOW);
    digitalWrite(LIGHT_TWO, LOW);
    digitalWrite(LIGHT_THREE, LOW);


}
