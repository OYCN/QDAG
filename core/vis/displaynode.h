#ifndef DISPLAYNODE_H
#define DISPLAYNODE_H

#include <QPointF>
#include <functional>

#include "../../vis/graphview.h"
#include "../../vis/node.h"

void DisplayNode(DisplayType type, QVector<Node*>& nodes);

void NoTypeHandle(QVector<Node*>& nodes);

#endif  // DISPLAYNODE_H