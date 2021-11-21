#include "node.h"
#include"QPoint"
#include"QString"
Node::Node(int x,int y,int number)
{
    this->r=30;
    setPoint(x,y);
    setStringId(number);
    this->index=number-1;

}
Node::Node()
{
}
void Node::addLink(Node node)
{
    this->linkedNodes.append(node);
}
QList<Node> Node:: getLink()
{
    return this->linkedNodes;
}
QPointF Node:: getPoint()
{
    return this->p;
}
void Node::setPoint(int x, int y)
{
    this->x=x;
    this->y=y;
    this->p =  QPoint(x,y);
}
qreal Node::getX()
{
    return  this->x;
}
qreal Node::getY()
{
    return this->y;
}
void Node::setStringId(int number)
{
    this->id = "V"+QString::number(number);
}
QString Node::getStringId()
{
    return this->id;
}
double Node::getR()
{
    return this->r;

}
//设置边的权值和得到边的权值
void Node::setWeightOfEdge(int weight)
{
    this->weightOfEdge.append(weight);
}
QList<double>* Node::getWeightOfEdge()
{
    return &this->weightOfEdge;
}




