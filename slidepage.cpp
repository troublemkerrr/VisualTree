#include "slidepage.h"

SlidePage::SlidePage(int radius, QString name, QWidget *parent):
    QWidget(parent),
    cornerRadius(radius),
    pageName(name)
{
    resize(preferWidth,parent->height());
    move(-preferWidth,0);

    nameLabel = new QLabel(pageName, this);
    textFont.setStyleStrategy(QFont::PreferAntialias);
    nameLabel->setFont(textFont);
    nameLabel->move(180,85);

    leftArrow = new mybutton(":/new/prefix1/img/leftArrow.png");
    leftArrow->setParent(this);
    leftArrow->move(100,100);

    propertyAnimation = new QPropertyAnimation(this,"geometry");
    propertyAnimation->setEasingCurve(QEasingCurve::InOutQuint);
    propertyAnimation->setDuration(1000);
}

void SlidePage::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen1(QColor(100,100,100,50));
    pen1.setWidth(2);
    painter.setPen(pen1);

    QBrush brush(QColor(255,255,255));
    painter.setBrush(brush);

    /* set the rounded border */
    QRect rect=this->rect();
    rect.setWidth((rect.width()-1));
    rect.setHeight(rect.height()-1);
    painter.drawRoundedRect(rect,60,60);

    QPen pen2(QColor(58,143,192,60));
    pen2.setWidth(8);
    painter.setPen(pen2);
    painter.drawLine(QPoint(575,200),QPoint(575,1150));//画线
}


void SlidePage::slideIn(){
    propertyAnimation->setStartValue(QRect(-this->rect().width(),0,this->width(),this->height()));
    propertyAnimation->setEndValue(QRect(this->rect().width()-this->width(),0,this->width(),this->height()));
    propertyAnimation->start();
}

void SlidePage::slideOut(){
    propertyAnimation->setStartValue(QRect(this->rect().width()-this->width(),0,this->width(),this->height()));
    propertyAnimation->setEndValue(QRect(-this->rect().width(),0,this->width(),this->height()));
    propertyAnimation->start();
}
