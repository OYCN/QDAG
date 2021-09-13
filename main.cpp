#include <QApplication>
#include <QMainWindow>

#include "vis/graphview.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QMainWindow w;
    GraphView* g = new GraphView;
    {
        QVector<NodeMeta> nmetas(1);
        NodeMeta& nmeta = nmetas[0];
        nmeta.data = "a";
        nmeta.flag = Qt::AlignCenter;
        nmeta.rect = QRect(5, 5, 30, 30);
        NodePtr nodeA = g->addNode(nmetas);
        nmeta.data = "b";
        NodePtr nodeB = g->addNode(nmetas);
        QVector<EdgeMeta> emetas(1);
        EdgeMeta& emeta = emetas[0];
        emeta.data = "111";
        EdgePtr edgeAB = g->addEdge(nodeA, nodeB, emetas);
    }
    w.setCentralWidget(g);
    w.show();
    return a.exec();
}
