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

 public:
    DEF_VAL_ALL(QColor, BorderColor);
    DEF_VAL_ALL(QColor, BackgroundColor);
    DEF_VAL_ALL(qreal, MinWidth);
    DEF_VAL_ALL(qreal, MinHeight);
    DEF_VAL_ALL_REF_CONST(QVector<NodeMeta>, Metas);

 public:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

 private:
    QVector<Edge*> mEdges;
};
#endif  // NODE_H
