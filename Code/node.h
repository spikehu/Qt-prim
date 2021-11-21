#ifndef NODE_H
#define NODE_H
#include"QPoint"
#include"QString"
#include"QList"
class Node
{
public:
    Node();
    Node(int x,int y,int number);
    //void addNodeLink(Node node);
    QPointF getPoint();
    void setPoint(int x,int y);
    void setStringId(int number);
    QString getStringId();
    double  getR();
    qreal getY();
    qreal  getX();
    void addLink(Node node);
    QList<Node> getLink();
    //List<Node> weightOfEdge设置和设置
    void setWeightOfEdge(int weight);
    QList<double>*  getWeightOfEdge();
    QList<bool> edgeSelected;//边是否被选中,true为被选中
    int index;//第几个结点






private:

    //节点坐标
    qreal  x;
    qreal  y;
    //节点半径
    double r;//默认为30像素
    QPointF p;
    //节点ID
    QString id;
    //与该节点相连的其他节点，使用list进行保存
    QList<Node> linkedNodes;
    //需要QList<int>保存边的权值
    QList<double> weightOfEdge;



};


#endif // NODE_H
