#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMenuBar>
#include <QToolBar>
#include <QLabel>
#include <QMovie>
#include <QPixmap>
#include <QWidget>
#include <QFrame>
#include <widg.h>
#include <QPainter>
#include <QVBoxLayout>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QToolBox>
#include <QString>
#include <QPushButton>
#include <QScreen>
#include <QApplication>
#include <QWidget>
#include <QApplication>
#include <QDateTime>
#include <QButtonGroup>
#include <QPushButton>
#include <QFile>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QChartView>
#include <QComboBox>
#include <QDateTimeAxis>
#include <QPointF>
#include "chke.h"
#include <QCheckBox>

//class TextEditEventFilter : public QObject {
//    Q_OBJECT
//public:
//    TextEditEventF    // 这里可以添加代码来显示一个模态对话框或另一个界面元素
// 例如，创建一个新的 QPlainTextEdit 并设置其文本为被点击文本框的文本ilter(QObject *parent = nullptr) : QObject(parent) {}

//protected:
//    bool eventFilter(QObject *obj, QEvent *event) override {
//        if (event->type() == QEvent::MouseButtonPress) {
//            QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit *>(obj);
//            if (textEdit) {
//                emit textEditClicked(textEdit);
//                return true; // 事件已处理
//            }
//        }
//        return QObject::eventFilter(obj, event);
//    }
//signals:
//    void textEditClicked(QPlainTextEdit *textEdit);
//};


