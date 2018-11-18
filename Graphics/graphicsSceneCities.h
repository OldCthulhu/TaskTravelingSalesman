#ifndef _GRAPHICS_SCENE_CITIES_H_
#define _GRAPHICS_SCENE_CITIES_H_

#include "includes.h"
#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QApplication>
#include <QWidget>
#include <QMimeData>
#include <QDrag>
#include <QFont>
#include <QPainter>
#include <QFontMetrics>
#include "Map/map.h"

const int SIZE_ELLIPSE = 20;

class GraphicsCity : public QGraphicsObject{
public:
    GraphicsCity(const shared_ptr<City> city, QGraphicsItem* parent = nullptr);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private:
    shared_ptr<QGraphicsEllipseItem> _ellipse;
    shared_ptr<QGraphicsTextItem> _text;
    shared_ptr<QGraphicsTextItem> _coordinates;
    shared_ptr<City> _city;
};

class GraphicsSceneCities : public QGraphicsScene{
    Q_OBJECT
public:
    GraphicsSceneCities(QObject* parent = nullptr);
    void Clear();
    void ClearLines();
    void SetWays(const shared_ptr<Map> map, const int numberBeginCity, vector<int> numberCities);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event) override{
        emit MoveCity();
        QGraphicsScene::mousePressEvent(event);
    }
private:
    list<shared_ptr<QGraphicsLineItem>> _lines;
signals:
    void MoveCity();
};

/*
 *
 *class GraphicsSceneCities : public QGraphicsScene{
 *public:
 *    GraphicsSceneCities(QObject* parent);
 *    virtual void setFocusItem(QGraphicsItem *item, Qt::FocusReason focusReason = Qt::OtherFocusReason) ;
 *    //virtual void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
 *};
 */

#endif
