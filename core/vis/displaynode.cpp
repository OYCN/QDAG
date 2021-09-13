#include "displaynode.h"

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
}