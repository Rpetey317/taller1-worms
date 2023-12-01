/********************************************************************************
** StartGame generated from reading UI file 'start_game.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_GAME_H
#define UI_START_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartGame
{
public:
    QLabel *label;
    QPushButton *startGameButton;

    void setupUi(QWidget *StartGame)
    {
        if (StartGame->objectName().isEmpty())
            StartGame->setObjectName(QString::fromUtf8("StartGame"));
        StartGame->resize(262, 213);
        label = new QLabel(StartGame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 60, 251, 17));
        startGameButton = new QPushButton(StartGame);
        startGameButton->setObjectName(QString::fromUtf8("startGameButton"));
        startGameButton->setGeometry(QRect(60, 130, 141, 41));

        retranslateUi(StartGame);

        QMetaObject::connectSlotsByName(StartGame);
    } // setupUi

    void retranslateUi(QWidget *StartGame)
    {
        StartGame->setWindowTitle(QCoreApplication::translate("StartGame", "StartGame", nullptr));
        label->setText(QCoreApplication::translate("StartGame", "To start the game click the button", nullptr));
        startGameButton->setText(QCoreApplication::translate("StartGame", "Start Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartGame: public Ui_StartGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_GAME_H
