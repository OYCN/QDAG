#include "edge.h"
#include "node.h"

#include <QDebug>
#include <QPainter>
#include <math.h>

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

void Edge::updateRect() {
    QPointF src = mNodeSrc->centerPos();
    QPointF dst = mNodeDst->centerPos();
    // qDebug() << src << dst;

    mRectW = abs(src.x() - dst.x());
    mRectH = abs(src.y() - dst.y());
    mRectX = src.x() < dst.x() ? src.x() : dst.x();
    mRectY = src.y() < dst.y() ? src.y() : dst.y();
    int off = mMeta.linewidth / 2 + mMeta.linewidth % 2;
    off += off * 1.5;
    mRectX -= off;
    mRectY -= off;
    mRectW += off * 2;
    mRectH += off * 2;
    qDebug() << "x:" << mRectX << "y:" << mRectY << "w:" << mRectW << "h:" << mRectH << "off:" << off;
}

QRectF Edge::boundingRect() const {
    
    return QRectF(mRectX, mRectY, mRectW, mRectH);
};

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setPen(QPen(mColor, mMeta.linewidth));

    painter->drawLine(QLineF(mNodeSrc->centerPos(), mNodeDst->centerPos()));

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
    if (isSelected()) {
        QPen pen;
        pen.setStyle(Qt::PenStyle::DotLine);
        pen.setWidth(1);
        QBrush brush;
        brush.setStyle(Qt::BrushStyle::NoBrush);
        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawRect(boundingRect());
    }
};
