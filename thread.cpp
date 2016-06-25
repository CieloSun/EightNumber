#include "thread.h"

Thread::Thread(Maze _maze,int _model):
maze(_maze),model(_model)
{
    stopped=false;
}

void Thread::stop()
{
    QMutexLocker locker(&mutex);
    stopped=true;
}

void Thread::setModel(int _model)
{
    model=_model;
}

void Thread::run()
{

    switch(model)
    {
    case 1:
        dfs();break;
    case 2:
        bfs();break;
    case 3:
        bestFirst();break;
    default:
        break;
    }
}

void Thread::dfs()
{
    vector<Maze> v;
    int d=0;//0down,1left,2right,3up
    srand(time(0));
    while(!stopped&&!maze.success())
    {
        Maze tmp=maze;
        d=(d+1)%4;
        switch(d)
        {
        case 0:
            maze.down()||maze.left()||maze.right()||maze.up();break;
        case 1:
            maze.left()||maze.down()||maze.right()||maze.up();break;
        case 2:
            maze.right()||maze.down()||maze.left()||maze.up();break;
        case 3:
            maze.up()||maze.down()||maze.left()||maze.right();break;
        }
        if(std::find(v.begin(),v.end(),maze)==v.end())
        {
            v.push_back(maze);
            emit showMaze(maze);
            msleep(500);
        }
        else maze=tmp;
    }
}

void Thread::resetMaze()
{
    int temp[3][3];
    int cnt = 0;
    for (int i = 0;i < 3;++i)
    {
        for (int j = 0;j < 3;++j)
        {
            temp[i][j] = cnt++;
        }
    }

    srand(time(0));
    for (int t = 0;t < 100;++t)
    {
        int i = rand() % 3;
        int j = rand() % 3;
        int k = rand() % 3;
        int h = rand() % 3;
        swap(temp[i][j], temp[k][h]);
    }
    maze=Maze(temp);
    emit showMaze(maze);
    QMutexLocker locker(&mutex);
    stopped=false;
}

void Thread::bfs()
{
    vector<Maze> visited;
    visited.clear();
    queue<Maze> q;
    q.push(maze);
    int cnt = 0;
    while (q.size()&&!stopped)
    {
        maze = q.front();q.pop();
        visited.push_back(maze);
        emit showMaze(maze);
        cnt++;
        if (maze.success())
        {
            return;
        }
        if (maze.left() && std::find(visited.begin(), visited.end(), maze) == visited.end())
        {
            q.push(maze);
            maze.right();
        }
        if (maze.up() && std::find(visited.begin(), visited.end(), maze) == visited.end())
        {
            q.push(maze);
            maze.down();
        }
        if (maze.right() && std::find(visited.begin(), visited.end(), maze) == visited.end())
        {
            q.push(maze);
            maze.left();
        }
        if (maze.down() && std::find(visited.begin(), visited.end(), maze) == visited.end())
        {
            q.push(maze);
            maze.up();
        }
        msleep(500);
    }
    return;
}


void Thread::bestFirst()
{
    vector<Maze> visited;
    visited.clear();
    priority_queue<Maze> pq;
    pq.push(maze);
    int cnt = 0;
    while (pq.size()&&!stopped)
    {
        maze = pq.top();pq.pop();
        visited.push_back(maze);
        emit showMaze(maze);
        cnt++;
        if (maze.success())
        {
            return;
        }
        if (maze.left() && std::find(visited.begin(), visited.end(), maze) == visited.end())
        {
            pq.push(maze);
            maze.right();
        }
        if (maze.up() && std::find(visited.begin(), visited.end(), maze) == visited.end())
        {
            pq.push(maze);
            maze.down();
        }
        if (maze.right() && std::find(visited.begin(), visited.end(), maze) == visited.end())
        {
            pq.push(maze);
            maze.left();
        }
        if (maze.down() && std::find(visited.begin(), visited.end(), maze) == visited.end())
        {
            pq.push(maze);
            maze.up();
        }
        msleep(500);
    }
    return;
}
