#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    w = new Setting;
    this->setMaximumSize(306,306);
    this->setMinimumSize(306,306);
    this->setWindowTitle("PowerSet");
    /*以上为 主窗口的参数设定*/

    tray = new QSystemTrayIcon;
    icon.addFile(":/new/prefix1/C:/Users/Fuerm/Desktop/electricity-32.png");
    tray->setToolTip("PowerSet is working");
    tray->setIcon(icon);    
    tray->show();
    /*以上为 托盘的设定*/

    creatActions();
    creatMenu();
    /*以上为 托盘菜单的设定*/

    connect(ui->CancleButton,SIGNAL(clicked()),this,SLOT(CancelSlot()));
    connect(ui->ChangeButton,SIGNAL(clicked()),this,SLOT(setPlan()));
    connect(w,SIGNAL(dlgRturn(bool)),this,SLOT(SetInfoSlot(bool)));

    /*以上为 主界面上两个按钮的槽函数关联*/

    connect(tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(iconActivied(QSystemTrayIcon::ActivationReason)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetInfoSlot(bool set)
{
    if(set == true)
    {
        ShowMessage();
    }
}

void MainWindow::readTxt()
{
    QFile *file = new QFile;
    file->setFileName(QDir::currentPath()+"\\set.txt");
    file->open(QIODevice::ReadOnly);
    QTextStream in(file);
    info = in.readAll();
    contains = info.split(";").at(0);
    judge = info.split(";").at(1).toInt();
    h1 = info.split(";").at(2).split(",").at(0).toInt();
    m1 = info.split(";").at(2).split(",").at(1).toInt();
    h2 = info.split(";").at(3).split(",").at(0).toInt();
    m2 = info.split(";").at(3).split(",").at(1).toInt();
    file->close();
}

void MainWindow::closeEvent(QCloseEvent *event)//关闭按钮函数
{
    this->hide();
    event->ignore();
}

void MainWindow::iconActivied(QSystemTrayIcon::ActivationReason reason)//图标对按钮的响应函数
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:showSlot();break;
    case QSystemTrayIcon::DoubleClick:showSlot();break;
    default:break;
    }
}

void MainWindow::creatActions()//事件关联函数
{
    quitAction = new QAction("Quit", this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    setAction = new QAction("Setting",this);
    connect(setAction ,SIGNAL(triggered()),this,SLOT(setSlot()));
}

void MainWindow::creatMenu()//菜单生成函数
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(setAction);
    trayIconMenu->addAction(quitAction);
    tray->setContextMenu(trayIconMenu);
}

void MainWindow::showSlot()//主窗口弹出函数
{
    ui->timeEdit->setTime(QTime::currentTime());
    this->show();
}

int MainWindow::ShowMessage()//通知提示函数
{
    readTxt();
    systemTime = QDateTime::currentDateTime();
    QString week = systemTime.toString("dddd");

    if(contains.contains(week.at(2)))
    {
        QTime n1(h1,m1,0);
        i = QTime::currentTime().secsTo(n1);
        shutdownString = ".Power will be off at "+QString::number(h1)+":"+QString::number(m1)+"; ";
        command = "shutdown -s -t " + QString::number(i);
        p.execute(command);
    }
    else
    {
        if(judge == 0)
        {
            QTime n2(h2,m2,0);
            i = QTime::currentTime().secsTo(n2);
            shutdownString = ".Power will be off at "+QString::number(h2)+":"+QString::number(m2)+"; ";
            command = "shutdown -s -t " + QString::number(i);
            p.execute(command);
        }
        else
        {
            p.execute("shutdown -a");
            tray->showMessage("PowerSet","There is no plan for today.",QSystemTrayIcon::Information,1500);
            return 0;
        }
    }



    int seconds,minutes,hours;
    seconds = i;
    hours = seconds / 3600;
    minutes = (seconds - 3600*hours)/60;
    seconds = (seconds - 3600*hours - 60*minutes);

    tray->showMessage("PowerSet","Today is "+systemTime.toString("dddd")+shutdownString
                      +QString::number(hours)+" hours, "+QString::number(minutes)+" minutes, "
                      +QString::number(seconds)+" seconds left.",QSystemTrayIcon::Information,2000);
    return 1;
}

void MainWindow::setPlan()//计划重置函数
{
    p.execute("shutdown -a");
    int seconds,minutes,hours;
    QTime time = ui->timeEdit->time();
    seconds = QTime::currentTime().secsTo(time);
    p.execute("shutdown -s -t " + QString::number(seconds));

    hours = seconds / 3600;
    minutes = (seconds - 3600*hours)/60;
    seconds = (seconds - 3600*hours - 60*minutes);


    tray->showMessage("RePlan","Mission Replaned.System will shutdown in "+
                      QString::number(hours)+" hours, "+QString::number(minutes)+" minutes, "
                      +QString::number(seconds)+" seconds from now on.",QSystemTrayIcon::Information,1000);
    this->hide();
}

void MainWindow::CancelSlot()//计划取消函数
{
    p.execute("shutdown -a");
    tray->showMessage("Cancel","Mission Canceled!",QSystemTrayIcon::Information,1000);
    this->hide();
}

void MainWindow::setSlot()//弹出设置界面
{

   w->show();
}
