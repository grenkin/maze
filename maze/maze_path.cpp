/*
    Модуль поиска путей в лабиринте

    Реализации методов
        Maze
            find_random_path
            find_shortest_path
*/

#include <cstdlib>
#include "maze.h"

// найти случайный путь в лабиринте из пункта a в пункт b
//   path[0..n]:  path[0] = a, path[n] = b
Maze::Path Maze::find_random_path (Point a, Point b)
{
    Maze::Path path;
    path.push_back(a);
    Maze::Point p = a;
    while (p != b) {
        Dir dir;
        // находим направление, в котором можно пройти
        // если нельзя пройти ни в каком направлении, то зациклится
        do {
            // выбрать случайное направление
            int dir_ind = rand() % num_dir;  // dir_ind in 0..num_dir-1
            dir = dir_values[dir_ind];
        } while (!can_go(p, dir));
        // идем в найденном направлении
        Point q = move_dir(p, dir);
        // in_maze(q) = 1
        p = q;
        path.push_back(p);
    }
    // p = b  =>  path[n] = b
    // path[0] = a
    return path;
}

// найти кратчайший путь в лабиринте из пункта a в пункт b
//   path[0..n]:  path[0] = a, path[n] = b
Maze::Path Maze::find_shortest_path (Point a, Point b)
{
    // TODO

}
