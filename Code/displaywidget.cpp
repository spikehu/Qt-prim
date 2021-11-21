#include "displaywidget.h"
#include "ui_displaywidget.h"
#include"QPainter"
#include"node.h"
#include"QDebug"
#include"QPen"
#include"QInputDialog"
#include"QMessageBox"
#define r 30
DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWidget)
{
    ui->setupUi(this);  
    this->isAddLink=false;
    this->isFindStartNode=true;
    this->setIsVecter(false);

}

DisplayWidget::~DisplayWidget()
{
    delete ui;
}

void DisplayWidget:: myDrawNode(QList<Node> nodesList,QPainter* painter)
{
    //遍历nodesList进行绘制

        for(int index =0 ;index< nodesList.size();index++)
        {
            Node node = nodesList.at(index);
            QBrush brush(QColor(122,122,0));
            QPen pen(QColor(0,0,0));
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawEllipse(node.getPoint(),r,r);
            //在圆中心绘制id
            painter->drawText(node.getPoint(),node.getStringId());
        }

}
//因为边取得是结点圆心位置，需要重新计算边的起始位置和终点位置
//line 是直线 r是结点绘制的半径
QLineF DisplayWidget::reCalculatePos(QLineF line)
{
    const static double pi = 3.14159265358979323846264338327950288419717;
    double angle  =::acos(line.dx()/line.length());
    QPointF sourceP = line.p1();
    QPointF destP=line.p2();
    //------------需要重新计算 还未实现
    if(line.dy() >= 0)
    {
        angle = 2*pi-angle;
    }
    QPointF newSourceP = sourceP + QPointF(sin(angle )*r ,cos(angle )*r);
    QPointF newDestP = destP  + QPointF(sin(angle )*r ,cos(angle )*r);
    QLineF newLine(newSourceP,newDestP);




 return newLine;

}
void DisplayWidget:: drawWeight(QList<Node> list,QPainter* painter)
{
    for(int index =0 ;index< nodesList.size();index++)
    {
        Node node = nodesList.at(index);
        //传入起点和终点
        //遍历该节点的所有路径并且绘制
//             qDebug()<<node.getLink().size();
         for(int  k = 0;k<node.getLink().size();k++){
             Node linkedNode = node.getLink().at(k);
             QPointF destPoint = linkedNode.getPoint();//终点
             QPointF sourcePoint = node.getPoint();//起点
             QPointF mid = (destPoint+sourcePoint)/2;
             if(!node.getWeightOfEdge()->isEmpty()&&k<node.getWeightOfEdge()->size())
             {
                 QFont font;
                 QPen pen;
                 pen.setColor(QColor(0,0,0));
                 font.setPointSize(10);
                 painter->setFont(font);
                 painter->setPen(pen);
                 painter->drawText(mid,QString::number(node.getWeightOfEdge()->at(k)));

             }
         }

    }
}//绘制权重
//绘制无向图的边
void DisplayWidget:: MyDrawLink(QList<Node> nodesList,QPainter* painter)
{
        //遍历nodesList进行绘制
     qDebug()<<"www";
    qDebug()<<"开始绘制";

        for(int index =0 ;index< nodesList.size();index++)
        {
            Node node = nodesList.at(index);
             QPen *pen= new QPen();
            //传入起点和终点
            //遍历该节点的所有路径并且绘制
//             qDebug()<<node.getLink().size();
             for(int  k = 0;k<node.getLink().size();k++){
                 Node linkedNode = node.getLink().at(k);
                 QPointF destPoint = linkedNode.getPoint();//终点
                 QPointF sourcePoint = node.getPoint();//起点
                 QLineF line(sourcePoint,destPoint);
                // --------------------这里调用了重新计算绘制直线的起点和终点，该功能还没有实现

                 //如果边被选中，则用另外一种颜色
                 if( k < node.edgeSelected.size()&& node.edgeSelected.at(k))
                 {
                     //qDebug()<<"换了颜色"<<node.getStringId()<<"--->"<<linkedNode.getStringId();
                     pen->setColor(QColor(255,255,44));
                     pen->setWidth(10);
                     painter->setPen(*pen);

                     painter->drawLine(sourcePoint,destPoint);

                 }else  if( k < node.edgeSelected.size()&& false==node.edgeSelected.at(k))
                 {
                     //qDebug()<<"恢复了颜色"<<node.edgeSelected.at(k)<<QString::number(k)<<node.getStringId();

                     //恢复原来的颜色
                     pen->setColor(QColor(0,0,0));
                     pen->setWidth(1);
                     painter->setPen(*pen);
                     painter->drawLine(sourcePoint,destPoint);

                 }
                  drawWeight(nodesList,painter);


             }

        }
}

