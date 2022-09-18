#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "math.h"

class TreeView
{
    Q_OBJECT
public:
    TreeView();
};




    QGraphicsScene scene;   // 定义一个场景，设置背景色为红色
    scene.setBackgroundBrush(Qt::red);

    QPen pen;   // 定义一个画笔，设置画笔颜色和宽度
    pen.setColor(QColor(0, 160, 230));
    pen.setWidth(10);

    QGraphicsRectItem *m_rectItem = new QGraphicsRectItem();   // 定义一个矩形图元
    m_rectItem->setRect(0, 0, 80, 80);
    m_rectItem->setPen(pen);
    m_rectItem->setBrush(QBrush(QColor(255, 0, 255)));
    m_rectItem->setFlag(QGraphicsItem::ItemIsMovable);

    QGraphicsLineItem *m_lineItem = new QGraphicsLineItem();    // 定义一个直线图元
    m_lineItem->setLine(QLineF(0, 0, 100, 100));
    m_lineItem->setPen(pen);
    m_lineItem->setFlag(QGraphicsItem::ItemIsMovable);

    QGraphicsPathItem *m_pathItem = new QGraphicsPathItem();    // 定义一个路径图元
    QPainterPath path;
    path.moveTo(90, 50);
    for (int i = 1; i < 5; ++i) {
        path.lineTo(50 + 40 * cos(0.8 * i * M_PI), 50 + 40 * sin(0.8 * i * M_PI));
    }
    path.closeSubpath();
    m_pathItem->setPath(path);
    m_pathItem->setPen(pen);
    m_pathItem->setFlag(QGraphicsItem::ItemIsMovable);

    QGraphicsPolygonItem *m_polygonItem = new QGraphicsPolygonItem();   // 定义一个多边形图元
    QPolygonF polygon;
    polygon << QPointF(-100.0, -150.0) << QPointF(-120.0, 150.0)
            << QPointF(320.0, 160.0) << QPointF(220.0, -140.0);
    m_polygonItem->setPolygon(polygon);
    m_polygonItem->setPen(pen);
    m_polygonItem->setFlag(QGraphicsItem::ItemIsMovable);

    scene.addItem(m_rectItem);      // 把矩形图元添加到场景
    scene.addItem(m_lineItem);      // 把直线图元添加到场景
    scene.addItem(m_pathItem);      // 把路径图元添加到场景
    scene.addItem(m_polygonItem);   // 把多边形图元添加到场景

    QGraphicsView view(&scene); // 定义一个视图，并把场景添加到视图
    view.resize(1024, 768);
    view.show();

    return a.exec();
}




#endif // TREEVIEW_H
