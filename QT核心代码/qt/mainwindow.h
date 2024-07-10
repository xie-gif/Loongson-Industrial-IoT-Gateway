#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <widg.h>
#include <QVBoxLayout>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QFile>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QChartView>
#include <QLineSeries>
//#include <QtCharts/QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QtCharts/QLogValueAxis>
using namespace QtCharts;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer; // 添加 QTimer 指针
    QThread *timerThread; // 添加 QThread 指针
    QSerialPort *uers ;
     QChart *chart;
   QtCharts::QLineSeries *ses;
   QLineSeries *zxd;

    void initializeTimer();
     void updateTime();
     void onButtonClicked();

     int8_t size_bit=0;
     int16_t time_sun=0;
     int8_t ntime_f=0;
     int8_t ntime_s=0;
     QChartView * chartvie;
     QValueAxis *yAxis;
     QValueAxis *xAxis;
     QLineSeries *series =new QLineSeries();
     QDateTimeAxis *XAxis = new QDateTimeAxis();
//     QValueAxis *XAxis=new QValueAxis();
      QPointF point;
      int16_t MAX_bit;


private slots:
     void on_comboBox_currentIndexChanged(int index);
     void showPopupTextEdit(QPlainTextEdit *textEdit) ;
     void updateCheckStates(int state) ;

private:
    Ui::MainWindow *ui;
    widg *hhj;
    QVBoxLayout * bj;
    QMainWindow * ztl;
};
#endif // MAINWINDOW_H
