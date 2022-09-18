#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QRect>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include "mybutton.h"
#include "sonwindow.h"
#include "slidepage.h"
#include "mydialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    void paintEvent(QPaintEvent *);

    /* For dragging */
    QPoint m_lastPos;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    int cornerRadius=60;

    SonWindow * son;

    mybutton * closeBtn;
    mybutton * runBtn;
    mybutton * addBtn;
    mybutton * moreBtn;
    mybutton * useBtn;

    /* For slidepage */
    bool slideFlag =true;
    bool slideFlag2 =true;
    int onShown = 0;
    SlidePage *codePage = nullptr;
    SlidePage *infoPage = nullptr;

    int choice=0;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
