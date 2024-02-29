#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    generateNodes();                        //  Generate nodes
    for (int i = 0; i < mWidth; i++)        //  Test that nodes were created successfully
    {
        for (int j = 0; j < mHeight; j++)
        {
             qDebug() << "x: " << nodes[j * mWidth + i].x;
             qDebug() << "y: " <<nodes[j * mWidth + i].y;
             qDebug() << " ";
    }
    }
    this->setLayout(gridLayout);

    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


bool Widget::generateNodes()
    {
        // Create a 2D array of nodes

        nodes = new Node[mWidth * mHeight];
        for (int i = 0; i < mWidth; i++)
        {
            for (int j = 0; j < mHeight; j++)
            {
                nodes[j * mWidth + i].x = i; // we need to give each node coordinates
                nodes[j * mWidth + i].y = j;
                nodes[j * mWidth + i].obstacle = false;
                nodes[j * mWidth + i].parentNode = nullptr;
                nodes[j * mWidth + i].spotVisited = false;
            }
        }
        //  Create connections with surrounding nodes
        for (int i = 0; i < mWidth; i++)
        {
            for (int j = 0; j < mHeight; j++)
            {                                       // Storing neighboring nodes into vector
                if ( j > 0)
                nodes[j * mWidth + i].vecNeighbor.push_back(&nodes[(j-1) * mWidth + (i + 0)]);
                if (j < mHeight - 1)
                    nodes[j * mWidth + i].vecNeighbor.push_back(&nodes[(j+1) * mWidth + (i + 0)]);
                if ( i > 0)
                nodes[j * mWidth + i].vecNeighbor.push_back(&nodes[(j + 0) * mWidth + (i - 1)]);
                if ( i < mWidth - 1)
                nodes[j * mWidth + i].vecNeighbor.push_back(&nodes[(j + 0) * mWidth + (i + 1)]);

            }
         }
        nodeStart = &nodes[0];
        nodeEnd = &nodes[(50)];

    return true; // Return true if all nodes were generated
    }


void Widget::paintEvent(QPaintEvent* event)
{
    // Create a QPainter object and begin painting

    painter.begin(this);

    // Set the pen and brush to use for drawing

    QPen pen(Qt::black, 3);
    QBrush brush(Qt::white);

    painter.setPen(QPen(Qt::black, 5, Qt::DotLine));



    for (int i = 0; i < mWidth; i++)
    {
        for (int j = 0; j < mHeight; j++)
        {
             for (auto n : nodes[j * mWidth + i].vecNeighbor)
                {
                    painter.drawLine(nodeSize * i + nodeSize / 2, nodeSize * j + nodeSize / 2,
                                     n->x*nodeSize + nodeSize / 2, n->y*nodeSize + nodeSize / 2);
                }
         }
    }

    for (int i = 0; i < mWidth; i++)
    {
        for (int j = 0; j < mHeight; j++)
        {
            painter.setPen(pen);
    // Draw empty nodes
            if(&nodes[j * mWidth + i] != nodeStart && &nodes[j * mWidth + i] != nodeEnd){
                if(nodes[j * mWidth + i].obstacle == false){
                    QRect rect(nodes[j * mWidth + i].x * nodeSize + nodeBorder,
                        nodes[j * mWidth + i].y * nodeSize + nodeBorder,
                        recSize,
                        recSize);
                     brush.setColor(Qt::white);
                     painter.setBrush(brush);
                     painter.drawRect(rect);
                }
    // Draw blue rectangle for obstacles
                if(nodes[j * mWidth + i].obstacle == true){
                        QRect rect(nodes[j * mWidth + i].x * nodeSize + nodeBorder,
                            nodes[j * mWidth + i].y * nodeSize + nodeBorder,
                            recSize,
                            recSize);
                         brush.setColor(Qt::blue);
                         painter.setBrush(brush);
                         painter.drawRect(rect);
                }
            }

                // Draw yellow rectangle if a spot has been checked
                if(nodes[j * mWidth + i].spotVisited){

                    QRect rect(nodes[j * mWidth + i].x * nodeSize + nodeBorder,
                        nodes[j * mWidth + i].y * nodeSize + nodeBorder,
                        recSize,
                        recSize);
                    QColor lYellow(255,255,100);
                    brush.setColor(lYellow);
                    painter.setBrush(brush);
                    painter.drawRect(rect);
                    //QThread::msleep(500);
                        // Run the event loop until the timer's timeout() signal is emitted

                }
                // Draw Green rectangle for start point
                    if(&nodes[j * mWidth + i] == nodeStart){

                        QRect rect(nodes[j * mWidth + i].x * nodeSize + nodeBorder,
                            nodes[j * mWidth + i].y * nodeSize + nodeBorder,
                            recSize,
                            recSize);
                        brush.setColor(Qt::green);
                        painter.setBrush(brush);
                        painter.drawRect(rect);
                    }
                    // Draw Red rectangle for end point
                    if(&nodes[j * mWidth + i] == nodeEnd){

                        QRect rect(nodes[j * mWidth + i].x * nodeSize + nodeBorder,
                            nodes[j * mWidth + i].y * nodeSize + nodeBorder,
                            recSize,
                            recSize);
                        brush.setColor(Qt::red);
                        painter.setBrush(brush);
                        painter.drawRect(rect);
                    }
                //We need to draw path started from end node back to parent
                if(nodeEnd != nullptr)
                {
                    QColor orange(255,100,0);
                    Node *p = nodeEnd;              // Create temp pointer to follow parent
                    while (p->parentNode != nullptr)
                    {
                        painter.setPen(QPen(orange, 4, Qt::DotLine));
                        painter.drawLine(p->x * nodeSize + nodeSize / 2, p->y * nodeSize + nodeSize / 2,
                              p->parentNode->x * nodeSize + nodeSize / 2, p->parentNode->y * nodeSize + nodeSize / 2);
                        // set next node to current nodes parent                        
                        p = p->parentNode;


                    }
                }
                 this->update();

    }
  }


    // End painting
    painter.end();
}

