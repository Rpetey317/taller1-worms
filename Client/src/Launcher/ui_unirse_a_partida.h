/********************************************************************************
** JoinGame generated from reading UI file 'unirse_a_partida.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNIRSE_A_PARTIDA_H
#define UI_UNIRSE_A_PARTIDA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JoinGame
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *gameName;
    QPushButton *acceptButton;

    void setupUi(QWidget *JoinGame)
    {
        if (JoinGame->objectName().isEmpty())
            JoinGame->setObjectName(QString::fromUtf8("JoinGame"));
        JoinGame->resize(252, 224);
        verticalLayout = new QVBoxLayout(JoinGame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(JoinGame);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        gameName = new QLineEdit(JoinGame);
        gameName->setObjectName(QString::fromUtf8("gameName"));

        horizontalLayout->addWidget(gameName);


        verticalLayout->addLayout(horizontalLayout);

        acceptButton = new QPushButton(JoinGame);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));

        verticalLayout->addWidget(acceptButton);


        retranslateUi(JoinGame);

        QMetaObject::connectSlotsByName(JoinGame);
    } // setupUi

    void retranslateUi(QWidget *JoinGame)
    {
        JoinGame->setWindowTitle(QCoreApplication::translate("JoinGame", "JoinGame", nullptr));
        label->setText(QCoreApplication::translate("JoinGame", "Name of Game", nullptr));
        acceptButton->setText(QCoreApplication::translate("JoinGame", "Accept", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JoinGame: public Ui_JoinGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNIRSE_A_PARTIDA_H
