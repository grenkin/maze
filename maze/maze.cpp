/*
    Основные функции для работы с лабиринтом

    Реализации методов
        Maze
            конструктор
            init_maze
            in_maze
            can_go
            move_dir
*/

#include <fstream>
#include "maze.h"

using namespace std;

/************************************************
    реализация методов класса Maze
************************************************/

// конструктор класса Maze
// создает лабиринт n x m со стенками по краям
Maze::Maze (int n_arg, int m_arg)
    : n(n_arg), m(m_arg)
{
    init_maze(n, m);
}

// инициализация лабиринта n x m со стенками по краям
void Maze::init_maze (int n, int m)
// 1 <= n,  1 <= m
{
    walls_h.resize(n + 2);  // walls_h[0..n+1]
    for (int i = 0; i <= n + 1; ++i)
        walls_h[i].resize(m + 2);  // walls_h[i][0..m+1]
    walls_v.resize(n + 2);  // walls_v[0..n+1]
    for (int i = 0; i <= n + 1; ++i)
        walls_v[i].resize(m + 2);  // walls_v[i][0..m+1]

    /* добавляем стенки по краям лабиринта */
    // добавляем горизонтальные стенки после 0-й и n-й строки
    //   в столбцах j=1..m
    for (int i = 0; i <= n; i += n) {  // for i = {0, n}
        for (int j = 1; j <= m; ++j)
            walls_h[i][j] = true;
    }
    // добавляем вертикальные стенки после 0-го и m-го столбца
    //   в строках i=1..n
    for (int j = 0; j <= m; j += m) {  // for j = {0, m}
        for (int i = 1; i <= n; ++i)
            walls_v[i][j] = true;
    }
}

/***********************************************/

// принадлежит ли пункт лабиринту
bool Maze::in_maze (Maze::Point p)
{
    return (1 <= p.i && p.i <= n && 1 <= p.j && p.j <= m);
}

// можно ли пройти из пункта p в направлении dir
bool Maze::can_go (Maze::Point p, Maze::Dir dir)
{
    // из p в направлении dir придем в q
    Point q = move_dir(p, dir);
    // если q не принадлежит лабиринту, то туда пройти нельзя
    if (!in_maze(q))
        return false;

    int i = p.i, j = p.j;
    bool w;  // есть ли стенка
    switch (dir) {
        case DIR_LEFT:
            w = walls_v[i][j - 1];
            break;
        case DIR_RIGHT:
            w = walls_v[i][j];
            break;
        case DIR_UP:
            w = walls_h[i - 1][j];
            break;
        case DIR_DOWN:
            w = walls_h[i][j];
            break;
    }
    return !w;
}

// пройти из пункта p в направлении dir
Maze::Point Maze::move_dir (Maze::Point p, Maze::Dir dir)
{
    Point q;
    q.i = p.i + di[dir];  q.j = p.j + dj[dir];
    return q;
}
