/********************************************************************************
** Form generated from reading UI file 'super_duper_tuki.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUPER_DUPER_TUKI_H
#define UI_SUPER_DUPER_TUKI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Greeter
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *createButton;
    QPushButton *joinButton;
    QPushButton *createMapButton;

    void setupUi(QWidget *Greeter)
    {
        if (Greeter->objectName().isEmpty())
            Greeter->setObjectName(QString::fromUtf8("Greeter"));
        Greeter->resize(522, 377);
        Greeter->setStyleSheet(QString::fromUtf8("QLabel{\n"
"color: white;\n"
"max-height: 10px;\n"
"}\n"
"QPushButton {\n"
"selection-background-color: rgb(255, 41, 41);\n"
"background: rgb(255, 159, 49);\n"
"}\n"
"QPushButton:hover{\n"
"\n"
"background:rgb(255, 0, 0);\n"
"}\n"
"QPushButton:pressed {\n"
"background:rgb(255, 102, 0);\n"
"}"));
        verticalLayout = new QVBoxLayout(Greeter);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(Greeter);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label);

        label_2 = new QLabel(Greeter);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);


        horizontalLayout_3->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 0);
        createButton = new QPushButton(Greeter);
        createButton->setObjectName(QString::fromUtf8("createButton"));

        horizontalLayout->addWidget(createButton);

        joinButton = new QPushButton(Greeter);
        joinButton->setObjectName(QString::fromUtf8("joinButton"));

        horizontalLayout->addWidget(joinButton);

        createMapButton = new QPushButton(Greeter);
        createMapButton->setObjectName(QString::fromUtf8("createMapButton"));

        horizontalLayout->addWidget(createMapButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Greeter);

        QMetaObject::connectSlotsByName(Greeter);
    } // setupUi

    void retranslateUi(QWidget *Greeter)
    {
        Greeter->setWindowTitle(QCoreApplication::translate("Greeter", "Form", nullptr));
        label->setText(QCoreApplication::translate("Greeter", "Ready to play Worms?", nullptr));
        label_2->setText(QCoreApplication::translate("Greeter", "Choose an option:", nullptr));
        createButton->setText(QCoreApplication::translate("Greeter", "Create Match", nullptr));
        joinButton->setText(QCoreApplication::translate("Greeter", "Join Match", nullptr));
        createMapButton->setText(QCoreApplication::translate("Greeter", "Create Map", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Greeter: public Ui_Greeter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUPER_DUPER_TUKI_H
