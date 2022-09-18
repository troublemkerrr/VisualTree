#include "sonwindow.h"

SonWindow::SonWindow()
{
    this->setFixedSize(1200,900);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    this->setMouseTracking(true);
    this->setCursor(Qt::CrossCursor);

    gv=new MyGraphicsView();
    gv->setParent(this);
    gv->show();
}

void SonWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(QColor(180,180,180));
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

void SonWindow::createNew()
{
    gv->init();
}

void SonWindow::build()
{
    gv->buildTree();
}

void SonWindow::build2()
{
    gv->buildTree2();
}

void SonWindow::pre()
{
    gv->pre(gv->root);
}

void SonWindow::in()
{
    gv->in(gv->root);
}

void SonWindow::pos()
{
    gv->pos(gv->root);
}

void SonWindow::morris()
{
    gv->morris(gv->root);
}

