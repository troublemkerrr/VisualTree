#include "mybutton.h"

mybutton::mybutton(QString imgSrc)
{
    QPixmap pic1(imgSrc);

    this->setFixedSize(50,50);
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pic1);
    this->setIconSize(QSize(50,50));
}
