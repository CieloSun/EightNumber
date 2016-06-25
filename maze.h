#include <QMainWindow>
#include <QPainter>
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
#include <QThread>
#include <QMutex>
#include <ctime>
#include <cstdlib>
#include <QString>
using namespace std;

const int endMaze[3][3] =
{
    { 1,2,3 },{ 8,0,4 },{ 7,6,5 }
};

class Maze
{
private:
    int p[3][3];
    int ei, ej;
public:
    Maze(int temp[3][3])
    {
        for (int i = 0;i < 3;++i)
        {
            for (int j = 0;j < 3;++j)
            {

                p[i][j] = temp[i][j];
                if (!p[i][j])
                {
                    ei = i;
                    ej = j;
                }

            }
        }
    }
    Maze()
    {
        for (int i = 0;i < 3;++i)
        {
            for (int j = 0;j < 3;++j)
            {

                p[i][j] = endMaze[i][j];
                if (!p[i][j])
                {
                    ei = i;
                    ej = j;
                }
            }
        }
    }
    bool valid(int x, int y) const
    {
        if (0 <= x&&x <= 2 && 0 <= y&&y <= 2) return true;
        return false;
    }
    bool left()
    {
        if (!valid(ei, ej - 1)) return false;
        swap(p[ei][ej], p[ei][ej - 1]);
        --ej;
        return true;
    }
    bool right()
    {
        if (!valid(ei, ej + 1)) return false;
        swap(p[ei][ej], p[ei][ej + 1]);
        ++ej;
        return true;
    }
    bool up()
    {
        if (!valid(ei - 1, ej)) return false;
        swap(p[ei][ej], p[ei - 1][ej]);
        --ei;
        return true;
    }
    bool down()
    {
        if (!valid(ei + 1, ej)) return false;
        swap(p[ei][ej], p[ei + 1][ej]);
        ++ei;
        return true;
    }
    bool success() const
    {
        for (int i = 0;i < 3;++i)
        {
            for (int j = 0;j < 3;++j)
            {
                if (p[i][j] != endMaze[i][j]) return false;
            }
        }
        return true;
    }
    bool operator== (const Maze &a)
    {
        for (int i = 0;i < 3;++i)
        {
            for (int j = 0;j < 3;++j)
            {
                if (p[i][j] != a.p[i][j]) return false;
            }
        }
        return true;
    }
    bool operator < (const Maze &a) const
    {
        return a.herustic() < herustic();
    }
    int herustic() const
    {
        int res = 0;
        for (int i = 0;i < 3;++i)
        {
            for (int j = 0;j < 3;++j)
            {
                for (int k = 0;k < 3;++k)
                {
                    for (int h = 0;h < 3;++h)
                    {
                        if (p[i][j] == endMaze[k][h])
                        {
                            res += abs(i - k) + abs(j - h);
                        }
                    }
                }
            }
        }
        return res;
    }
    int pget(int i,int j) const
    {
        return p[i][j];
    }
};
