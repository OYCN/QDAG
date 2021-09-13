#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>

#include "../common/macro.h"
#include "graphview.h"

class Edge;
class Node;

class GraphScene : public QGraphicsScene {
    Q_OBJECT

 public:
    GraphScene(QObject* parent = nullptr);

 public:
    void addNode(Node* node);
    void addEdge(Edge* edge);

 public:
    DEF_VAL_ALL(DisplayType, Type);

 private:
    QVector<Node*> mNodes;
    QVector<Edge*> mEdges;
};

#endif  // GRAPHSCENE_H
