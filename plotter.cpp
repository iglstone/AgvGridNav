#include "plotter.h"

plotter::plotter(QWidget *parent) : QWidget(parent)
{
    this->XRows = 20;
    this->YCols = 10;
    m_timer.start(500, this);
    m_nStep = 0;
}

plotter::~plotter(){
    m_timer.stop();
}

void plotter::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    drawGrid(&painter);

    //painter.drawLine(0,0,200,200);

}

void plotter::drawGrid(QPainter *painter)
{

    painter->setPen(Qt::black);

    int Margin=35;//边缘
    QRect rect;
    //取得绘图区域，大小要减去旁白
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

    //painter->setBrush(Qt::blue);
    //painter->drawEllipse(30, 30, 10,10);

    int nIndex = (m_nStep) % 2;
    if(nIndex){
        painter->setBrush(Qt::blue);
        painter->drawEllipse(30, 30, 10,10);
    }else{
        //painter->setPen(Qt::blue);
        //painter->drawEllipse(30, 30, 10,10);
    }

}

void plotter::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if (event->timerId() == m_timer.timerId())
    {
        ++m_nStep;
        update();
    }
    else
    {
        QWidget::timerEvent(event);
    }
}
