#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <vector>
#include <QGridLayout>
#include <QPainter>
#include <QDebug>
#include <QPoint>
#include <QMouseEvent>
#include <QTimer>
#include <QThread>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    QGridLayout *gridLayout = new QGridLayout(this);
    QTimer timer;
    QList<QLabel *> label;
    QPainter painter;

    int nodeSize = 60;
    int nodeBorder = 10;    
    int recSize = 30;

    int count;
    int selectedNodeX;
    int selectedNodeY;

    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    struct Node
    {
        bool obstacle = false;      // If node is blocking path
        bool spotVisited = false;   // If node has been checked
        float globalGoal;           // Distance to end point
        float localGoal;            // Distance to goal from current node
        int x;
        int y;
        std::vector<Node*> vecNeighbor;  // Connections to neighbors
        Node * parentNode;          //Nodes connecting to this node
    };

    Node *nodes = nullptr;
    Node *nodeStart = nullptr;
    Node *nodeEnd = nullptr;
    //Node *currentNode = nullptr;

    int mWidth = 10;            // Width and Height of grid
    int mHeight = 10;

    Ui::Widget *ui;

private slots:
    bool generateNodes();
    void aStarAlg();
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
    void nodeVisited();
    void on_pushButton_released();
};
    #endif // WIDGET_H
