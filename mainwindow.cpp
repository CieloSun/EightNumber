#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    thread=new Thread(maze);
    thread->resetMaze();
    ui->setupUi(this);
    connect(ui->actionDfs,SIGNAL(triggered(bool)),this,SLOT(dfs()));
    connect(ui->actionBfs,SIGNAL(triggered(bool)),this,SLOT(bfs()));
    connect(ui->actionBest_first,SIGNAL(triggered(bool)),this,SLOT(bestFirst()));
    connect(thread,SIGNAL(showMaze(Maze)),this,SLOT(setMaze(Maze)),Qt::BlockingQueuedConnection);
    connect(ui->actionPause,SIGNAL(triggered(bool)),this,SLOT(pause()));
}

void MainWindow::setMaze(Maze _maze)
{
    maze=_maze;
    update();
    updateGeometry();
}

void MainWindow::dfs()
{
    thread->setModel(1);
    thread->start();
}

void MainWindow::bfs()
{
    thread->setModel(2);
    thread->start();
}

void MainWindow::bestFirst()
{
    thread->setModel(3);
    thread->start();
}

void MainWindow::pause()
{
    thread->stop();
}

void MainWindow::resetMaze()
{
    thread->resetMaze();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    painter=new QPainter();
    painter->begin(this);
    painter->setPen(QPen(Qt::black,2,Qt::SolidLine));
    for(int i=0;i<4;++i)
    {
        painter->drawLine(50,50+50*i,200,50+50*i);
        painter->drawLine(50+50*i,50,50+50*i,200);
    }
    for(int i=0;i<3;++i)
    {
        for(int j=0;j<3;++j)
        {
            int num=maze.pget(i,j);
            if(num)
            {
                QString numstr=QString::number(num);
                painter->setFont(QFont(QString::fromLocal8Bit("宋体"),20,-1,false));
                painter->drawText(75+i*50,75+j*50,numstr);
            }
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
