#include <QApplication>
#include <QMainWindow>

#include "vis/graphview.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QMainWindow w;
    GraphView* g = new GraphView;
    {
        NodeMeta nmeta;
        nmeta.datas.resize(1);
        nmeta.type = NodeMeta::Type::Ellipse;
        nmeta.datas[0].data = "a";
        nmeta.datas[0].flag = Qt::AlignCenter;
        nmeta.datas[0].rect = QRect(5, 5, 30, 30);
        NodePtr nodeA = g->addNode(nmeta);
        nmeta.datas[0].data = "b";
        NodePtr nodeB = g->addNode(nmeta);
        EdgeMeta emeta;
        emeta.data = "111";
        EdgePtr edgeAB = g->addEdge(nodeA, nodeB, emeta);
        g->flush();
    }
    w.setCentralWidget(g);
    w.show();
    return a.exec();
}
