#include "edge.h"
#include "node.h"

#include <QDebug>
#include <QPainter>

Edge::Edge(Node* nodeSrc, Node* nodeDst, QGraphicsItem* parent) : QGraphicsItem(parent) {
    mNodeSrc = nodeSrc;
    mNodeDst = nodeDst;
    mPad = 70;
    mColor = Qt::black;

    mNodeSrc->addEdge(this);
    mNodeDst->addEdge(this);

    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setZValue(-1);
}

Edge::~Edge() {}

QRectF Edge::boundingRect() const {
    QLineF line(mNodeSrc->pos(), mNodeDst->pos());

    QPointF tl, br;

    if (line.x1() > line.x2()) {
        tl.setX(line.x2());
        br.setX(line.x1());
    } else {
        tl.setX(line.x1());
        br.setX(line.x2());
    }
    if (line.y1() > line.y2()) {
        tl.setY(line.y2());
        br.setY(line.y1());
    } else {
        tl.setY(line.y1());
        br.setY(line.y2());
    }
    QRectF rect(0, 0, line.dx() + mMeta.linewidth, line.dy());
    qDebug() << rect;
    return rect;
};

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setPen(QPen(mColor, mMeta.linewidth));

    QLineF line(
        mNodeSrc->x() + mNodeSrc->boundingRect().width() / 2, mNodeSrc->y() + mNodeSrc->boundingRect().height() / 2,
        mNodeDst->x() + mNodeDst->boundingRect().width() / 2, mNodeDst->y() + mNodeDst->boundingRect().height() / 2);

    painter->drawLine(line);

    if (mMeta.data.size()) {
        QPointF textPoint;
        QRectF bound = boundingRect();
        textPoint.setX(bound.x() + bound.width() / 2 + 10);
        textPoint.setY(bound.y() + bound.height() / 2 + 10);
        QFont font = painter->font();
        font.setPixelSize(15);
        painter->setFont(font);
        painter->drawText(textPoint, mMeta.data);
    }
    // if (isSelected()) {
    qDebug() << "select";
    QPen pen;
    pen.setStyle(Qt::PenStyle::DotLine);
    pen.setWidth(1);
    QBrush brush;
    brush.setStyle(Qt::BrushStyle::NoBrush);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(boundingRect());
    // }
};
