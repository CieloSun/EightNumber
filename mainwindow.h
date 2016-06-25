#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "thread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void bfs();
    void bestFirst();
    void dfs();
    void resetMaze();
    void pause();
    void setMaze(Maze _maze);
private:
    Ui::MainWindow *ui;
    QPainter *painter;
    Maze maze;
    Thread *thread;
};

#endif // MAINWINDOW_H
