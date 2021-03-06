#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

#include "../common/macro.h"
#include "graphview.h"

class Node;

class Edge : public QGraphicsItem {
 public:
    Edge(Node* nodeSrc, Node* nodeDst, QGraphicsItem* parent = nullptr);
    ~Edge();

 public:
   void updateRect();

 public:
    DEF_VAL_ALL(qreal, Pad);
    DEF_VAL_ALL(Node*, NodeSrc);
    DEF_VAL_ALL(Node*, NodeDst);
    DEF_VAL_ALL(QColor, Color);
    DEF_VAL_ALL_REF_CONST(EdgeMeta, Meta);

 public:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

 private:
    qreal mRectX;
    qreal mRectY;
    qreal mRectW;
    qreal mRectH;
};
#endif  // EDGE_H