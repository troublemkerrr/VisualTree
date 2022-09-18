#include "shadow.h"

Shadow::Shadow(QWidget *parent) : QWidget(parent)
{
//    bg = new QWidget(this);
//    bg->resize(parent->size());
//    bg->setStyleSheet("background-color:#5a000000");
//    bg->setAttribute(Qt::WA_TransparentForMouseEvents);
//    bg->show();
    this->resize(parent->size());
    this->setStyleSheet("background-color:#5a000000");
    this->setAttribute(Qt::WA_TransparentForMouseEvents);
}
