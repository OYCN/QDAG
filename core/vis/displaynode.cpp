#include "displaynode.h"

#include <math.h>
#include <QDebug>

void DisplayNode(DisplayType type, QVector<Node*>& nodes) {
    switch (type) {
        case DisplayType::NoType:
            NoTypeHandle(nodes);
            break;

        default:
            break;
    }
}

void NoTypeHandle(QVector<Node*>& nodes) {
    // TODO
    qDebug() << "NoTypeHandle running";
    int cols = sqrt(nodes.size() + 1);
    qDebug() << "cols: " << cols;
    for (int i = 0; i < nodes.size(); i++) {
        int idx_x = i % cols;
        int idx_y = i / cols;
        qreal start_x = 0;
        qreal start_y = 0;
        Node* m = nodes[i];
        QRectF c = m->boundingRect();
        if (idx_x != 0) {
            Node* left = nodes[idx_y * cols + idx_x - 1];
            QRectF l = left->boundingRect();
            qreal dis = (l.width() + c.width()) / 2;
            start_x = l.x() + l.width() + dis;
        }
        if (idx_y != 0) {
            Node* top = nodes[(idx_y - 1) * cols + idx_x];
            QRectF t = top->boundingRect();
            qreal dis = (t.height() + c.height()) / 2;
            start_y = t.y() + t.height() + dis;
        }
        // qDebug() << "start_x: " << start_x << " start_y: " << start_y;

        // start_x += c.width() / 2;
        // start_y += c.height() / 2;
        m->setPos(start_x, start_y);
        qDebug() << "Node(" << idx_x << ", " << idx_y << ") x: " << start_x << ", y: " << start_y;
    }
}