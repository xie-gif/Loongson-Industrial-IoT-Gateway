// widg.cpp
#include "widg.h"
#include <QPainter>

#include <QDebug>

widg::widg(QWidget *parent) : QWidget(parent) {
    // 构造函数内容
}

//void widg::paintEvent(QPaintEvent *event) {
//    QPainter painter(this);
//    painter.setPen(QPen(Qt::black, 2)); // 设置画笔颜色和宽度

//    // 绘制水平分割线
//    int midHeight = height() / 2; // 假设水平分割线在中间
//    painter.drawLine(0, midHeight, width(), midHeight);

//    // 确定垂直线的位置和长度
//    int verticalLineStartY = midHeight + 10; // 从水平线下方10像素处开始绘制垂直线
//    int verticalLineHeight = height() - verticalLineStartY; // 垂直线将延伸到控件底部

//    // 绘制四条等间距的垂直线
//    int numVerticalLines = 3;
//    int horizontalSpacing = width() / (numVerticalLines + 1); // 计算水平间距

//    qDebug() << this->size();
//    for (int i = 0; i < numVerticalLines; ++i) {
//        int x = horizontalSpacing * (i + 1); // 计算每条垂直线的x坐标
//        painter.drawLine(x, verticalLineStartY, x, height());
//    }
//}
