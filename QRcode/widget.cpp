#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QPainter>
#include <QBrush>
#include<QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->groupQR->setStyleSheet("color:black");
    setWindowTitle("QRcode生成器");
    this->_centerIcon = QPixmap(":/new/dog.png") ;
    on_pushButton_clicked();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString temp = ui->lineEdit->text();
    if(temp.isEmpty())
    {
        temp="请输入内容";
    }
    _str=temp.toUtf8();
    update();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    QBrush brush(Qt::black);
    paint.setBrush(brush);
    QRcode* mqrcode = QRcode_encodeString(_str.data(),7,QR_ECLEVEL_Q,QR_MODE_8,true);
    if(mqrcode != NULL)
    {
        this->_size = (this->width()-50)/mqrcode->width;
        this->_margin=(this->width()/2)-(mqrcode->width*_size)/2;
        unsigned char*point = mqrcode->data;
        for(int x=0;x<mqrcode->width;x++)
        {
            for(int y=0;y<mqrcode->width;y++)
            {
                if(*point&1)
                {
                    QRectF r(x*_size+_margin,y*_size+_margin+20,_size,_size);
                    paint.drawRect(r);
                }
                point++;
            }
        }
    }
    double scale = 0.28;
    double icon_size= (this->width()-2.0*_margin)*scale;
    double ix= this->width()/2.0-icon_size/2.0;
    double iy= this->height()/2.0-icon_size/2.0;
    QRect icon(ix,iy+20,icon_size,icon_size);
    paint.drawPixmap(icon,_centerIcon);
}