void Widget::mouseReleaseEvent(QMouseEvent* event)
{

    if(event->button() == Qt::LeftButton){
        qDebug() << "x1: " << selectedNodeX;
        qDebug() << "y1: " << selectedNodeY;
        QPoint cursorPos = QCursor::pos();
        selectedNodeX = (cursorPos.x() / nodeSize) - 9;
        selectedNodeY = ((cursorPos.y() - nodeBorder) / nodeSize) - 2;

         if(selectedNodeX >= 0 && selectedNodeX < mWidth) // Make sure selection is within grid
         {
              if(selectedNodeY >= 0 && selectedNodeY < mHeight)
             {
                    nodes[selectedNodeY * mWidth + selectedNodeX].obstacle =
                            !nodes[selectedNodeY * mWidth + selectedNodeX].obstacle; // toggle obstacle on and off
                    nodes[selectedNodeY * mWidth + selectedNodeX].spotVisited = false;
                    qDebug() << "x1: " << selectedNodeX;
                    qDebug() << "y1: " << selectedNodeY;
                this->update();
              }
         }
    }
    if(event->button() == Qt::RightButton){
        QPoint cursorPos = QCursor::pos();
        selectedNodeX = (cursorPos.x() / nodeSize) - 9 ;
        selectedNodeY = ((cursorPos.y() - nodeBorder) / nodeSize) - 2;

         if(selectedNodeX >= 0 && selectedNodeX < mWidth) // Make sure selection is within grid
         {
              if(selectedNodeY >= 0 && selectedNodeY < mHeight)
             {
                    nodeStart =
                            &nodes[selectedNodeY * mWidth + selectedNodeX]; // toggle obstacle on and off
                    qDebug() << "x1: " << selectedNodeX;
                    qDebug() << "y1: " << selectedNodeY;


              }
         }
    }

    if(event->button() == Qt::MiddleButton){
        QPoint cursorPos = QCursor::pos();
        selectedNodeX = (cursorPos.x() / nodeSize) - 9 ;
        selectedNodeY = ((cursorPos.y() - nodeBorder) / nodeSize) - 2 ;

         if(selectedNodeX >= 0 && selectedNodeX < mWidth) // Make sure selection is within grid
         {
              if(selectedNodeY >= 0 && selectedNodeY < mHeight)
             {
                    nodeEnd =
                            &nodes[selectedNodeY * mWidth + selectedNodeX]; // toggle obstacle on and off
                    qDebug() << "x1: " << selectedNodeX;
                    qDebug() << "y1: " << selectedNodeY;


              }
         }
    }


}

