#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QProcess>
#include <QEvent>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMenu>
#include <setting.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event); //重新定义窗口关闭事件

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *tray;             //定义托盘图标
    QDateTime systemTime;              //当前系统时间
    QString shutdownString;            //储存ShutdownMessage提示语句
    QString command;                   //储存关机命令
    QString contains;                  //储存contains
    QString info;
    QTime time_1,time_2;
    QProcess p;                        //执行命令的进程
    QIcon icon;                        //创建图标
    QAction *quitAction;               //退出事件
    QAction *setAction;                //设置事件
    QMenu *trayIconMenu;               //托盘图标点击菜单

    int i,h1,m1,h2,m2,judge;           //计时间差 单位:s
    Setting *w;
    void creatActions();               //事件初始化和关联函数
    void creatMenu();                  //菜单创建函数


private slots:
    void CancelSlot();                 //取消关机计划
    void setPlan();                    //重新定制关机计划
    void showSlot();                   //图标点击后 弹出主窗口
    void setSlot();                    //弹出设置窗口
    void SetInfoSlot(bool set);

    void readTxt();
    void iconActivied(QSystemTrayIcon::ActivationReason reason);

public slots:
    int ShowMessage();                  //发送通知函数
};

#endif // MAINWINDOW_H