bool a=false;
int b=0;
    QButtonGroup get;
     MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,timer(new QTimer(this))
{
    ui->setupUi(this);
    uers = new QSerialPort(this);
    uers->setPortName("/dev/ttyS7");
    QTabWidget *tabWi = new QTabWidget;
    QWidget *chartCon=new QWidget();
    QWidget *chartCOn1=new QWidget();
    QVBoxLayout *chartL1=new QVBoxLayout(chartCOn1);
    QVBoxLayout *chartL=new QVBoxLayout(chartCon);

    TextEditEventFilter * chek = new  TextEditEventFilter(this);
    ui->UART->setTextInteractionFlags(Qt::NoTextInteraction);
    ui->CAN->setTextInteractionFlags(Qt::NoTextInteraction);
    ui->Rs485->setTextInteractionFlags(Qt::NoTextInteraction);


    ui->UART->installEventFilter(chek);
    ui->CAN->installEventFilter(chek);
    ui->Rs485->installEventFilter(chek);
    ui->UART->setPlaceholderText("UART");
    ui->CAN->setPlaceholderText("CAN");
    ui->Rs485->setPlaceholderText("RS485");
//    ui->CAN->setPlainText("新的文本内容");

    ui->UART->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    ui->UART->setMinimumWidth(100);

    ui->CAN->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    ui->CAN->setMinimumWidth(100);

    ui->Rs485->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    ui->Rs485->setMinimumWidth(100);


    connect(chek, &TextEditEventFilter::textEditClicked, this, &MainWindow::showPopupTextEdit);
    this->setFixedSize(800,500);
    this->statusBar()->show();
    this->setWindowTitle("网关终端 （1.0.0）");
    this->statusBar()->showMessage("准备就绪");
    initializeTimer();

    chart = new QChart();
    ses = new QLineSeries();
    chart->addSeries(ses);
    chart->setAnimationOptions(QChart::AllAnimations);
    chartvie = new QChartView(chart);
    chartvie->setRenderHint(QPainter::Antialiasing);
    chartvie->setParent(this);
    chartL->addWidget(chartvie);

    chartCon->setLayout(chartL);

    tabWi->addTab(ui->frame,QStringLiteral("数据"));
    tabWi->addTab(chartCon,QStringLiteral("监视"));
    tabWi->setParent(this);
    chartL->addStretch(1);

    connect(ui->checkBox, &QCheckBox::stateChanged, this, &MainWindow::updateCheckStates);
    connect(ui->checkBox_2, &QCheckBox::stateChanged, this, &MainWindow::updateCheckStates);
    connect(ui->checkBox_3, &QCheckBox::stateChanged, this, &MainWindow::updateCheckStates);

    tabWi->setGeometry(200,150,595,330);
    tabWi->show();
    chartL->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    ui->comboBox->setEditText("1");
    ui->comboBox->setCurrentIndex(3); // 设置第一个项为当前项
    ui->led_1->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
    ui->groupBox->move(30,200);
    chartvie->setRubberBand(QChartView::HorizontalRubberBand);
    chartvie->setFixedSize(580,270);

    ui->l_6->setText("速率:0kb/s");
    ui->l_8->setText("速率:0kb/s");
    ui->l_10->setText("速率:0kb/s");

    uers->setBaudRate(QSerialPort::Baud115200);
    uers->setDataBits(QSerialPort::Data8);
    uers->setParity(QSerialPort::OddParity);
    uers->setStopBits(QSerialPort::TwoStop);
    uers->setFlowControl(QSerialPort::NoFlowControl);


    connect(uers,&QSerialPort::readyRead,[=](){
        QString newdat=uers->readAll();
        size_bit+=newdat.length();
        QString currentText = ui->UART->toPlainText();
        currentText.append(newdat);
        ui->UART->setPlainText(currentText);
    });

    MAX_bit=size_bit;
    QMovie* gif = new QMovie("/home/mnt/20240607033818_s10_p_Chr125_1536x864_1488x742_haf_1_www.ssbbww.com.gif");
    ui->label->setMovie(gif);
    ui->label->setScaledContents(true);
    gif->start();
    QFrame *gifFrame = new QFrame(this);
    gifFrame->setFrameShape(QFrame::Box);
    gifFrame->setLineWidth(3);
    gifFrame->setGeometry((this->width()-400)/2, 2, 409, 90); // 假设 yAxis 是您的 y 轴
    chart->setTitle("Sales Data");
    ui->label->setParent(gifFrame);
    ui->label->resize(390, 90);
    hhj = new widg(this);
    hhj->setFixedSize(880, 900); // 假设widg的高度为250像素
    // hhj->move(0, 50); // 假设将widg控件放   this->setFixedSize(860,580);置在窗口的某个位置
    hhj->show();
    hhj->lower();

    hhj->repaint();

    xAxis= new QValueAxis();
    yAxis= new QValueAxis();

    QDateTime temp_StartTime(QDate(1970, 1, 1), QTime(8, 0, 0));
    QDateTime temp_EndTime(QDate(1970, 1, 1), QTime(8, 0, 10));
    yAxis->setRange(1,10);
    xAxis->setRange(1,10);
    XAxis->setFormat("mm:ss");
    XAxis->setRange(temp_StartTime, temp_EndTime);
    qDebug()<<temp_EndTime;
    XAxis->setTickCount(10);

    chart->addAxis(XAxis, Qt::AlignBottom); // x轴通常在底部
    chart->addAxis(yAxis, Qt::AlignLeft);
    series->append(0,0);
    chart->addSeries(series);
    series->attachAxis(yAxis);
    series->attachAxis(XAxis);
    series->setPointsVisible(true);
    chart->setDropShadowEnabled();
}

void MainWindow::initializeTimer() {
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime); // 连接信号和槽
    connect(ui->key, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
}

void MainWindow::onButtonClicked()
{
   if(ui->comboBox->currentIndex()!=-1)
   {
       ui->comboBox->setCurrentIndex(3);
       ui->led_1->display(0);
       ui->lcdNumber_2->display(0);
       ui->lcdNumber_3->display(0);
   }
}
void widg::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 2)); // 设置画笔颜色和宽度

    // 绘制水平分割线
    int midHeight = 150; // 假设水平分割线在中间
    painter.drawLine(0, midHeight, width(), midHeight);

    // 确定垂直线的位置和长度
    int verticalLineStartY = midHeight =159+ 10; // 从水平线下方10像素处开始绘制垂直线
    int verticalLineHeight = height() - verticalLineStartY; // 垂直线将延伸到控件底部
    int horizontalSpacing = 800/ (3+1); // 计算水平间距
    int i = 0;
    int x = horizontalSpacing * (i +1); // 计算每条垂直线的x坐标
    painter.drawLine(x, verticalLineStartY, x, height());
}


