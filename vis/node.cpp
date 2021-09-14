#include "node.h"

#include <QDebug>
#include <QPainter>

#include "edge.h"

Node::Node(QGraphicsItem *parent) : QGraphicsItem(parent) {
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    mBackgroundColor = Qt::white;
    mBorderColor = Qt::black;
    mRectX = 0;
    mRectY = 0;
    mRectW = 10;
    mRectH = 10;
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

void Node::setMetas(NodeMeta &metas) {
    mMetas = metas;
    updateRect();
}

NodeMeta Node::getMetas() { return mMetas; }

void Node::updateRect() {
    QVector<NodeMeta::Data> &metas = mMetas.datas;
    qreal min_x = metas[0].rect.x();
    qreal max_x = metas[0].rect.x() + metas[0].rect.width();
    qreal min_y = metas[0].rect.y();
    qreal max_y = metas[0].rect.y() + metas[0].rect.height();
    for (int i = 1; i < metas.size(); i++) {
        NodeMeta::Data &meta = metas[i];
        QRect &rect = meta.rect;
        int x = rect.x();
        int y = rect.y();
        int mx = x + rect.width();
        int my = y + rect.height();
        min_x = x < min_x ? x : min_x;
        max_x = mx > max_x ? mx : max_x;
        min_y = y < min_y ? y : min_y;
        max_y = my > max_y ? my : max_y;
    }
    min_x -= (mMetas.borderwidth + 0.5) / 2;
    max_x += (mMetas.borderwidth + 0.5) / 2;
    min_y -= (mMetas.borderwidth + 0.5) / 2;
    max_y += (mMetas.borderwidth + 0.5) / 2;
    // qDebug() << "minx:" << min_x << " maxx:" << max_x << " miny:" << min_y << "maxy:" << max_y;
    qreal center_x = (max_x + min_x) / 2;
    qreal center_y = (max_y + min_y) / 2;
    if (mMetas.type == NodeMeta::Type::Ellipse) {
        int dff_x = max_x - min_x;
        int dff_y = max_y - min_y;
        int max_dff = dff_x > dff_y ? dff_x : dff_y;
        constexpr qreal sqrt_2 = 1.41421356237;
        mRectW = max_dff * sqrt_2;
        mRectH = max_dff * sqrt_2;
        mRectX = center_x - mRectW / 2;
        mRectY = center_x - mRectH / 2;
        // qDebug() << "Node: " << reinterpret_cast<void *>(this) << ", X: " << mRectX << ", Y: " << mRectY
        //          << ", D: " << mRectW;
    }
}

QPointF Node::centerPos() {
    return pos() + QPointF(mRectX + mRectW / 2, mRectY + mRectH / 2);
}

QRectF Node::boundingRect() const { return QRectF(mRectX, mRectY, mRectW, mRectH); }

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF bound = boundingRect();

    // painter->setBrush(QBrush(mBackgroundColor));
    painter->setPen(QPen((QBrush(mBorderColor), mMetas.borderwidth)));
    painter->drawEllipse(bound.x(), bound.y(), bound.width(), bound.height());
    QVector<NodeMeta::Data> &metas = mMetas.datas;
    for (int i = 0; i < metas.size(); i++) {
        NodeMeta::Data &meta = metas[i];
        QFont font = painter->font();
        font.setPixelSize(meta.fontpix);
        painter->setFont(font);
        painter->drawText(meta.rect.x(), meta.rect.y(), meta.rect.width(), meta.rect.height(), meta.flag, meta.data);
    }

    if (isSelected()) {
        QPen pen;
        pen.setStyle(Qt::PenStyle::DotLine);
        pen.setWidth(1);
        QBrush brush;
        brush.setStyle(Qt::BrushStyle::NoBrush);
        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawRect(bound);
    }
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event) { QGraphicsItem::mouseMoveEvent(event); }

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, mEdges)
            edge->updateRect();
        break;
    default:
        break;
    };
    // qDebug() << change;

    return QGraphicsItem::itemChange(change, value);
}
