#include "graphscene.h"

#include "edge.h"
#include "node.h"

#include "../core/vis/displaynode.h"

GraphScene::GraphScene(QObject* parent) : QGraphicsScene(parent) {
    mType = DisplayType::NoType;
    this->setItemIndexMethod(QGraphicsScene::ItemIndexMethod::NoIndex);
}

void GraphScene::addNode(Node* node) {
    mNodes.push_back(node);
    this->addItem(node);
    DisplayNode(mType, mNodes);

    update();
}

void GraphScene::addEdge(Edge* edge) {
    mEdges.push_back(edge);
    this->addItem(edge);

    update();
}
