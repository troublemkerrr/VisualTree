#include "hidebutton.h"

hidebutton::hidebutton(QString imgSrc)
{
    QPixmap pic2(imgSrc);

    this->setFixedSize(50,50);
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pic2);
    this->setIconSize(QSize(50,50));
}
