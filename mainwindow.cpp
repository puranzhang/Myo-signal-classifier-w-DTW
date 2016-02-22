//CMSC240 Project
//Team: Ningxi, Puran, Ryan
//QT done by Ryan
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <stdlib.h>
#include "Signal.h"
#include "DTW.h"
#include <vector>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Produces the window that shows the two signals and their DTW graph
void MainWindow::paintEvent(QPaintEvent* e)
{

    int normalizeLines = 3;
    int indexLines = 5;
    int lineX;
    int lineY;

    DTW findDTW;


    std::string topNormString[] = {"1.0", "0.6", "0.2"};
    std::string normStr[] = {"0.0", "0.4", "0.8"};
    std::string indexStr[] = {"2000", "1500", "1000", "500", "0"};

    QPainter painter(this);

    QPoint textPoint;
    textPoint.setX(350);
    textPoint.setY(50);
    QString title = "Timeseries alignment";
    painter.drawText(textPoint, title);

    title = "Reference index";
    painter.rotate(270);
    textPoint.setX(-325);
    textPoint.setY(35);
    painter.drawText(textPoint, title);
    painter.rotate(-270);


    QPen pointPen(Qt::black);
    pointPen.setWidth(1);

    QPen linePen(Qt::black);
    linePen.setWidth(2);
    painter.setPen(linePen);


    painter.setPen(pointPen);
    painter.drawRect(QRect(80,80,120,450));
    //All rectangles are made with widths of 120 and 450 so that when drawing
    //the graphs they will occupy a space of 100 or 400 pixels, as 10 on each side
    //for the 120 and 25 on each side for the 450 will be the dead zones to make
    //the graphs more readable

    //make the vectors that contain the normalized signals
    QStringList list = qApp->arguments();
    std::string arg1 = list.at(1).toStdString();
    std::string arg2 = list.at(2).toStdString();

    Signal originalSig = Signal(arg1);
    Signal comparedSig = Signal(arg2);

    std::vector<double> referencedSig = originalSig.getData();
    std::vector<double> newSig = comparedSig.getData();


    //Print the graph of the new signal
    QPoint graphPoint1;
    QPoint graphPoint2;
    graphPoint2.setY(505);
    graphPoint2.setX(90+(newSig.front()*100));
    lineY = 505;
    for(int counter = 0; counter < (int)newSig.size(); counter++)
    {
        graphPoint1 = graphPoint2;
        graphPoint2.setY((double)lineY-((double)counter/((double)newSig.size()/(double)400)));

        double xSet = newSig.at(counter)*100;
        graphPoint2.setX(90 + xSet);
        painter.drawLine(graphPoint1, graphPoint2);
    }


    //Prints the graph of the original signal

    graphPoint2.setY(550+(referencedSig.front()*100));
    graphPoint2.setX(235);
    lineY = 235;
    for(int counter = 0; counter < (int)referencedSig.size(); counter++)
    {
        graphPoint1 = graphPoint2;
        graphPoint2.setX((double)lineY+((double)counter/((double)referencedSig.size()/(double)400)));

        double ySet = referencedSig.at(counter)*100;
        graphPoint2.setY(550 + ySet);
        painter.drawLine(graphPoint1, graphPoint2);
    }


    //prints the shortest path

    vector<double> dtwPoints = findDTW.dtw(referencedSig, newSig);
    //starting is 235, 555, goes to 635, 135
    lineX = 235;
    lineY = 515;
    QPoint pathPoint1;
    QPoint pathPoint2;
    //initialize points to 0,0 as that is the start
    pathPoint1.setX(235 + dtwPoints[0]/((double)dtwPoints.size()/(double)800));
    pathPoint1.setY(515 - dtwPoints[1]/((double)dtwPoints.size()/(double)800));
    pathPoint2 = pathPoint1;
    int graphDraw = 0;
    while(graphDraw < (int)dtwPoints.size())
    {
        pathPoint1 = pathPoint2;
        int xPoint = dtwPoints[graphDraw];
        int yPoint = dtwPoints[graphDraw+1];
        xPoint = ((double)lineX+(xPoint/((double)dtwPoints.size()/(double)800)));
        yPoint = ((double)lineY-(yPoint/((double)dtwPoints.size()/(double)800)));
        pathPoint2.setX((double)xPoint);
        pathPoint2.setY((double)yPoint);
        graphDraw = graphDraw + 2;
        painter.drawLine(pathPoint1, pathPoint2);
    }

    lineX = 90;
    lineY = 70;
    //Paints the normalization tick marks for the upper graph
    for(int counter = 0; counter < indexLines+1; counter++)
    {
        painter.drawLine(QLine(lineX+(20*counter),lineY,lineX+(20*counter),lineY+10));
    }
    //Paints the normalization numbers for the upper graph
    lineX = 85;
    for(int counter = 0; counter < normalizeLines; counter++)
    {
        QString graphNum = QString::fromStdString(topNormString[counter]);
        textPoint.setX(lineX+(40*counter));
        textPoint.setY(lineY-10);
        painter.drawText(textPoint, graphNum);
    }


    //horizontal lines for the indices of the top right graph
    lineX = 70;
    lineY = 145;
    for(int counter = 0; counter< indexLines; counter++)
    {
        painter.drawLine(QLine(lineX,lineY+(90*counter),lineX+10,lineY+(90*counter)));
    }

    painter.rotate(270);
    //The rotate actually affects the coordinates, so the X and Y must be flipped
    //and the X made negative in order to appear in the right spot when rotated 270 degrees
    textPoint.setY(60);
    int start = -158;
    for(int counter = 0; counter < indexLines; counter ++)
    {
       QString graphNum = QString::fromStdString(indexStr[counter]);
       //Adjusts the height for the changing size of the numbers
       if(counter == 3)
       {
            start = start+3;
       }
       else if(counter == 4)
       {
           start = start+6;
       }
       textPoint.setX(start + (-90 * counter));
       painter.drawText(textPoint, graphNum);
    }
    painter.rotate(-270);


    //Writes the Lower Graph's Ticks and Values for its Indices, the horizontal ones
    lineX = 595;
    lineY = 660;
    start = 590;
    textPoint.setY(690);
    for(int counter = indexLines-1; counter >= 0; counter --)
    {
       QString graphNum = QString::fromStdString(indexStr[counter]);
       //Adjusts the width for the changing size of the numbers
       if(counter == 1)
       {
            start = start-6;
       }
       else if(counter == 2)
       {
           start = start-3;
       }
       textPoint.setX(start - (90 * counter));
       painter.drawText(textPoint, graphNum);
       painter.drawLine(QLine(lineX-(90*counter), lineY, lineX-(90*counter), lineY+10));
    }

    painter.drawRect(QRect(210,540,450,120));


    lineX = 200;
    lineY = 550;
    //Draws the vertical ticks for the normalized indices
    for(int counter = 0; counter < indexLines+1; counter++)
    {
        painter.drawLine(QLine(lineX,lineY+(20*counter),lineX+10,lineY+(20*counter)));
    }
    //The rotate actually affects the coordinates, so the X and Y must be flipped
    //and the X made negative in order to appear in the right spot when rotated 270 degrees
    textPoint.setY(190);
    for(int counter = 0; counter < normalizeLines; counter ++)
    {
       painter.rotate(270);

       QString graphNum = QString::fromStdString(normStr[counter]);
       textPoint.setX(-660 + (40 * counter));
       painter.drawText(textPoint, graphNum);
       painter.rotate(-270);

    }

    painter.drawRect(QRect(210,80,450,450));
}

