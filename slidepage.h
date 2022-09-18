#ifndef SLIDEPAGE_H
#define SLIDEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include "mybutton.h"

class SlidePage : public QWidget
{
    Q_OBJECT

private:
    int cornerRadius;
    const int preferWidth = 600;

    QString pageName;
    QLabel *nameLabel;
    QFont textFont = QFont("Corbel Light", 24,QFont::Bold);

    QPropertyAnimation * propertyAnimation = nullptr;

    void paintEvent(QPaintEvent *);

public:
    mybutton * leftArrow;
    explicit SlidePage(int radius, QString name, QWidget *parent = nullptr);

public slots:
    void slideIn();
    void slideOut();
};

#endif // SLIDEPAGE_H