void MainWindow::updateCheckStates(int state) {
    Qt::CheckState state1 = ui->checkBox->checkState();
    Qt::CheckState state2 = ui->checkBox_2->checkState();
    Qt::CheckState state3 = ui->checkBox_3->checkState();
      timer->start(1000);


}

void MainWindow::updateTime() {
        QString size_kb="速率"+(QString::number(size_bit/1000.0))+"kb/s";
     static qint64 lastXValue = 1;
       time_sun++;
       ntime_f=time_sun/60;
       ntime_s=time_sun%60;
       QString stime_f = QString::number(ntime_f);
       QString stime_s = QString::number(ntime_s);
       QString stime_sun =stime_f+":"+stime_s;

       if(size_bit>yAxis->max())
       {
         yAxis->setRange(0,size_bit+5);
       }

       QDateTime  temp(QDate(1970,1,1),QTime(8,0,0));
       temp=temp.addMSecs(time_sun*1000);
       qint64 ntemp=temp.toMSecsSinceEpoch();
       series->append(ntemp, size_bit);

       qint64 x_MAX = XAxis->max().toMSecsSinceEpoch();

    if(ntemp > x_MAX)
    {
        qint64 x_sum= (ntemp-x_MAX)/100;

        qint64 x_avg=ntemp/2;
        QDateTime rang = QDateTime::fromMSecsSinceEpoch(x_avg);
        QDateTime rang_end = rang.addSecs(10+x_sum);
        QDateTime rang_stop =rang.addSecs(-5);
        XAxis->setRange(rang_stop,rang_end);

    }

//    ses->append(40,22);
//    series->attachAxis(yAxis);
//    series->attachAxis(XAxis);


    chartvie->update();
    chart->update();

    if(a)
    this->statusBar()->showMessage("连接成功");
    if(ui->comboBox->currentIndex()!=-1)
    switch (ui->comboBox->currentIndex())
    {
    case 0:
        if(!uers->isOpen())
        uers->open(QIODevice::ReadWrite);
           ui->l_6->setText(size_kb);
           ui->led_1->display(stime_sun);
          ui->label_5->setText("端口号: "+uers->portName());
        break;
    case 1:
                    ui->lcdNumber_2->display(stime_sun);
       break;
   case 2:
        ui->lcdNumber_3->display(stime_sun);
    default:
        break;
    }

    else
        if(Qt::Checked == ui->checkBox->checkState() ||
           Qt::Checked == ui->checkBox_2->checkState() ||
           Qt::Checked == ui->checkBox_3->checkState())
           {
            if(Qt::Checked == ui->checkBox->checkState())
                if(!uers->isOpen())
                {
                    uers->open(QIODevice::ReadWrite);
                   ui->l_6->setText(size_kb);
                   ui->led_1->display(stime_sun);
                     ui->label_5->setText("端口号: "+uers->portName());
                }

                     if(Qt::Checked == ui->checkBox_2->checkState())
                                 ui->lcdNumber_2->display(stime_sun);

                    if(Qt::Checked == ui->checkBox_3->checkState())
                                ui->lcdNumber_3->display(stime_sun);
        }



    size_bit=0;
}


MainWindow::~MainWindow()
{
    delete ui;
    delete hhj;
    delete bj;
    uers->close();
    delete uers;
}

void MainWindow::showPopupTextEdit(QPlainTextEdit *textEdit) {

        QDialog *dialog = new QDialog(this, Qt::Dialog); // 设置窗口标志
        dialog->setWindowTitle("Popup Text Edit");
        dialog->resize(400, 300);

        QPlainTextEdit *largeTextEdit = new QPlainTextEdit(textEdit);
        largeTextEdit->setReadOnly(true);

        QPushButton *closeButton = new QPushButton("关闭");
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(largeTextEdit);
        layout->addWidget(closeButton);
        dialog->setLayout(layout);

        // 连接关闭按钮的点击信号到对话框的 accept 槽
        connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);

        dialog->exec(); // 显示模态对话框

}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(ui->comboBox->currentIndex()!=-1)
    {
      ui->led_1->display(0);
      ui->lcdNumber_2->display(0);
      ui->lcdNumber_3->display(0);
      time_sun=0;
      timer->start(1000);
    }
}

