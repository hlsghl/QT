#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"qrencode/qrencode.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void paintEvent(QPaintEvent *event);
private:
    Ui::Widget *ui;
    int _size;
    int _margin;
    QPixmap _centerIcon;
    QByteArray _str;
};

#endif // WIDGET_H
