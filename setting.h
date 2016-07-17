#ifndef SETTING_H
#define SETTING_H

#include <QMainWindow>


namespace Ui {
class Setting;
}

class Setting : public QMainWindow
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = 0);
    ~Setting();

signals:
    void dlgRturn(bool set);

private:
    Ui::Setting *ui;
    bool edit;
    QString days,info;
    void repeatDays();

private slots:
    void applySlot();
    void okSlot();

    void readTxt();
    void writeTxt(QString s);
};

#endif // SETTING_H
