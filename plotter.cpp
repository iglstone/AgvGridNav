#include "plotter.h"

plotter::plotter(QWidget *parent) : QWidget(parent)
{
    this->XRows = 20;
    this->YCols = 10;
}

void plotter::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    drawGrid(&painter);
    painter.setPen(Qt::black);
    painter.drawLine(0,0,200,200);

}

void plotter::drawGrid(QPainter *painter)
{

    painter->drawLine(0,0,150,100);

    int Margin=35;//边缘
    QRect rect;
    //取得绘图区域，大小要减去旁白
    //rect=QRect(Margin+300,Margin+300,width()-Margin-700,height()-Margin-500);
    rect=QRect(Margin, Margin, width()-2*Margin, height()-2*Margin);

    float xstep = (float)(rect.width())/this->XRows;
    float ystep = (float)(rect.height())/this->YCols;

    for(int i=0; i<=this->XRows; i++)
    {
        int x=Margin+i*xstep;
        painter->drawLine(x,rect.top(),x,rect.bottom());
    }

    for(int j=0; j<=this->YCols; j++)
    {
        int y=Margin+(j*ystep);
        painter->drawLine(Margin,y,rect.right(),y);
    }

}
