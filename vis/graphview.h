#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>

typedef void* NodePtr;
typedef void* EdgePtr;

class GraphScene;

struct NodeMeta {
    enum class Type { Ellipse };
    struct Data {
        QString data = "";
        QRect rect = QRect(0, 0, 4, 4);
        int flag = Qt::AlignCenter;
        int fontpix = 20;
    };
    int borderwidth = 3;
    QVector<Data> datas;
    Type type = Type::Ellipse;
};

struct EdgeMeta {
    QString data = "";
    int linewidth = 3;
};

enum class DisplayType {
    // 随缘
    NoType,
    // 辐射状散布，靠近中心的节点边缘多
    Dispersion,
    // 水平树状分布
    HorizontalTree,
    // 垂直树状分布
    VerticalTree
};

class GraphView : public QGraphicsView {
 public:
    GraphView(QWidget* parent = nullptr);

 public:
    NodePtr addNode(NodeMeta& metas);
    EdgePtr addEdge(NodePtr src, NodePtr dst, EdgeMeta& meta);

    void setType(DisplayType type);
    DisplayType getType();
    void flush();

 protected:
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

 private:
    GraphScene* mGraphScene;
    bool mIsDrag = false;
    QPoint mStartPos;
};

#endif  // GRAPHVIEW_H