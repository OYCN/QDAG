#include "node.h"

#include <QPainter>

Node::Node(QGraphicsItem *parent) : QGraphicsItem(parent) {
    this->setFlag(QGraphicsItem::ItemIsMovable, false);

    mBackgroundColor = Qt::white;
    mBorderColor = Qt::black;
}

Node::~Node() {}

void Node::addEdge(Edge *edge) { mEdges.push_back(edge); }

void Node::removeEdge(Edge *edge) {
    for (int i = 0; i < mEdges.size(); ++i) {
        if (mEdges.at(i) == edge) {
            mEdges.removeAt(i);
        }
    }
}

QRectF Node::boundingRect() const { return QRectF(0, 0, 40, 40); }

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF bound = boundingRect();

    QBrush brush(mBackgroundColor);

    QBrush contourBrush(mBorderColor);
    QPen pen(contourBrush, 3);

    painter->setBrush(brush);
    painter->setPen(pen);

    QFont font = painter->font();
    font.setPixelSize(20);
    painter->setFont(font);

    painter->drawEllipse(5, 5, bound.width() - 10, bound.height() - 10);
    for (int i = 0; i < mMetas.size(); i++) {
        NodeMeta &meta = mMetas[i];
        painter->drawText(meta.rect.x(), meta.rect.y(), meta.rect.width(), meta.rect.height(), meta.flag, meta.data);
    }
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event) { QGraphicsItem::mouseMoveEvent(event); }