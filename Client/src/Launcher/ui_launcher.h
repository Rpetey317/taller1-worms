/********************************************************************************
** Greeter generated from reading UI file 'launcher.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAUNCHER_H
#define UI_LAUNCHER_H

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
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *createButton;
    QPushButton *joinButton;

    void setupUi(QWidget *Greeter)
    {
        if (Greeter->objectName().isEmpty())
            Greeter->setObjectName(QString::fromUtf8("Greeter"));
        Greeter->resize(441, 362);
        verticalLayout_2 = new QVBoxLayout(Greeter);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Greeter);
        label->setObjectName(QString::fromUtf8("label"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        QBrush brush2(QColor(255, 255, 255, 128));
        brush2.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        QBrush brush3(QColor(190, 190, 190, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        QBrush brush4(QColor(0, 0, 0, 128));
        brush4.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush4);
#endif
        label->setPalette(palette);
        QFont font;
        font.setPointSize(25);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(Greeter);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        label_2->setPalette(palette1);

        verticalLayout->addWidget(label_2);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        createButton = new QPushButton(Greeter);
        createButton->setObjectName(QString::fromUtf8("createButton"));
        QPalette palette2;
        QBrush brush5(QColor(255, 163, 72, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush5);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush5);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush5);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush5);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush5);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush5);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush5);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush5);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush5);
        createButton->setPalette(palette2);

        horizontalLayout->addWidget(createButton);

        joinButton = new QPushButton(Greeter);
        joinButton->setObjectName(QString::fromUtf8("joinButton"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Button, brush5);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush5);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush5);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush5);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush5);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush5);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush5);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush5);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush5);
        joinButton->setPalette(palette3);

        horizontalLayout->addWidget(joinButton);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(Greeter);

        QMetaObject::connectSlotsByName(Greeter);
    } // setupUi

    void retranslateUi(QWidget *Greeter)
    {
        Greeter->setWindowTitle(QCoreApplication::translate("Greeter", "Greeter", nullptr));
        label->setText(QCoreApplication::translate("Greeter", "Ready to play WORMS?", nullptr));
        label_2->setText(QCoreApplication::translate("Greeter", "Choose an option:", nullptr));
        createButton->setText(QCoreApplication::translate("Greeter", "Create Match", nullptr));
        joinButton->setText(QCoreApplication::translate("Greeter", "Join Match", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Greeter: public Ui_Greeter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAUNCHER_H
