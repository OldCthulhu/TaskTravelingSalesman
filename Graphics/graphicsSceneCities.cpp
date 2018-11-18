#include "graphicsSceneCities.h"
#include <QDebug>

//*************
//GraphicsCity*
//*************

GraphicsCity::GraphicsCity(const shared_ptr<City> city, QGraphicsItem* parent){
    _city = city;

    int x = _city->coordinates.x - SIZE_ELLIPSE / 2;
    int y = _city->coordinates.y - SIZE_ELLIPSE / 2;
    _ellipse = std::make_shared<QGraphicsEllipseItem>(x, y, SIZE_ELLIPSE, SIZE_ELLIPSE, this);

    _text = std::make_shared<QGraphicsTextItem>(city->name.c_str(), this);
    _coordinates = std::make_shared<QGraphicsTextItem>("(;)", this);
    _coordinates->setPlainText(QString("(%1; %2)").arg(QString::number(_city->coordinates.x)).arg(QString::number(_city->coordinates.y)));

    QFont fontNameCity = _text->font();
    QFontMetrics fmNameCity(fontNameCity);

    _text->setX(x - ((fmNameCity.width(city->name.c_str())) / 2 - 5));
    _text->setY(y + SIZE_ELLIPSE / 2 + fmNameCity.height());

    QFont fontCoordinatesCity = _text->font();
    QFontMetrics fmCoordiantesCity(fontCoordinatesCity);

    _coordinates->setX(x - ((fmCoordiantesCity.width("(xxx; xxx)")) / 2) + 5);
    _coordinates->setY(y - SIZE_ELLIPSE / 2 - fmCoordiantesCity.height());


    setFlag(QGraphicsItem::ItemIsMovable);

    setAcceptDrops(true);
    setAcceptHoverEvents(true);
}

void GraphicsCity::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    if(event->button() == Qt::RightButton){
        return;
    }

    int x = event->scenePos().x();
    int y = event->scenePos().y();

    _city->coordinates.x = x;
    _city->coordinates.y = y;

    QString coordinates = QString("(%1; %2)").arg(QString::number(x)).arg(QString::number(y));
    _coordinates->setPlainText(coordinates);

    QFont fontCoordinatesCity = _text->font();
    QFontMetrics fmCoordiantesCity(fontCoordinatesCity);

    QGraphicsObject::mouseMoveEvent(event);
}



QRectF GraphicsCity::boundingRect() const{
    return _ellipse->boundingRect();
}

void GraphicsCity::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){

    QPen pen(Qt::red);
    QBrush brush(Qt::red);

    if(_city->isBegin){
        pen.setColor(Qt::blue);
        brush.setColor(Qt::blue);

        /*
        auto flag = std::make_shared<QGraphicsTextItem>("Н-К", this);
        QFont fontNameCity = _text->font();
        QFontMetrics fmNameCity(fontNameCity);

        flag->setY(_ellipse->y());
        flag->setX(_ellipse->x() + SIZE_ELLIPSE);*/
    }else{
        pen.setColor(Qt::red);
        brush.setColor(Qt::red);
    }

    _ellipse->setBrush(brush);
    _ellipse->setPen(pen);

    _ellipse->paint(painter, option, widget);
}


/*
 *void GraphicsCity::mousePressEvent(QGraphicsSceneMouseEvent * event){
 *    if(event->button() == Qt::RightButton){
 *        QBrush brush(Qt::green);
 *        _ellipse->setBrush(brush);
 *    }
 *}
 */

//********************
//GraphicsSceneCities*
//********************

GraphicsSceneCities::GraphicsSceneCities(QObject* parent) : QGraphicsScene(parent){

}


void GraphicsSceneCities::Clear() {
    _lines.clear();
    clear();
}

void GraphicsSceneCities::ClearLines(){
    for(auto& line : _lines){
        removeItem(line.get());
        line.reset();
    }

    _lines.clear();
}

void GraphicsSceneCities::SetWays(const shared_ptr<Map> map, const int numberBeginCity, vector<int> numberCities){

    for(auto& line : _lines){
        removeItem(line.get());
        line.reset();
    }

    _lines.clear();

    QPen greenPen;
    QColor color(Qt::green);

    City beginCity = map->GetCity(numberBeginCity);
    City prevCity = beginCity;
    int sizeWays = numberCities.size();
    for(int i = 0; i < sizeWays; ++i){
        City currCity = map->GetCity(numberCities[i]);


        QPoint p1, p2;
        p1.setX(prevCity.coordinates.x);
        p1.setY(prevCity.coordinates.y);
        p2.setX(currCity.coordinates.x);
        p2.setY(currCity.coordinates.y);

        auto line = shared_ptr<QGraphicsLineItem>(new QGraphicsLineItem(QLine(p1, p2)), [](QGraphicsLineItem*){});
        greenPen.setWidth(3);

        if(i == 0){
            greenPen.setColor(Qt::red);
        }else{
            greenPen.setColor(Qt::green);
        }

        line->setPen(greenPen);
        _lines.push_back(line);

        addItem(line.get());

        prevCity = currCity;
    }

    QPoint p1, p2;
    p1.setX(prevCity.coordinates.x);
    p1.setY(prevCity.coordinates.y);
    p2.setX(beginCity.coordinates.x);
    p2.setY(beginCity.coordinates.y);

    auto line = shared_ptr<QGraphicsLineItem>(new QGraphicsLineItem(QLine(p1, p2)), [](QGraphicsLineItem*){});

    greenPen.setColor(Qt::blue);
    line->setPen(greenPen);
    _lines.push_back(line);

    addItem(line.get());

}


/*
 *
 *
 *void GraphicsSceneCities::setFocusItem(QGraphicsItem *item, Qt::FocusReason focusReason){
 *    //QBrush brush(Qt::green);
 *    //item->setBrush(brush);
 *}
 *
 */
/*
 *void GraphicsSceneCities::mousePressEvent(QGraphicsSceneMouseEvent * event){
 *
 *}
 */
