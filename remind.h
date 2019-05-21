#ifndef REMIND_H
#define REMIND_H

#include <QDialog>
#include <QString>
#include <QTime>
#include <QTimer>

namespace Ui {
class remind;
}

class remind : public QDialog
{
    Q_OBJECT

public:
    explicit remind(QWidget *parent = nullptr);
    ~remind();

    void cool();           //计时器启动

private slots:
    void on_btn_cancel_clicked();

    int readFromFile();

    void updateDateTimeAndDisplay0();
    void updateDateTimeAndDisplay1();
    void updateDateTimeAndDisplay2();
    void updateDateTimeAndDisplay3();
    void updateDateTimeAndDisplay4();
    void updateDateTimeAndDisplay5();

private:
    Ui::remind *ui;
    QString h;
    QString m;
    QString s;
    QList<QString> date_lines;
    QTimer ptimer0;
    QTimer ptimer1;
    QTimer ptimer2;
    QTimer ptimer3;
    QTimer ptimer4;
    QTimer ptimer5;
    QTime baseTime;
    QString showStr;
    int t = 0;
};

#endif // REMIND_H