//绘制有向图的边
void DisplayWidget::myDrawVector(QList<Node> list, QPainter *painter)
{

    //遍历nodesList进行绘制
    static double Pi=3.14159265358979323846264338327950288419717;
    static double arrowSize = 20;

    for(int index =0 ;index< nodesList.size();index++)
    {
        Node node = nodesList.at(index);
        //传入起点和终点
        //遍历该节点的所有路径并且绘制
         for(int  k = 0;k<node.getLink().size();k++){
             Node linkedNode = node.getLink().at(k);//终点结点
             QPointF destPoint = linkedNode.getPoint();//终点
             QPointF sourcePoint = node.getPoint();//起点
             QLineF line(sourcePoint,destPoint);
             double angle = ::acos(line.dx()/line.length());
             if (line.dy() >= 0)
                      angle = 2*Pi - angle;

             //绘制直线
             painter->drawLine(node.getPoint(),linkedNode.getPoint());
             //绘制箭头
               QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + Pi / 3) * arrowSize,
                                                               cos(angle + Pi / 3) * arrowSize);
               QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                                               cos(angle + Pi - Pi / 3) * arrowSize);
               QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
                                                           cos(angle - Pi / 3) * arrowSize);
               QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
                                                           cos(angle - Pi + Pi / 3) * arrowSize);
               painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
               drawWeight(list,painter);

         }

    }
}
//在该函数内进行绘制操作
void DisplayWidget:: paintEvent(QPaintEvent* event)
{

    //重新绘制nodesList中的节点
    QPainter *painter =new QPainter(this);
    QPen *pen = new QPen(QColor(255,122,0));
    //painter->setBrush(brush);

    if(this->getIsVecter())
    {

         myDrawVector(this->nodesList,painter);
    }else
    {

        MyDrawLink(this->nodesList,painter);
    }

    myDrawNode(this->nodesList,painter);
}
//找到鼠标双击时候的结点
Node* DisplayWidget::findNearestNode(QList<Node> *nodeList,QMouseEvent *event)
{
    Node *nearestNode = &nodeList->operator[](0);
    double minDistance = pow(nearestNode->getX()-event->x(),2)+pow(nearestNode->getY()-event->y(),2);
    for(int index =1;index < nodeList->size();index++)
    {
         Node *node = &nodeList->operator[](index);
         double distance = pow(node->getX()-event->x(),2)+pow(node->getY()-event->y(),2);
         if(minDistance > distance )
         {
             minDistance=distance;
             nearestNode = node;
         }
    }

    return nearestNode;
}
//添加结点或者路径
void DisplayWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Node static *startOfLink= new Node();
    Node static *endOfLink=new Node();
   int static id = 1;
   //根据鼠标点击位置生成节点

   if(!this->isAddLink)
   {
        this->nodesList.append(Node(event->x(),event->y(),id++));

        update();//重新绘制
   }else
   {


       //首先判断鼠标双击的位置，在nodesList中寻找离该位置最近的节点作为选中的起点
       //循环遍历找到最近的节点
       //比较平方就可以
      //通过findNearestNode方法得到最近节点

       //判断是找到终点还是起点
       //在nodesList中找到开始节点，并且把终点与之关联
       switch (this->isFindStartNode) {
       case true:
           //找路径起点
            startOfLink = findNearestNode(&this->nodesList,event);

//            qDebug()<<"找到起点"+startOfLink->getStringId();
           break;
       case false:
            endOfLink = findNearestNode(&this->nodesList,event);
            //记录startOfLink和endOfLink节点间的路径
            startOfLink->addLink(*endOfLink);
//            qDebug()<<"找到终点"+endOfLink->getStringId();
            this->addWeight(startOfLink->getWeightOfEdge());
            startOfLink->edgeSelected.append(false);

            //如果是有向图，这里就不添加
            //--------------------------------------待做，根据标志位判断是有向图还是无向图---------
            if(!this->getIsVecter())
            {

                endOfLink->addLink(*startOfLink);
                endOfLink->getWeightOfEdge()->append(startOfLink->getWeightOfEdge()->last());
                endOfLink->edgeSelected.append(false);
                //qDebug()<<"size:"<<QString::number(endOfLink->getWeightOfEdge()->size());
            }

            //在这里弹出一个输入框，要求输入边的权值----------------------待做-----------------------------------------------------------------
            //qDebug()<<"找到路径"+startOfLink->getStringId()+"--->"+startOfLink->getLink().last().getStringId();

             update();//重新绘制
           break;
       default:
           break;
       }
       //状态切换
       this->isFindStartNode = !this->isFindStartNode;


   }


}
//添加权重
//直接list.append()
void DisplayWidget::addWeight(QList<double>* weights)
{
    bool ok ;
    double num = QInputDialog::getDouble(this,"添加权重","权重:",1,1,1000000,2,&ok);
    if(ok)
    {
        weights->append(num);

    }
}
QList<Node>* DisplayWidget:: getNodesList()
{
    return &this->nodesList;
}
bool DisplayWidget::getIsVecter()
{
   return this->isVecter;
}
void DisplayWidget::setIsVecter(bool b)
{
    this->isVecter=b;
}

