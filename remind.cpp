#include "remind.h"
#include "ui_remind.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>

remind::remind(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::remind)
{
    ui->setupUi(this);

    connect(&this->ptimer0 , SIGNAL(timeout()), this, SLOT(updateDateTimeAndDisplay0()));
    connect(&this->ptimer1 , SIGNAL(timeout()), this, SLOT(updateDateTimeAndDisplay1()));
    connect(&this->ptimer2 , SIGNAL(timeout()), this, SLOT(updateDateTimeAndDisplay2()));
    connect(&this->ptimer3 , SIGNAL(timeout()), this, SLOT(updateDateTimeAndDisplay3()));
    connect(&this->ptimer4 , SIGNAL(timeout()), this, SLOT(updateDateTimeAndDisplay4()));
    connect(&this->ptimer5 , SIGNAL(timeout()), this, SLOT(updateDateTimeAndDisplay5()));

    if(readFromFile() == -1) {
        QMessageBox::critical(this, "ERROR","文件打开失败");
        this->close();
    }

    QDateTime current = QDateTime::currentDateTime();
    QString cur = current.toString("yyyy MM dd");       //当前日期

    int i;
    qDebug() << cur;

    for (i = 0;i < date_lines.length();i++) {         //遍历所有日程
        QString line = date_lines.at(i);              //一行的日程
        line = line.trimmed();                              //去除开头结尾空白字符串
        QStringList subs = line.split(' ');           //标准化
        QString date = subs.at(1) + " " + subs.at(2) + " " + subs.at(3);  //日程中的几年几月几日
        QString time = subs.at(4) + " " + subs.at(5);
        if(date == cur) {                                      //如果日期吻合
            if(subs.at(11) == "活动开始前") {
                this->baseTime = QTime::currentTime();
                this->ptimer0.start(1);
                this->ui->label->setText("主题：" + subs.at(0));
                this->ui->label_2->setText("地点：" + subs.at(12));
                this->ui->label_3->setText("备注：" + subs.at(13));
            }else if (subs.at(11) == "5分钟前") {
                this->baseTime = QTime::currentTime();
                this->ptimer1.start(1);
                this->ui->label->setText("主题：" + subs.at(0));
                this->ui->label_2->setText("地点：" + subs.at(12));
                this->ui->label_3->setText("备注：" + subs.at(13));
            }else if (subs.at(11) == "10分钟前") {
                this->baseTime = QTime::currentTime();
                this->ptimer2.start(1);
                this->ui->label->setText("主题：" + subs.at(0));
                this->ui->label_2->setText("地点：" + subs.at(12));
                this->ui->label_3->setText("备注：" + subs.at(13));
            }else if (subs.at(11) == "15分钟前") {
                this->baseTime = QTime::currentTime();
                this->ptimer3.start(1);
                this->ui->label->setText("主题：" + subs.at(0));
                this->ui->label_2->setText("地点：" + subs.at(12));
                this->ui->label_3->setText("备注：" + subs.at(13));
            }else if (subs.at(11) == "30分钟前") {
                this->baseTime = QTime::currentTime();
                this->ptimer4.start(1);
                this->ui->label->setText("主题：" + subs.at(0));
                this->ui->label_2->setText("地点：" + subs.at(12));
                this->ui->label_3->setText("备注：" + subs.at(13));
            }else if (subs.at(11) == "1小时前") {
                this->baseTime = QTime::currentTime();
                this->ptimer5.start(1);
                this->ui->label->setText("主题：" + subs.at(0));
                this->ui->label_2->setText("地点：" + subs.at(12));
                this->ui->label_3->setText("备注：" + subs.at(13));
            }
        }
    }
}

remind::~remind()
{
    delete ui;
}

void remind::updateDateTimeAndDisplay0()
{
    QTime current = QTime::currentTime();
    int t = this->baseTime.msecsTo(current);
    qDebug() << "差值t：" << t;
    QTime showTime(0,0,10,0);
    showTime = showTime.addMSecs(-t);
    qDebug() << "showTime: " << showTime;
    showStr = showTime.toString("hh:mm:ss:zzz");
    this->ui->lcdNumber->display(showStr);
    if(t == 10000) {
        int choose;
        choose= QMessageBox::question(this, tr("提醒"), QString(tr("快去做你的事去吧")), QMessageBox::Yes | QMessageBox::No);
        if (choose == QMessageBox::No) {
            int choose2 = QMessageBox::question(this, tr("提醒"), QString(tr("安排有变?")), QMessageBox::Yes | QMessageBox::No);
            if(choose2 == QMessageBox::Yes) {
                this->close();
            }else {
                QMessageBox::question(this, tr("提醒"), QString(tr("那就赶紧去做！")), QMessageBox::Yes);
                this->close();
            }
        } else if (choose == QMessageBox::Yes) {
            this->close();
        }
    }
}

