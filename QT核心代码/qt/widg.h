#ifndef WIDG_H
#define WIDG_H

#include <QPlainTextEdit>
#include <QMouseEvent>
#include <QDialog>
#include <QVBoxLayout>
#include <QWidget>

class widg : public QWidget
{
    Q_OBJECT
public:
    explicit widg(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *)override;

//    ~widg()
//    {
//        delete hhj;
//    }

signals:

};



#endif // WIDG_H
