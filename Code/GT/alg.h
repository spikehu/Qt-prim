#ifndef ALG_H
#define ALG_H

#include"QList"
#include"node.h"
class Alg
{
public:
    Alg();
    Alg(int size);
    //最小生成树算法需要的3个状态数组
    bool* selected;
    double* minDst;
    int* parent;
    Node MST(QList<Node>* nodesList,Node node);
    int findIndexOfNode(QList<Node> list,int id);//在一个结点找到对应id的结点在link中的位置

};

#endif // ALG_H
