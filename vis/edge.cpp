#include "edge.h"
#include "node.h"

#include <math.h>
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

QRectF Edge::boundingRect() const { return QRectF(mRectX, mRectY, mRectW, mRectH); };

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setPen(QPen(mColor, mMeta.linewidth));

    QLineF line(mNodeSrc->centerPos(), mNodeDst->centerPos());

    qreal angle = std::atan2(line.dy(), line.dx());

    QPointF src = mNodeSrc->crossPos(angle);
    QPointF dst = mNodeDst->crossPos(angle + M_PI);

    painter->drawLine(QLineF(src, dst));

    QPointF arrowA;
    QPointF arrowB;
    arrowA.setX(dst.x() + cos(angle + M_PI - mMeta.arrowAngle) * mMeta.arrowLen);
    arrowA.setY(dst.y() + sin(angle + M_PI - mMeta.arrowAngle) * mMeta.arrowLen);
    arrowB.setX(dst.x() + cos(angle + M_PI + mMeta.arrowAngle) * mMeta.arrowLen);
    arrowB.setY(dst.y() + sin(angle + M_PI + mMeta.arrowAngle) * mMeta.arrowLen);
    qDebug() << (angle + M_PI - mMeta.arrowAngle) * 180 / M_PI << cos(angle + M_PI - mMeta.arrowAngle);
    painter->setPen(QPen(mColor, mMeta.arrowwidth));
    // painter->setBrush(QBrush(Qt::black));
    // painter->drawPolygon(QPolygonF() << dst << arrowA << arrowB);
    painter->drawLine(QLineF(dst, arrowA));
    painter->drawLine(QLineF(dst, arrowB));

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
