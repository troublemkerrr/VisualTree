#ifndef HIDEBUTTON_H
#define HIDEBUTTON_H

#include <QPushButton>
#include <QString>
#include <QPixmap>

//实际上和clossbutton没有区别，可以不写
class hidebutton: public QPushButton
{
    Q_OBJECT
public:
    hidebutton(QString imgSrc);
};

#endif // HIDEBUTTON_H
