#include "queryandalter.h"
#include "ui_queryandalter.h"
#include <QMessageBox>
#include <QDebug>
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QTextStream>
#include <mainwindow.h>

queryAndAlter::queryAndAlter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::queryAndAlter)
{
    ui->setupUi(this);


    if(readFromFile() == -1){
        QMessageBox::critical(this, "ERROR","文件打开失败");
        this->close();
    }

    this->model = new QStandardItemModel;

    //设置表头
    this->model->setVerticalHeaderItem(0,new QStandardItem("主题"));
    this->model->setVerticalHeaderItem(1,new QStandardItem("开始时间"));
    this->model->setVerticalHeaderItem(2,new QStandardItem("结束时间"));
    this->model->setVerticalHeaderItem(3,new QStandardItem("提醒时间"));
    this->model->setVerticalHeaderItem(4,new QStandardItem("地点"));
    this->model->setVerticalHeaderItem(5,new QStandardItem("备注"));
    this->model->setVerticalHeaderItem(6,new QStandardItem("时区"));

    this->ui->tableView->setModel(model);

    this->ui->tableView->setRowHeight(0,72);
    this->ui->tableView->setRowHeight(1,72);
    this->ui->tableView->setRowHeight(2,72);
    this->ui->tableView->setRowHeight(3,72);
    this->ui->tableView->setRowHeight(4,72);
    this->ui->tableView->setRowHeight(5,72);
    this->ui->tableView->setRowHeight(6,72);

    this->ui->tableView->setColumnWidth(1,500);
}

queryAndAlter::~queryAndAlter()
{
    delete ui;
}

void queryAndAlter::on_tableView_doubleClicked(const QModelIndex &index)
{
    QAbstractItemModel *imodel = this->ui->tableView->model();
    QString name = imodel->data(model->index(0,0)).toString();
    qDebug() << name;
    QString the = index.data().toString();
    qDebug() << the;                 //改变后的值
    QStringList subss = doQuery2(name);
    int r = index.row();
    qDebug() << r;

    int namelen = name.length();
    QString a = imodel->data(model->index(3,0)).toString();  //remindlen
    int re = a.length();
    QString b = imodel->data(model->index(4,0)).toString();  //locationlen
    int lo = b.length();
    QString c = imodel->data(model->index(5,0)).toString();  //tiplen
//    int ti = c.length();

    qDebug() << theOrigin;
    writeToFile(r, theOrigin, the, namelen, re, lo, n);
}

QStringList queryAndAlter::doQuery2(QString th)
{
    int i;
    for (i = 0;i < date_lines.length();i++) {
        QString line = date_lines.at(i);
        line = line.trimmed();                        //去除开头结尾空白字符串
        QStringList subs = line.split(' ');
        if(th == subs.at(0)) {
            return subs;
        }
    }
    QMessageBox::critical(this, "ERROR", "未找到相应主题的日程！", "确定");
}

int queryAndAlter::doQuery3(QString th)
{
    int i;
    for (i = 0;i < date_lines.length();i++) {
        QString line = date_lines.at(i);
        line = line.trimmed();                        //去除开头结尾空白字符串
        QStringList subs = line.split(' ');
        if(th == subs.at(0)) {
            qDebug() << i;
            qDebug() <<"这里是行数";
            return i;         
        }
    }
    QMessageBox::critical(this, "ERROR", "未找到相应主题的日程！", "确定");
}

void queryAndAlter::doQuery(QString th)
{
    int i;
    for (i = 0;i < date_lines.length();i++) {
        QString line = date_lines.at(i);
        line = line.trimmed();                        //去除开头结尾空白字符串
        QStringList subs = line.split(' ');
        if(th == subs.at(0)){
            display(subs);
        }
    }
}

int queryAndAlter::readFromFile()
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
        qDebug() << date_lines.at(i);
    }
    return 0;
}

void queryAndAlter::display(QStringList t)
{
    this->model->setItem(0, 0, new QStandardItem(t.at(0)));
    this->model->setItem(1, 0, new QStandardItem(t.at(1) + " " + t.at(2) + " " + t.at(3) + " " + t.at(4) + " " + t.at(5)));
    this->model->setItem(2, 0, new QStandardItem(t.at(6) + " " + t.at(7) + " " + t.at(8) + " " + t.at(9) + " " + t.at(10)));
    this->model->setItem(3, 0, new QStandardItem(t.at(11)));
    this->model->setItem(4, 0, new QStandardItem(t.at(12)));
    this->model->setItem(5, 0, new QStandardItem(t.at(13)));
    this->model->setItem(6, 0, new QStandardItem(t.at(14)));
}

void queryAndAlter::on_pushButton_clicked()
{
    this->model->clear();
    this->model->setVerticalHeaderItem(0,new QStandardItem("主题"));
    this->model->setVerticalHeaderItem(1,new QStandardItem("开始时间"));
    this->model->setVerticalHeaderItem(2,new QStandardItem("结束时间"));
    this->model->setVerticalHeaderItem(3,new QStandardItem("提醒时间"));
    this->model->setVerticalHeaderItem(4,new QStandardItem("地点"));
    this->model->setVerticalHeaderItem(5,new QStandardItem("备注"));
    this->model->setVerticalHeaderItem(6,new QStandardItem("时区"));

    this->ui->tableView->setRowHeight(0,72);
    this->ui->tableView->setRowHeight(1,72);
    this->ui->tableView->setRowHeight(2,72);
    this->ui->tableView->setRowHeight(3,72);
    this->ui->tableView->setRowHeight(4,72);
    this->ui->tableView->setRowHeight(5,72);
    this->ui->tableView->setRowHeight(6,72);

    this->ui->tableView->setColumnWidth(1,500);
    QString th = this->ui->lineEdit->text();
    doQuery(th);
    n = doQuery3(th);
}

