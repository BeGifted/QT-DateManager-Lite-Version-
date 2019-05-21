#ifndef QUERYANDALTER_H
#define QUERYANDALTER_H

#include <QDialog>
#include <QStandardItemModel>
#include <QString>
#include <QList>
#include <QFile>
#include <QStandardItem>
#include <QTimer>

namespace Ui {
class queryAndAlter;
}

class queryAndAlter : public QDialog
{
    Q_OBJECT

public:
    explicit queryAndAlter(QWidget *parent = nullptr);
    ~queryAndAlter();
    int readFromFile();
    void display(QStringList t);
    void doQuery(QString cnt);
    QStringList doQuery2(QString cnt);
    void writeToFile(int index, QString cnt, QString cnt2, int themeLen, int remindLen, int locationLen, int n);
    int doQuery3(QString th);
    void DeleteOneline(int nn);
    void deleteOnelineInFile(int nNumLine);
    void closeEvent(QCloseEvent *event);

    int n, flag2 = 0;
    QString strall;

public slots:


private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();


    void on_tableView_clicked(const QModelIndex &index);



    void on_btn_delete_clicked();

private:
    Ui::queryAndAlter *ui;
    QStandardItemModel * model;
    QList<QString> date_lines;
    QString theOrigin;
    QString theOOrigin;
    int flag = 0;



};

#endif // QUERYANDALTER_H