void Widget::aStarAlg()
{
    for (int i = 0; i < 1000; ++i)
       label << new QLabel(this);
    // Reset Navigation Graph - default all node states

            for (int i = 0; i < mWidth; i++)
                for (int j = 0; j < mHeight; j++)
                {
                    nodes[j*mWidth + i].spotVisited = false;
                    nodes[j*mWidth + i].globalGoal = INFINITY;
                    nodes[j*mWidth + i].localGoal = INFINITY;
                    nodes[j*mWidth + i].parentNode = nullptr;	// No parents

                }

             auto distance = [](Node *a, Node *b) //Get two nodes and calculate distance
             {
               return sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
             };

             auto heuristic = [distance](Node* a, Node* b) // Calculate heuristic
                     {
                         return distance(a, b);
                     };

             // Start with starting point
             Node *nodeCurrent = nodeStart;
             nodeStart->localGoal = 0.0;
             nodeStart->globalGoal = heuristic(nodeStart, nodeEnd);

             // Create list of untested nodes
             // Add start node to not tested list - this will ensure it gets tested.
             std::list<Node*> untestedNodes;
            untestedNodes.push_back(nodeStart);
            count = 0;
            for(int i = 0; i < 1000; i++)
            label.at(i)->hide();
            while (!untestedNodes.empty() && nodeCurrent != nodeEnd)
            {
                // Sort Untested nodes by global goal, so lowest is first
                untestedNodes.sort([](Node* lhs, Node* rhs)
                { return lhs->globalGoal < rhs->globalGoal; } );

                // If top of list is a visited Node, pop it off the list
                while(!untestedNodes.empty() && untestedNodes.front()->spotVisited)
                                untestedNodes.pop_front();

                if (untestedNodes.empty())
                    break;

                  QEventLoop loop;
                  QTimer::singleShot(15, &loop, SLOT(quit()));
                  loop.exec();

                nodeCurrent = untestedNodes.front();
                nodeCurrent->spotVisited = true; // We only check each node once


               QFont font = label.at(count)->font();
               font.setPointSize(8);
               label.at(count)->setFont(font);
                QString cost = " " + QString::number(nodeCurrent->localGoal) + "    " +
                        QString::number((int)nodeCurrent->globalGoal) + "    \n" + QString::number((int)nodeCurrent->localGoal + (int)nodeCurrent->globalGoal);
                label.at(count)->setText(cost);
                label.at(count)->setGeometry(QRect(nodeCurrent->x* nodeSize + nodeBorder,nodeCurrent->y* nodeSize + nodeBorder,
                                         30, 30));
                label.at(count)->setStyleSheet("background-color: transparent;");

                label.at(count)->show();
                qDebug() << "local: " << nodeCurrent->localGoal << "\nglobal: " << nodeCurrent->globalGoal;


                // check each nodes neighbor
                for (auto nodeNeighbor : nodeCurrent ->vecNeighbor)
                {
                    // if the neighbour is not visited and is
                    // not an obstacle, add it to the untested Nodes List
                    if (!nodeNeighbor->spotVisited && nodeNeighbor->obstacle == 0)
                                  untestedNodes.push_back(nodeNeighbor);

                    // Calculate if neighbor local goal is lower than current
                    float checkifLocalLower = nodeCurrent->localGoal +
                            distance(nodeCurrent, nodeNeighbor);

                    if (checkifLocalLower < nodeNeighbor->localGoal)
                    {
                        nodeNeighbor->parentNode = nodeCurrent;
                        nodeNeighbor->localGoal = checkifLocalLower;

                        // Workout neighbors heuristic
                        nodeNeighbor->globalGoal = nodeNeighbor->localGoal +
                                heuristic(nodeNeighbor, nodeEnd);
                    }
                }
                count = count + 1;

            }

}

void Widget::nodeVisited()
{

}

void Widget::on_pushButton_released()
{

    aStarAlg();
}

