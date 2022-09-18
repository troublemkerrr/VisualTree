#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include "mybutton.h"

class MyDialog : public QDialog
{
    Q_OBJECT

private:
    void paintEvent(QPaintEvent *);

    /* For dragging */
    bool bPressFlag = false;
    QPoint beginDrag;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public:
    MyDialog(int w,int h);
};

#endif // MYDIALOG_H
