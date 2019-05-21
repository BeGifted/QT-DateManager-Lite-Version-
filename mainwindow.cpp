#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QWidget>
#include <QShowEvent>
#include <adddate.h>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QFileSystemWatcher>
#include <remind.h>
#include <queryandalter.h>
#include <dialog2.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //主界即时更新 todo
    QFileSystemWatcher * fc = new QFileSystemWatcher;
    connect(fc,  SIGNAL(fileChanged(:/date.txt)), this, SLOT(filechange()));

    if(readFromFile() == -1){
        QMessageBox::critical(this, "ERROR","文件打开失败");
        this->close();
    }

    //qDebug() << cur;

    //动态获取时间
    myTimer = new QTimer(this);
    myTimer->start(1000);
    connect(myTimer, SIGNAL(timeout()), this, SLOT(GetDateTime()));


    this->setWindowTitle("日程管理提醒系统");
    this->setWindowIcon(QIcon(":/ico/date.ico"));

    this->model = new QStandardItemModel;

    //设置表头
    this->model->setHorizontalHeaderItem(0,new QStandardItem("主题"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("地点"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("备注"));

    this->ui->tableView->setModel(model);

    this->ui->tableView->setColumnWidth(0,175);
    this->ui->tableView->setColumnWidth(1,180);
    this->ui->tableView->setColumnWidth(2,180);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GetDateTime()           //获取动态时间
{
    QDateTime current = QDateTime::currentDateTime();
    QString cur_y = current.toString("yyyy");       //当前日期
    QString cur_m = current.toString("MM");
    QString cur_d = current.toString("dd");

    QTime current1 =QTime::currentTime();
    QString cur1 = current1.toString("hh mm ss");

    qDebug() << "当前时间：" << current1;
    //h,m,s为当前时间
    QString h = current1.toString("hh");
    QString m = current1.toString("mm");
    QString s = current1.toString("ss");

    this->baseTime = QTime::currentTime();

    int i;
    for (i = 0;i < date_lines.length();i++) {         //遍历所有日程
        QString line = date_lines.at(i);              //一行的日程
        line = line.trimmed();                              //去除开头结尾空白字符串
        QStringList subs = line.split(' ');           //标准化

        QString time = subs.at(4) + " " + subs.at(5) + " 00";
        //qDebug() << time;
        QTime time1;
        time1 = QTime::fromString(time, "hh mm ss");    //日程中的时间转换为qtime
        if(subs.at(1) == cur_y&&subs.at(2) == cur_m &&subs.at(3) == cur_d) {       //当天日期吻合
            qDebug() << "日期吻合";
            qDebug() << "当前时间增加10秒：" << current1.addSecs(10) ;
            qDebug() << "抓取到的符合时间：" << time1;
            if(current1.addSecs(10).toString() == time1.toString()) {                            //活动开始前
                qDebug() << "提醒时间到了！！！";
                remind l;
                l.exec();
            }else if (current1.addSecs(300).toString() == time1.toString()) {               //前5分钟
                remind l;
                l.exec();
            }else if (current1.addSecs(600).toString() == time1.toString()) {                //前10分钟
                remind l;
                l.exec();
            }else if (current1.addSecs(900).toString() == time1.toString()) {                //前15分钟
                remind l;
                l.exec();
            }else if (current1.addSecs(1800).toString() == time1.toString()) {               //前30分钟
                remind l;
                l.exec();
            }else if (current1.addSecs(3600).toString() == time1.toString()) {               //前1小时
                remind l;
                l.exec();
            }
        }
    }
}

void MainWindow::on_action_A_2_triggered()
{
    addDate a;
    a.exec();
}

void MainWindow::on_action_H_triggered()
{
    QMessageBox::aboutQt(this, "鸣谢");
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    //调用doquery -> display
    this->model->clear();
    this->model->setHorizontalHeaderItem(0,new QStandardItem("主题"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("地点"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("备注"));

    this->ui->tableView->setColumnWidth(0,175);
    this->ui->tableView->setColumnWidth(1,180);
    this->ui->tableView->setColumnWidth(2,180);

    QString cnt = date.toString("yyyy MM dd");
    qDebug() << cnt;
    doQuery(cnt);
}

void MainWindow::doQuery(QString cnt)  //cnt为点击tableview的日期
{
    int i, row = 0;
    for (i = 0;i < date_lines.length();i++) {
        QString line = date_lines.at(i);
        line = line.trimmed();      //去除开头结尾空白字符串
        QStringList subs = line.split(' ');
        if(cnt.left(4) == subs.at(1)&&cnt.mid(5,2) == subs.at(2)&&cnt.right(2) == subs.at(3)){
            display(row++, subs);
        }
    }
}

int MainWindow::readFromFile()
{
    QFile file("date.txt");
    if(! file.open(QIODevice::ReadWrite | QIODevice::Text)){
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
        qDebug() << date_lines.at(i);
    }
    return 0;
}

void MainWindow::display(int row, QStringList t)
{
    this->model->setItem(row, 0, new QStandardItem(t.at(0)));
    this->model->setItem(row, 1, new QStandardItem(t.at(12)));
    this->model->setItem(row, 2, new QStandardItem(t.at(13)));
}

void MainWindow::filechange()
{
    MainWindow s;
    s.show();
}

void MainWindow::on_actiona_triggered()
{
    queryAndAlter q;
    q.exec();
}

void MainWindow::on_action_S_triggered()
{
    Dialog2 d;
    d.exec();
}
