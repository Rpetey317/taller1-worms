/********************************************************************************
** CreateMap generated from reading UI file 'create_map.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATE_MAP_H
#define UI_CREATE_MAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateMap {
public:
    QLabel* label;
    QPushButton* pushButton;

    void setupUi(QWidget* CreateMap) {
        if (CreateMap->objectName().isEmpty())
            CreateMap->setObjectName(QString::fromUtf8("CreateMap"));
        CreateMap->resize(338, 257);
        label = new QLabel(CreateMap);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 40, 341, 17));
        pushButton = new QPushButton(CreateMap);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(120, 160, 89, 25));

        retranslateUi(CreateMap);

        QMetaObject::connectSlotsByName(CreateMap);
    }  // setupUi

    void retranslateUi(QWidget* CreateMap) {
        CreateMap->setWindowTitle(QCoreApplication::translate("CreateMap", "CreateMap", nullptr));
        label->setText(QCoreApplication::translate(
                "CreateMap", "Aca deberia delegar a SDL para que cree el mapa", nullptr));
        pushButton->setText(QCoreApplication::translate("CreateMap", "Create", nullptr));
    }  // retranslateUi
};

namespace Ui {
class CreateMap: public Ui_CreateMap {};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_CREATE_MAP_H
