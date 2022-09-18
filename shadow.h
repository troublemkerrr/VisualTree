#ifndef SHADOW_H
#define SHADOW_H

#include <QWidget>

class Shadow : public QWidget
{
    Q_OBJECT

public:
    QWidget *bg;
    Shadow(QWidget *parent = nullptr);
};

#endif // SHADOW_H




//private:
//    bool pressed = false;
//    bool enabled = true;
//    QWidget *bg;
//    void mousePressEvent(QMouseEvent *event){if(enabled)pressed = true;}
//    void mouseReleaseEvent(QMouseEvent *event){if(enabled && pressed)emit clicked();pressed = false;}
//    void resizeEvent(QResizeEvent *event){bg->resize(this->parentWidget()->size());}
//public:
//    SheildLayer(QWidget *parent = nullptr) : QWidget(parent){
//        bg = new QWidget(this);
//        bg->resize(parent->size());
//        bg->setStyleSheet("background-color:#5a000000");
//        bg->setAttribute(Qt::WA_TransparentForMouseEvents);
//        bg->show();
//    }
//    void setEnabled(bool e){enabled = e;}
//signals:
//    void clicked();
//};
