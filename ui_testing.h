/********************************************************************************
** Form generated from reading UI file 'testing.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTING_H
#define UI_TESTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Testing
{
public:
    QTableView *tableView;

    void setupUi(QWidget *Testing)
    {
        if (Testing->objectName().isEmpty())
            Testing->setObjectName(QStringLiteral("Testing"));
        Testing->resize(614, 373);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Testing->sizePolicy().hasHeightForWidth());
        Testing->setSizePolicy(sizePolicy);
        Testing->setLayoutDirection(Qt::LeftToRight);
        tableView = new QTableView(Testing);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 40, 591, 291));
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        retranslateUi(Testing);

        QMetaObject::connectSlotsByName(Testing);
    } // setupUi

    void retranslateUi(QWidget *Testing)
    {
        Testing->setWindowTitle(QApplication::translate("Testing", "Testing", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Testing: public Ui_Testing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTING_H
