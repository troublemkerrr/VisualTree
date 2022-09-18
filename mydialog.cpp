#include "mydialog.h"

MyDialog::MyDialog(int w,int h)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(w,h);

    mybutton * closeBtn=new mybutton(":/new/prefix1/img/close.png");
    closeBtn->setParent(this);
    closeBtn->move(w-70,30);
    connect(closeBtn,&mybutton::clicked,this,&QDialog::close);
}

void MyDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(QColor(100,100,100,50));
    pen.setWidth(3);
    painter.setPen(pen);

    QBrush brush(QColor(255,255,255));
    painter.setBrush(brush);

    /* set the rounded border */
    QRect rect=this->rect();
    rect.setWidth((rect.width()-1));
    rect.setHeight(rect.height()-1);
    painter.drawRoundedRect(rect,30,30);
}

void MyDialog::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void MyDialog::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void MyDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(bPressFlag)
    {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}
