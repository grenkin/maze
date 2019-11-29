/*
    Модуль поиска путей в лабиринте

    Реализации методов
        Maze
            find_random_path
            find_shortest_path
*/

#include <cstdlib>
#include "maze.h"
#include "../graph/graph.h"

using namespace std;

// найти случайный путь в лабиринте из пункта a в пункт b
//   path[0..k]:  path[0] = a, path[k] = b
Maze::Path Maze::find_random_path (Point a, Point b)
{
    Path path;
    path.push_back(a);
    Point p = a;
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
    // p = b  =>  path[k] = b
    // path[0] = a
    return path;
}

// индекс вершины графа, соответствующей пункту [i,j] лабиринта maze
int vertex_index(Maze &maze, Maze::Point p)
    // i in 1..n, j in 1..m
    // ind in 0..n*m-1
{
    int n = maze.n, m = maze.m;
    int i = p.i, j = p.j;
    int ind = (i - 1) * m + (j - 1);
    return ind;
}

// найти кратчайший путь в лабиринте из пункта a в пункт b
//   path[0..k]:  path[0] = a, path[k] = b
Maze::Path Maze::find_shortest_path (Point a, Point b)
{
    /* строим граф */
    // вершины графа - это пункты лабиринта [i,j], i=1..n, j=1..m
    int num_vert = n * m;  // число вершин в графе
    Graph graph(num_vert);

    // таблица соответствия : вершина графа -> пункт лабиринта
    vector<Point> vert_to_point (num_vert);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            Point p = {i, j};
            int u = vertex_index(*this, p);  // вершина графа
            // u in 0..num_vert-1

            // заполняем элемент таблицы соответствия
            vert_to_point[u] = p;

            // перечисляем направления движения из пункта p лабиринта
            for (int dir_ind = 0; dir_ind < num_dir; ++dir_ind) {
                Maze::Dir dir = dir_values[dir_ind];
                if (can_go(p, dir)) {
                    // идем из пункта p в направлении dir
                    Point q = move_dir(p, dir);
                    // in_maze(q) = 1
                    int v = vertex_index(*this, q);
                    // v - смежная вершина графа

                    // добавляем ребро из u в v
                    graph.add_edge(u, v);
                }
            }
        }
    }

    // вершины графа, соответствующие пунктам a, b
    int a_v = vertex_index(*this, a),  b_v = vertex_index(*this, b);
    // находим кратчайший путь в графе из a_v в b_v
    Graph::Path graph_path = graph.find_shortest_path(a_v, b_v);

    // переводим путь в графе в путь в лабиринте
    Path path;
    for (auto v : graph_path) {
        path.push_back(vert_to_point[v]);
    }

    return path;
}
