#include <iostream>
#include <cstdlib>
#include <ctime>
#include "maze/maze.h"

using namespace std;

int main()
{
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

    maze.print();

    return 0;
}
