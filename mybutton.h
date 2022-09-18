#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QPixmap>

class mybutton: public QPushButton
{
    Q_OBJECT

public:
    mybutton(QString imgSrc);
};

#endif // MYBUTTON_H
