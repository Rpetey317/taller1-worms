/********************************************************************************
** Form generated from reading UI file 'crear_partida_nueva.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREAR_PARTIDA_NUEVA_H
#define UI_CREAR_PARTIDA_NUEVA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateGame
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *gameName;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *mapCombo;
    QPushButton *acceptButton;

    void setupUi(QWidget *CreateGame)
    {
        if (CreateGame->objectName().isEmpty())
            CreateGame->setObjectName(QString::fromUtf8("CreateGame"));
        CreateGame->resize(400, 300);
        verticalLayoutWidget = new QWidget(CreateGame);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(60, 10, 261, 281));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        gameName = new QLineEdit(verticalLayoutWidget);
        gameName->setObjectName(QString::fromUtf8("gameName"));

        horizontalLayout->addWidget(gameName);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        mapCombo = new QComboBox(verticalLayoutWidget);
        mapCombo->setObjectName(QString::fromUtf8("mapCombo"));

        horizontalLayout_3->addWidget(mapCombo);


        verticalLayout->addLayout(horizontalLayout_3);

        acceptButton = new QPushButton(verticalLayoutWidget);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));

        verticalLayout->addWidget(acceptButton);


        retranslateUi(CreateGame);

        QMetaObject::connectSlotsByName(CreateGame);
    } // setupUi

    void retranslateUi(QWidget *CreateGame)
    {
        CreateGame->setWindowTitle(QCoreApplication::translate("CreateGame", "Form", nullptr));
        label->setText(QCoreApplication::translate("CreateGame", "Name", nullptr));
        label_3->setText(QCoreApplication::translate("CreateGame", "Map", nullptr));
        acceptButton->setText(QCoreApplication::translate("CreateGame", "Accept", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateGame: public Ui_CreateGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREAR_PARTIDA_NUEVA_H
