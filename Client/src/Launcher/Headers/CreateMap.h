#ifndef CREATEMAP_H
#define CREATEMAP_H

#include <QDialog>
#include <QWidget>

#include "../ui_create_map.h"

class CreateMap: public QDialog {
public:
    explicit CreateMap();
    // QString getEnteredText() const;

private slots:
    void CreateNewMap();

private:
    void connectEvents();
};

#endif  // CREATEMAPA_H