void remind::updateDateTimeAndDisplay1() {
    QTime current = QTime::currentTime();
    int t = this->baseTime.msecsTo(current);
    qDebug() << "差值t：" << t;
    QTime showTime(0,5,0,0);
    showTime = showTime.addMSecs(-t);
    qDebug() << "showTime: " << showTime;
    showStr = showTime.toString("hh:mm:ss:zzz");
    this->ui->lcdNumber->display(showStr);
    if(t == 300000) {
        int choose;
        choose= QMessageBox::question(this, tr("提醒"), QString(tr("快去做你的事去吧")), QMessageBox::Yes | QMessageBox::No);
        if (choose == QMessageBox::No) {
            int choose2 = QMessageBox::question(this, tr("提醒"), QString(tr("安排有变?")), QMessageBox::Yes | QMessageBox::No);
            if(choose2 == QMessageBox::Yes) {
                this->close();
            }else {
                QMessageBox::question(this, tr("提醒"), QString(tr("那就赶紧去做！")), QMessageBox::Yes);
                this->close();
            }
        } else if (choose == QMessageBox::Yes) {
            this->close();
        }
    }
}
void remind::updateDateTimeAndDisplay2()
{
    QTime current = QTime::currentTime();
    int t = this->baseTime.msecsTo(current);
    qDebug() << "差值t：" << t;
    QTime showTime(0,10,0,0);
    showTime = showTime.addMSecs(-t);
    qDebug() << "showTime: " << showTime;
    showStr = showTime.toString("hh:mm:ss:zzz");
    this->ui->lcdNumber->display(showStr);
    if(t == 600000) {
        int choose;
        choose= QMessageBox::question(this, tr("提醒"), QString(tr("快去做你的事去吧")), QMessageBox::Yes | QMessageBox::No);
        if (choose == QMessageBox::No) {
            int choose2 = QMessageBox::question(this, tr("提醒"), QString(tr("安排有变?")), QMessageBox::Yes | QMessageBox::No);
            if(choose2 == QMessageBox::Yes) {
                this->close();
            }else {
                QMessageBox::question(this, tr("提醒"), QString(tr("那就赶紧去做！")), QMessageBox::Yes);
                this->close();
            }
        } else if (choose == QMessageBox::Yes) {
            this->close();
        }
    }
}

void remind::updateDateTimeAndDisplay3() {
    QTime current = QTime::currentTime();
    int t = this->baseTime.msecsTo(current);
    qDebug() << "差值t：" << t;
    QTime showTime(0,15,0,0);
    showTime = showTime.addMSecs(-t);
    qDebug() << "showTime: " << showTime;
    showStr = showTime.toString("hh:mm:ss:zzz");
    this->ui->lcdNumber->display(showStr);
    if(t == 900000) {
        int choose;
        choose= QMessageBox::question(this, tr("提醒"), QString(tr("快去做你的事去吧")), QMessageBox::Yes | QMessageBox::No);
        if (choose == QMessageBox::No) {
            int choose2 = QMessageBox::question(this, tr("提醒"), QString(tr("安排有变?")), QMessageBox::Yes | QMessageBox::No);
            if(choose2 == QMessageBox::Yes) {
                this->close();
            }else {
                QMessageBox::question(this, tr("提醒"), QString(tr("那就赶紧去做！")), QMessageBox::Yes);
                this->close();
            }
        } else if (choose == QMessageBox::Yes) {
            this->close();
        }
    }
}
void remind::updateDateTimeAndDisplay4()
{
    QTime current = QTime::currentTime();
    int t = this->baseTime.msecsTo(current);
    qDebug() << "差值t：" << t;
    QTime showTime(0,30,0,0);
    showTime = showTime.addMSecs(-t);
    qDebug() << "showTime: " << showTime;
    showStr = showTime.toString("hh:mm:ss:zzz");
    this->ui->lcdNumber->display(showStr);
    if(t == 1800000) {
        int choose;
        choose= QMessageBox::question(this, tr("提醒"), QString(tr("快去做你的事去吧")), QMessageBox::Yes | QMessageBox::No);
        if (choose == QMessageBox::No) {
            int choose2 = QMessageBox::question(this, tr("提醒"), QString(tr("安排有变?")), QMessageBox::Yes | QMessageBox::No);
            if(choose2 == QMessageBox::Yes) {
                this->close();
            }else {
                QMessageBox::question(this, tr("提醒"), QString(tr("那就赶紧去做！")), QMessageBox::Yes);
                this->close();
            }
        } else if (choose == QMessageBox::Yes) {
            this->close();
        }
    }
}

void remind::updateDateTimeAndDisplay5() {
    QTime current = QTime::currentTime();
    int t = this->baseTime.msecsTo(current);
    qDebug() << "差值t：" << t;
    QTime showTime(1,0,0,0);
    showTime = showTime.addMSecs(-t);
    qDebug() << "showTime: " << showTime;
    showStr = showTime.toString("hh:mm:ss:zzz");
    this->ui->lcdNumber->display(showStr);
    if(t == 3600000) {
        int choose;
        choose= QMessageBox::question(this, tr("提醒"), QString(tr("快去做你的事去吧")), QMessageBox::Yes | QMessageBox::No);
        if (choose == QMessageBox::No) {
            int choose2 = QMessageBox::question(this, tr("提醒"), QString(tr("安排有变?")), QMessageBox::Yes | QMessageBox::No);
            if(choose2 == QMessageBox::Yes) {
                this->close();
            }else {
                QMessageBox::question(this, tr("提醒"), QString(tr("那就赶紧去做！")), QMessageBox::Yes);
                this->close();
            }
        } else if (choose == QMessageBox::Yes) {
            this->close();
        }
    }
}

void remind::on_btn_cancel_clicked()
{
    int choose;
    choose= QMessageBox::question(this, tr("取消"), QString(tr("你确定要取消吗?")), QMessageBox::Yes | QMessageBox::No);
    if (choose == QMessageBox::Yes) {
        int choose2 = QMessageBox::question(this, tr("取消"), QString(tr("你真的确定不会忘记吗?")), QMessageBox::Yes | QMessageBox::No);
        if(choose2 == QMessageBox::Yes) {
            this->ui->lcdNumber->display("00:00:00:000");
            this->close();
        }
    } else if (choose == QMessageBox::No) {
        //do nothing
    }
}

int remind::readFromFile()
{
    QFile file("date.txt");
    if(! file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        date_lines.append(line);
    }
    file.close();
    int i;
    for (i = 0;i < date_lines.length();i++) {
        qDebug() << date_lines.at(i);                //输出所有日程安排
    }
    return 0;
}
