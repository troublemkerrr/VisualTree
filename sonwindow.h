#ifndef SONWINDOW_H
#define SONWINDOW_H

#include <QWidget>
#include <QRect>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include "graphview.h"

class SonWindow : public QWidget
{
    Q_OBJECT

private:
    void paintEvent(QPaintEvent *);

public:
    SonWindow();
    MyGraphicsView *gv;

public slots:
    void createNew();

    void build();
    void build2();

    void pre();
    void in();
    void pos();    
    void morris();
};


#endif // SONWINDOW_H
