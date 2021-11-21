#include "alg.h"
#include"QDebug"
#include"node.h"
Alg::Alg()
{

}
Alg::Alg(int size)
{
    this->parent = new int[size];
    this->selected =new bool[size];
    this->minDst =new double[size];
    for(int i =0;i < size;i++)
    {
        this->parent[i] = 0;
        this->minDst[i]= __DBL_MAX__;
        this->selected[i]=false;
    }
}
//传入3个状态数组和新选中的结点
Node Alg::MST(QList<Node>* nodesList,Node node)
{

    //使用普利姆算法
    //默认从第0个结点开始
//    nodesList->operator[](0).edgeSelected.operator[](0)=true;
//    nodesList->operator[](1).edgeSelected.operator[](0)=true;
    int nodesSize = nodesList->size();//用来得到数组长度



    //从新加入的结点遍历所有可达的结点未被选中的结点，并把比当前minDst小的值加入同时更新该结点父亲结点
    for(int index =0 ; index < node.getWeightOfEdge()->size();index++ )
    {

        int linkId =node.getLink().at(index).index;
//         qDebug()<<linkId;

        //qDebug()<<"遍历"<<linkId<<":"<<node.getWeightOfEdge()->at(index)<<selected[linkId];

        if( !selected[linkId]&& node.getWeightOfEdge()->at(index) <= minDst[linkId] )
        {
//             qDebug()<<"end";
            //更新

            minDst[linkId] = node.getWeightOfEdge()->at(index);
            parent[linkId] = node.index;
        }
    }

    //选择未被遍历的距离最小的结点
    int id = 0  ;
    double min = __DBL_MAX__;
    for(int index = 0;index <nodesSize;index++ )
    {
        if(!selected[index] && minDst[index] < min )
        {
            id = index ;
            min =minDst[index];
        }
    }
    selected[id] =true;


    //打印状态
    for(int i=0 ; i <nodesSize;i++ )
    {
        qDebug()<<selected[i];
        qDebug()<<minDst[i];
        qDebug()<<parent[i];
    }
    //算法结束，对所有边进行状态更新
    //比如 结点1和2选择了一条边，则1.edgeSelected中对应2的为true 同时2.edgeSelected对应1的也是true
    //从结点id为1的开始
    for(int i = 1;i < nodesSize;i++)
    {
        if(selected[i])
        {
            int linkedNodeId = parent[i];
            //从该点相邻的点中找到该点在link中的位置
            qDebug()<<"结点"<<i<<"邻接结点："<<linkedNodeId;
            int index =  findIndexOfNode(nodesList->operator[](i).getLink(),linkedNodeId);
            //将相应的edgeSelected设置为true;
            nodesList->operator[](i).edgeSelected.operator[](index)=true;

//            //另一条边也要进行同样操作
           int index2 = findIndexOfNode(nodesList->operator[](linkedNodeId).getLink(),i);
           nodesList->operator[](linkedNodeId).edgeSelected.operator[](index2)=true;
        }
    }


return nodesList->operator[](id);
}
//在一个结点找到对应id的结点在link中的位置
int Alg::findIndexOfNode(QList<Node> list,int id)
{
    for(int i=0;i<list.size();i++)
    {

        if(id== list.at(i).index)
        {
            return i;
        }
    }
    qDebug()<<-1;
    return -1;//否则返回-1
}
