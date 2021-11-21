#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QMenu"
#include"QToolBar"
#include"displaywidget.h"
#include"QTextEdit"
#include"QDebug"
#include"QList"
#include"node.h"
#include"alg.h"
#include"QMessageBox"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->algFlag=false;
    QMessageBox::information(this,"info","使用双击在空白处生成结点，点击连接按钮后，双击选择两个结点进行连线。");





    //菜单 有算法选择 绘制 nextStep
    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    //创建菜单
    QMenu *chooseAlg =  bar->addMenu("算法");
    QMenu *drawGraphic = bar->addMenu("绘制");
//    QMenu *nextStep = bar->addMenu("nextStep");


    QAction *actionAlgMaximumMatching = chooseAlg->addAction("最大匹配算法");
    actionAlgMaximumMatching->setCheckable(true);
    QAction *actionAlgDST =  chooseAlg->addAction("最短路径");
    actionAlgDST->setCheckable(true);
    QAction *actionAlgMST =chooseAlg->addAction("最小生成树");
    actionAlgMST->setCheckable(true);
    chooseAlg->addSeparator();

    //工具区域 负责绘制节点 连接节点
    QToolBar *toolbar = new QToolBar();
    addToolBar(Qt::LeftToolBarArea,toolbar);
    QAction *drawNode = toolbar->addAction("绘制节点");
    //在两节点之间连线添加
    QAction *drawLink = toolbar->addAction("连接节点");

    QAction *nextStep = toolbar->addAction("nextStep");
    drawLink->setCheckable(true);
    drawNode->setCheckable(true);


        //当QAction *drawLink 被点击 开始进行连接操作
        //    绘制区域在中心部件
        //    图形绘制区域
    setCentralWidget(ui->widgetGraph);

    //点击了连接节点QAction,进行路径的绘制
    connect(drawLink,&QAction::triggered,ui->widgetGraph,[=](bool flag)
    {
        qDebug()<<"点击了连接节点";
        ui->widgetGraph->isAddLink=true;
        //先找到路径的起点
        //所以isFindStartNode=true
        ui->widgetGraph->isFindStartNode=true;
        drawNode->setChecked(false);

    });

    //点击了绘制节点，进行节点绘制
    connect(drawNode,&QAction::triggered,ui->widgetGraph,[=]()
    {
        qDebug()<<"点击了绘制节点";
        drawLink->setChecked(false);
        //则isAddLink=false;
        ui->widgetGraph->isAddLink=false;
    });

    //根据选择了不同的算法，展示不同的算法步骤
    //使用connect 使用匿名函数调用不同的算法
    //点击nextStep展示算法的每一个步骤

    //选择了最大匹配算法
    connect(actionAlgMaximumMatching,&QAction::triggered,ui->widgetGraph,[=]
    {
        //ALG = "maximumMatch" 并在nexStep进行算法调用
        this->setALG("maximumMatch");
        qDebug()<<"选择了最大匹配";
        actionAlgDST->setChecked(false);
        actionAlgMST->setChecked(false);

        //设置为无向图
        ui->widgetGraph->setIsVecter(false);
    });
    //选择了最短路径算法
    connect(actionAlgDST,&QAction::triggered,ui->widgetGraph,[=]()
    {
         this->setALG("DST");
        qDebug()<<"选择了最短路径";
        actionAlgMaximumMatching->setChecked(false);
        actionAlgMST->setChecked(false);
         //设置为有向图
         ui->widgetGraph->setIsVecter(true);
    });

    //选择了最小生成树算法
    connect(actionAlgMST,&QAction::triggered,ui->widgetGraph,[=]()
    {
        this->setALG("MST");
        qDebug()<<"选择了最小生成树";
          actionAlgMaximumMatching->setChecked(false);
          actionAlgDST->setChecked(false);
          //设置为无向图
          ui->widgetGraph->setIsVecter(false);
    });
//点击了nextStep
    connect(nextStep,&QAction::triggered,ui->widgetGraph,[=]()
    {
         static Node node;
         static Alg* alg;
        QList<Node> *list = ui->widgetGraph->getNodesList();
        if(!this->algFlag )
        {
             alg = new Alg(list->size());
             alg->selected[0]=true;
            //默认从第一个结点开始
             node = list->operator[](0);
             this->algFlag=true;
             qDebug()<<"进入";
        }
        node = alg->MST(list,node);
        ui->widgetGraph->update();
    });
}
//算法选择
void MainWindow::setALG(QString alg)
{
    this->ALG= alg;
}
QString MainWindow::getALG()
{
    return this->ALG;
}
MainWindow::~MainWindow()
{
    delete ui;
}

