#include <iostream>
#include <cstdlib>
#include <ctime>
#include "maze/maze.h"

using namespace std;

int main()
{
    // лабиринт 5x5
    Maze maze(5, 5);

    // добавляем стенки
    /* maze.walls_v[1][1] = maze.walls_v[2][1] = true;
    maze.walls_h[2][2] = maze.walls_h[2][3] =
        maze.walls_h[2][4] = maze.walls_h[2][5] = true;
    maze.walls_v[4][3] = maze.walls_v[5][3] = true; */

    int p = 25;
    srand (time(NULL));
    // случайная генерация лабиринта
    //   ставим стенку с вероятностью p%
    maze.generate_random(p);

    // очистить экран
    console::clear_screen();
    // вывести лабиринт на экран
    maze.print();
    // нажмите любую клавишу
    console::pause();

    // очистить экран
    console::clear_screen();
    // найти случайный путь в лабиринте между двумя пунктами
    Maze::Path path = maze.find_random_path({1, 1}, {3, 3});
    // вывести путь на экран с паузами
    maze.animate_path(path, 100);
    // нажмите любую клавишу
    console::pause();

    // очистить экран
    console::clear_screen();
    // вывести путь на экран
    maze.print_path(path);
    // нажмите любую клавишу
    console::pause();

    return 0;
}