void queryAndAlter::writeToFile(int index, QString cnt, QString cnt2, int themeLen, int remindLen, int locationLen, int n)
{
    flag2++;
    if(flag2 != 1){
    QFile writeFile("date.txt");
    QString tempStr;
    if(writeFile.open(QIODevice::WriteOnly|QIODevice::Text)) {
        for(int i = 0;i < date_lines.length();i++) {
            tempStr = date_lines.at(i);
            if(i == n) {
                if(date_lines.at(n).contains(cnt)) {
                    tempStr.replace(cnt,cnt2);
                    qDebug() <<  "你大爷永远是你大爷";
                    qDebug() << tempStr;
                    qDebug() <<  "你大爷永远是你大爷";
                    writeFile.close();
                    deleteOnelineInFile(n);
                    qDebug() << n;
                    qDebug() << "这里是修改";
                    qDebug() << strall;
                    qDebug() << "这里是修改";
                    break;
                }
            }
        }
   }

    QFile file("date.txt");
    if(! file.open(QIODevice::Append | QIODevice::Text)) {
            QMessageBox::critical(this, "ERROR","文件打开失败");
            return;
    }
    QTextStream out(&file);
    out << tempStr + '\n';
    file.close();
}
//                QString tempStr=date_lines.at(i);
//                if(index == 0) {
//                    tempStr.replace(0, cnt.length(), cnt2);
//                } else if(index == 1) {
//                    tempStr.replace(themeLen, cnt.length(), cnt2);
//                } else if(index == 2) {
//                    tempStr.replace(themeLen + 19, cnt.length(), cnt2);
//                } else if(index == 3) {
//                    tempStr.replace(themeLen + 36, cnt.length(), cnt2);
//                } else if(index == 4) {
//                    tempStr.replace(themeLen + 37 + remindLen , cnt.length(), cnt2);
//                } else if(index == 5) {
//                    tempStr.replace(themeLen + 37 + remindLen + locationLen, cnt.length(), cnt2);
//                } else if(index == 6) {
//                    tempStr.replace(themeLen + 37 + remindLen + locationLen + tipLen, cnt.length(), cnt2);
//                }
//                stream << tempStr << '\n';

}

void queryAndAlter::on_tableView_clicked(const QModelIndex &index)
{
    flag += 1;
    if(flag == 1){
        theOrigin = index.data().toString();
    }
    qDebug() << "qt";
    qDebug() << theOrigin;
    qDebug() << "qt2";
}

void queryAndAlter::on_btn_delete_clicked()
{
    deleteOnelineInFile(n);
    QMessageBox::information(this, "Congratulation","日程已删除！没有后悔药了！");
    this->model->clear();
    MainWindow m;
    m.adjustSize();
}

void queryAndAlter::DeleteOneline(int nn)
{
    qDebug() << "删除成功2";
    qDebug() << nn;
    int nLine=0;
    int Index=0;
    //算出行数nLine
    while(Index!=-1) {
        Index=strall.indexOf('\n',Index+1);
        nLine++;
    }

    if(nn==0) {
        int nIndex=strall.indexOf('\n');
        strall.remove(0,nIndex+1);
        qDebug() << "删除成功1";
    }
    else {
        int nTemp=nn;
        int nIndex=0,nIndex2=0;
        while(nTemp--) {
            nIndex=strall.indexOf('\n',nIndex+1);//这里会更新nIndex
            if(nIndex!=-1) {                   //说明是有效的
                nIndex2=strall.indexOf('\n',nIndex+1);
            }
        }
        //删除的行不是最后一行（从nIndex+1这个位置起nIndex2-nIndex个字符全部抹去）
        if(nn < nLine-1) {
            strall.remove(nIndex+1, nIndex2-nIndex);//不用减一
        }
        //删除的是最后一行（从nIndex起始len-nIndex个字符全抹去）
        //不能从nIndex+1处开始，
        else if(nn == nLine-1) {
            int len=strall.length();
            strall.remove(nIndex,len-nIndex);
        }
    }
}

void queryAndAlter::deleteOnelineInFile(int nNumLine)
{
    QFile readfile("date.txt");
    if(readfile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&readfile);
        strall=stream.readAll();
        qDebug() << "这里是删除一行";
        qDebug() << strall;
        qDebug() << "这里是删除一行";
    }
    readfile.close();
    DeleteOneline(nNumLine);

    QFile writefile("date.txt");
    if(writefile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream wrtstream(&writefile);
        wrtstream<<strall;
    }
    writefile.close();
}

void queryAndAlter::closeEvent(QCloseEvent *event)
{
    int choose;
    choose= QMessageBox::question(this, tr("Exit"), QString(tr("Are you sure you want to exit?")), QMessageBox::Yes | QMessageBox::No);
    if (choose== QMessageBox::No) {
        event->ignore();
    } else if (choose== QMessageBox::Yes) {
        MainWindow m;
        m.repaint();
        event->accept();
    }
}



