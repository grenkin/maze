#include <iostream>
#include "maze/maze.h"

using namespace std;

int main()
{
    Maze maze(5, 5);
    // добавляем стенки
    maze.walls_v[1][1] = maze.walls_v[2][1] = true;
    maze.walls_h[2][2] = maze.walls_h[2][3] =
        maze.walls_h[2][4] = maze.walls_h[2][5] = true;
    maze.walls_v[4][3] = maze.walls_v[5][3] = true;

    maze.print();

    return 0;
}
