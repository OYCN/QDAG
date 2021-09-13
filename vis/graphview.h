#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>

typedef void* NodePtr;
typedef void* EdgePtr;

class GraphScene;

struct NodeMeta {
    QString data;
    QRect rect;
    int flag;
};

struct EdgeMeta {
    QString data;
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
    NodePtr addNode(QVector<NodeMeta>& metas);
    EdgePtr addEdge(NodePtr src, NodePtr dst, QVector<EdgeMeta>& metas);

    void setType(DisplayType type);
    DisplayType getType();

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