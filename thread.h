#ifndef THREAD_H
#define THREAD_H
#include "maze.h"

class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(Maze _maze,int _model=0);
    void resetMaze();
    void dfs();
    void bfs();
    void bestFirst();
    void stop();
    void setModel(int _model);
protected:
    void run();
signals:
    void showMaze(Maze maze);
private slots:
private:
    Maze maze;
    QMutex mutex;
    int model;
    volatile bool stopped;
};

#endif // THREAD_H
