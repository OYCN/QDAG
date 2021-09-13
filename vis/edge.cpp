#include "edge.h"
#include "node.h"

#include <QPainter>

Edge::Edge(Node* nodeSrc, Node* nodeDst, QGraphicsItem* parent) : QGraphicsItem(parent) {
    mNodeSrc = nodeSrc;
    mNodeDst = nodeDst;
    mPad = 70;
    mColor = Qt::black;

    mNodeSrc->addEdge(this);
    mNodeDst->addEdge(this);

    this->setZValue(-1);
}

Edge::~Edge() {}

QRectF Edge::boundingRect() const {
    QPointF centerA(mNodeSrc->x(), mNodeSrc->y());
    QPointF centerB(mNodeDst->x(), mNodeDst->y());
    qreal srcX = mNodeSrc->x();
    qreal srcY = mNodeSrc->y();
    qreal dstX = mNodeDst->x();
    qreal dstY = mNodeDst->y();

    QPointF tl, br;

    if (srcX > dstX) {
        tl.setX(dstX - mPad);
        br.setX(srcX + mPad);
    } else {
        tl.setX(srcX - mPad);
        br.setX(dstX + mPad);
    }
    if (srcY > dstY) {
        tl.setY(dstY - mPad);
        br.setY(srcY + mPad);
    } else {
        tl.setY(srcY - mPad);
        br.setY(dstY + mPad);
    }

    return QRectF(tl, br);
};

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setPen(QPen(mColor, 3));

    QLineF line(
        mNodeSrc->x() + mNodeSrc->boundingRect().width() / 2, mNodeSrc->y() + mNodeSrc->boundingRect().height() / 2,
        mNodeDst->x() + mNodeDst->boundingRect().width() / 2, mNodeDst->y() + mNodeDst->boundingRect().height() / 2);

    painter->drawLine(line);

    if (mMetas.size()) {
        QPointF textPoint;
        QRectF bound = boundingRect();
        textPoint.setX(bound.x() + bound.width() / 2 + 10);
        textPoint.setY(bound.y() + bound.height() / 2 + 10);
        QFont font = painter->font();
        font.setPixelSize(15);
        painter->setFont(font);
        painter->drawText(textPoint, mMetas[0].data);
    }
};
