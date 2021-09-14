#include "graphview.h"
#include <QDebug>
#include <QScrollBar>
#include <QWheelEvent>

#include "edge.h"
#include "graphscene.h"
#include "node.h"

GraphView::GraphView(QWidget *parent) : QGraphicsView(parent) {
    mGraphScene = new GraphScene();
    this->setScene(mGraphScene);
    this->setRenderHint(QPainter::Antialiasing, true);
    this->setMouseTracking(true);

    mGraphScene->setSceneRect(-10000, -10000, 20000, 20000);

    this->setBackgroundBrush(QBrush(QPixmap(":/grid/grid100_w4_28o.png")));
}

NodePtr GraphView::addNode(NodeMeta &metas) {
    Node *node = new Node;
    node->setMetas(metas);
    mGraphScene->addNode(node);
    return reinterpret_cast<NodePtr>(node);
}
EdgePtr GraphView::addEdge(NodePtr src, NodePtr dst, EdgeMeta &meta) {
    Node *s = reinterpret_cast<Node *>(src);
    Node *d = reinterpret_cast<Node *>(dst);
    Edge *edge = new Edge(s, d);
    edge->setMeta(meta);
    mGraphScene->addEdge(edge);
    return reinterpret_cast<EdgePtr>(edge);
}

void GraphView::setType(DisplayType type) { mGraphScene->setType(type); }
DisplayType GraphView::getType() { return mGraphScene->getType(); }

void GraphView::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        this->scale(1.1, 1.1);
    } else {
        this->scale(0.9, 0.9);
    }
}

void GraphView::flush() { mGraphScene->flush(); }

void GraphView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        this->mIsDrag = true;
        this->viewport()->setCursor(Qt::ClosedHandCursor);
        this->mStartPos = event->pos();
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphView::mouseMoveEvent(QMouseEvent *event) {
    if (this->mIsDrag) {
        QPoint movPos = event->pos();
        QPoint dis = movPos - mStartPos;
        QScrollBar *hBar = horizontalScrollBar();
        QScrollBar *vBar = verticalScrollBar();
        hBar->setValue(hBar->value() + (isRightToLeft() ? dis.x() : -dis.x()));
        vBar->setValue(vBar->value() - dis.y());
        mStartPos = movPos;
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphView::mouseReleaseEvent(QMouseEvent *event) {
    this->mIsDrag = false;
    this->viewport()->setCursor(Qt::ArrowCursor);
    QGraphicsView::mouseReleaseEvent(event);
}
