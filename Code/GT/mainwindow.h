#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"QMouseEvent"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void QMouseEvent();
    void setALG(QString alg);
    QString getALG();
    //用来限制算法类只生成一次
    bool algFlag;


private:
    Ui::MainWindow *ui;
    //使用一个QString表示用什么算法
    QString ALG;//默认为"" maximumMatch:最大匹配 DST:最短路径 MST：最小生成树

};
#endif // MAINWINDOW_H
