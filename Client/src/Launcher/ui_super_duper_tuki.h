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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Greeter
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *changeName;
    QPushButton *selectNameButton;
    QPushButton *randomNameButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *playerName;
    QHBoxLayout *horizontalLayout;
    QPushButton *createButton;
    QPushButton *joinButton;

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
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(Greeter);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(label_2);

        changeName = new QLineEdit(Greeter);
        changeName->setObjectName(QString::fromUtf8("changeName"));

        horizontalLayout_2->addWidget(changeName);

        selectNameButton = new QPushButton(Greeter);
        selectNameButton->setObjectName(QString::fromUtf8("selectNameButton"));

        horizontalLayout_2->addWidget(selectNameButton);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(verticalLayout_2);

        randomNameButton = new QPushButton(Greeter);
        randomNameButton->setObjectName(QString::fromUtf8("randomNameButton"));

        verticalLayout->addWidget(randomNameButton);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        playerName = new QLabel(Greeter);
        playerName->setObjectName(QString::fromUtf8("playerName"));

        horizontalLayout_3->addWidget(playerName);


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


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Greeter);

        QMetaObject::connectSlotsByName(Greeter);
    } // setupUi

    void retranslateUi(QWidget *Greeter)
    {
        Greeter->setWindowTitle(QCoreApplication::translate("Greeter", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("Greeter", "Name:", nullptr));
        selectNameButton->setText(QCoreApplication::translate("Greeter", "Select", nullptr));
        randomNameButton->setText(QCoreApplication::translate("Greeter", "Random Name", nullptr));
        playerName->setText(QCoreApplication::translate("Greeter", "Your name...", nullptr));
        createButton->setText(QCoreApplication::translate("Greeter", "Create", nullptr));
        joinButton->setText(QCoreApplication::translate("Greeter", "Join", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Greeter: public Ui_Greeter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUPER_DUPER_TUKI_H
