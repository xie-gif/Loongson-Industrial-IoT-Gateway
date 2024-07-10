// File: TextEditEventFilter.cpp

#include "chke.h"
#include <QPlainTextEdit>
#include <QEvent>

TextEditEventFilter::TextEditEventFilter(QObject *parent)
    : QObject(parent)
{
}

bool TextEditEventFilter::eventFilter(QObject *obj, QEvent *event){
    if (event->type() == QEvent::MouseButtonPress) {
//        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
//        qDebug()<<obj->objectName();

        QPlainTextEdit *textEdit = qobject_cast<QPlainTextEdit *>(obj);
//        if (textEdit) {
//            QPoint localPos = textEdit->mapFromGlobal(mouseEvent->globalPos());
//            if (textEdit->geometry().contains(localPos)) {
        qDebug()<<textEdit->objectName();
                emit textEditClicked(textEdit);
//            }
//        }
    }
    return QObject::eventFilter(obj, event);
}
