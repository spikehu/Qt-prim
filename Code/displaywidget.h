#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include"node.h"
#include"QList"
namespace Ui {
class DisplayWidget;
}

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWidget(QWidget *parent = nullptr);
    ~DisplayWidget();
    void mouseDoubleClickEvent(QMouseEvent *event);//双击添加节点


    //下面两个bool变量在QAction中connect进行赋值
    bool isFindStartNode;//用于判断是找起点还是终点，0为起点，1为终点
    bool isAddLink ;//判断是在绘制路径还是节点，默认false是节点

    QPainter*  painter;


    Node* findNearestNode(QList<Node>*,QMouseEvent *);//找到离鼠标双击时候的最近节点


    //绘制的方法
    //绘制节点
    void myDrawNode(QList<Node> list,QPainter* painter);

    //因为边取得是结点圆心位置，需要重新计算边的起始位置和终点位置
    //传入直线位置
    QLineF reCalculatePos(QLineF line);
    void MyDrawLink(QList<Node> list,QPainter* painter);//绘制无向图的边
    void myDrawVector(QList<Node> list,QPainter* painter);//绘制有向图的边
    void drawWeight(QList<Node> list,QPainter* painter);//绘制权重

    void paintEvent(QPaintEvent *event);//绘制
    //返回存储的节点,返回list地址
    QList<Node>* getNodesList();
    bool getIsVecter();
    void   setIsVecter(bool isVectoer);

private:
    bool isVecter;//判断是有向图结点还是无向图结点
    Ui::DisplayWidget *ui;
    QList<Node> nodesList;//存储双击生成的多个节点
    void addWeight(QList<double>* weights);





};

#endif // DISPLAYWIDGET_H
