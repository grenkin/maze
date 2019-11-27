/*
    Основные функции для работы с лабиринтом

    Реализации методов
        Maze
            in_maze
            can_go
            move_dir
*/

#include "maze.h"

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
