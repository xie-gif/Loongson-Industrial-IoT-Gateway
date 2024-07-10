// File: TextEditEventFilter.h

#ifndef TEXTEDITEVENTFILTER_H
#define TEXTEDITEVENTFILTER_H

#include <QObject>
#include <QDebug>
#include <QPlainTextEdit>
#include <QEvent>

class QPlainTextEdit;

class TextEditEventFilter : public QObject {
    Q_OBJECT  // 宏，启用元对象系统

public:
    explicit TextEditEventFilter(QObject *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void textEditClicked(QPlainTextEdit *textEdit);  // 定义一个信号
};



#endif // TEXTEDITEVENTFILTER_H
