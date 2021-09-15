#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include "../common/macro.h"
#include "graphview.h"

class Edge;
struct NodeMeta;

class Node : public QGraphicsItem {
 public:
    Node(QGraphicsItem* parent = nullptr);
    ~Node();

 public:
    void addEdge(Edge* edge);
    void removeEdge(Edge* edge);
    void setMetas(NodeMeta& metas);
    NodeMeta getMetas();
    void updateRect();
    QPointF centerPos();
    QPointF crossPos(qreal angle, qreal add = 0);

 public:
    DEF_VAL_ALL(QColor, BorderColor);
    DEF_VAL_ALL(QColor, BackgroundColor);
    DEF_VAL_ALL(qreal, MinWidth);
    DEF_VAL_ALL(qreal, MinHeight);

 public:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

 private:
    QVector<Edge*> mEdges;
    NodeMeta mMetas;
    qreal mRectX;
    qreal mRectY;
    qreal mRectW;
    qreal mRectH;
};
#endif  // NODE_H
