#include "setting.h"
#include "ui_setting.h"
#include <QDir>
#include <QFile>
#include <QTextStream>

Setting::Setting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    this->setWindowTitle("Settings");
    this->setMaximumSize(543,441);
    this->setMinimumSize(543,441);
    readTxt();
    connect(ui->applyButton,SIGNAL(clicked()),this,SLOT(applySlot()));
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(okSlot()));
}

Setting::~Setting()
{
    delete ui;
}

void Setting::repeatDays()
{

    if(ui->mon->isChecked())
        days += "一";
    if(ui->tus->isChecked())
        days += "二";
    if(ui->wen->isChecked())
        days += "三";
    if(ui->thr->isChecked())
        days += "四";
    if(ui->fri->isChecked())
        days += "五";
    if(ui->sat->isChecked())
        days += "六";
    if(ui->sun->isChecked())
        days += "日";
    if(ui->Enable->isChecked())
        days += ";0";
    else
        days += ";1";
    days += ";"+ui->chosen->time().toString("hh,mm")+";"
            +ui->Else->time().toString("hh,mm");



    if(info != days)
    {
        writeTxt(days);
        edit = true ;
    }
    else
        edit = false;
    days = "";
    emit dlgRturn(edit);
}

void Setting::applySlot()
{
    repeatDays();
}

void Setting::okSlot()
{
    repeatDays();
    this->hide();
}

void Setting::readTxt()
{
    QFile *file = new QFile;
    file->setFileName(QDir::currentPath()+"\\set.txt");
    file->open(QIODevice::ReadOnly);

    QTextStream in(file);
    info = in.readAll();

    file->close();

    if(info.contains("日"))
        ui->sun->setChecked(true);
    if(info.contains("一"))
        ui->mon->setChecked(true);
    if(info.contains("二"))
        ui->tus->setChecked(true);
    if(info.contains("三"))
        ui->wen->setChecked(true);
    if(info.contains("四"))
        ui->thr->setChecked(true);
    if(info.contains("五"))
        ui->fri->setChecked(true);
    if(info.contains("六"))
        ui->sat->setChecked(true);

    if(info.split(";").at(1)=="0")
        ui->Enable->setChecked(true);

    QTime t1 = QTime::fromString(info.split(";").at(2),"hh,mm");
    QTime t2 = QTime::fromString(info.split(";").at(3),"hh,mm");

    ui->chosen->setTime(t1);
    ui->Else->setTime(t2);

}

void Setting::writeTxt(QString s)
{
    QFile *file = new QFile;
    file->setFileName(QDir::currentPath()+"\\set.txt");
    file->open(QIODevice::WriteOnly);

    QTextStream in(file);
    in<<s;
    file->close();
}
