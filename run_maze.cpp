#include <iostream>
#include <cstdlib>
#include <ctime>
#include "maze/maze.h"

using namespace std;

// считать с экрана координаты пункта лабиринта
Maze::Point read_point (string point_name)
{
    Maze::Point p;
    cout << "Point " << point_name << " = \n";
    cout << "   row = ";
    cin >> p.i;
    cout << "   col = ";
    cin >> p.j;
    cout << "\n";
    return p;
}

int main()
{

/* создание объекта "лабиринт" */
    int n = 5;  // число строк
    int m = 5;  // число столбцов
    // лабиринт n x m
    Maze maze(n, m);


/* демонстрация ручного ввода стенок */
    // добавляем стенки
    /* maze.walls_v[1][1] = maze.walls_v[2][1] = true;
    maze.walls_h[2][2] = maze.walls_h[2][3] =
        maze.walls_h[2][4] = maze.walls_h[2][5] = true;
    maze.walls_v[4][3] = maze.walls_v[5][3] = true; */


/* демонстрация случайной генерации лабиринта */
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
    // console::pause();


/* ввод начального и конечного пунктов */
    /*
    // очистить экран
    console::clear_screen();
    // вывести лабиринт на экран
    maze.print();
    */
    // ввод пунктов
    Maze::Point A = read_point("A"), B = read_point("B");


/* демонстрация путей в лабиринте */
    // очистить экран
    console::clear_screen();
    // найти случайный путь в лабиринте между двумя пунктами
    Maze::Path path1 = maze.find_random_path(A, B);
    // вывести путь на экран с паузами
    maze.animate_path(path1, 50);
    // нажмите любую клавишу
    console::pause();
    // очистить экран
    console::clear_screen();
    // вывести путь на экран
    maze.print_path(path1);
    // нажмите любую клавишу
    console::pause();

    // очистить экран
    console::clear_screen();
    // найти кратчайший путь в лабиринте между двумя пунктами
    Maze::Path path2 = maze.find_shortest_path(A, B);
    // вывести путь на экран с паузами
    maze.animate_path(path2, 100);
    // нажмите любую клавишу
    console::pause();
    // очистить экран
    console::clear_screen();
    // вывести путь на экран
    maze.print_path(path2);
    // нажмите любую клавишу
    console::pause();


/* демонстрация ввода-вывода лабиринта в файл */
/*
    const char *file_name = "lab1.txt";
    // вывести лабиринт в файл
    maze.print_data(file_name);

    // считать лабиринт из файла
    Maze maze1(file_name);
    // очистить экран
    console::clear_screen();
    // вывести лабиринт на экран
    maze.print();
    // нажмите любую клавишу
    console::pause();
*/

    return 0;
}
