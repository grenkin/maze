/*
    Модуль вывода лабиринта на экран

    Реализации методов
        Maze
            print
            print_path
            animate_path
*/

#include <cstdio>
#include <array>
#include "maze.h"

using namespace std;

/***********************************************/

// символы для вывода на экран
enum console_chars {
#ifdef WIN_CONSOLE
    CH_POINT      = 249,
    CH_VERT_LINE  = 179,
    CH_HORIZ_LINE = 196,
    CH_SPACE      = ' ',
    CH_LINE_BREAK = '\n',
    CH_UNIT       = '@',
    // 4 цифры означают узловой символ (left, right, up, down)
    CH_NODE_0000 = CH_SPACE,
    CH_NODE_0001 = CH_SPACE,
    CH_NODE_0010 = CH_SPACE,
    CH_NODE_0011 = CH_VERT_LINE,
    CH_NODE_0100 = CH_SPACE,
    CH_NODE_0101 = 218,
    CH_NODE_0110 = 192,
    CH_NODE_0111 = 195,
    CH_NODE_1000 = CH_SPACE,
    CH_NODE_1001 = 191,
    CH_NODE_1010 = 217,
    CH_NODE_1011 = 180,
    CH_NODE_1100 = CH_HORIZ_LINE,
    CH_NODE_1101 = 194,
    CH_NODE_1110 = 193,
    CH_NODE_1111 = 197
#else // WIN_CONSOLE
    CH_POINT      = '.',
    CH_VERT_LINE  = '|',
    CH_HORIZ_LINE = '-',
    CH_SPACE      = ' ',
    CH_LINE_BREAK = '\n',
    CH_UNIT       = '@',
    // 4 цифры означают узловой символ (left, right, up, down)
    CH_NODE_0000 = CH_SPACE,
    CH_NODE_0001 = CH_SPACE,
    CH_NODE_0010 = CH_SPACE,
    CH_NODE_0011 = CH_VERT_LINE,
    CH_NODE_0100 = CH_SPACE,
    CH_NODE_0101 = '-',
    CH_NODE_0110 = '-',
    CH_NODE_0111 = '|',
    CH_NODE_1000 = CH_SPACE,
    CH_NODE_1001 = '-',
    CH_NODE_1010 = '-',
    CH_NODE_1011 = '|',
    CH_NODE_1100 = CH_HORIZ_LINE,
    CH_NODE_1101 = '-',
    CH_NODE_1110 = '-',
    CH_NODE_1111 = '+'
#endif // WIN_CONSOLE
};

void write (console_chars ch) { console::write(ch); }
// вывести узловой символ по данным о том, есть ли стенки слева, справа, сверху и снизу
// walls[] = { wall_left, wall_right, wall_up, wall_down }
void write_node (array<bool, 4> walls);


/***********************************************/

// вывести лабиринт в файл (поток) out
// пункт [i,j] вывести как символ c[i,j], i=1..n, j=1..m
void Maze::print_maze (vector<vector<char> > c, FILE *out)
{
    for (int i = 0; i <= n; ++i) {
        /* выводим квадратик 2x2, соответствующий точке (i, j) */
        for (int j = 0; j <= m; ++j) {
            // выводим содержимое точки (i, j)
            if (i > 0 && j > 0)
                console::write(c[i][j]);
            else
                write(CH_SPACE);
            // выводим стенку справа от точки (i, j)
            if (walls_v[i][j])  // правее точки (i, j) есть стенка
                write(CH_VERT_LINE);
            else
                write(CH_SPACE);
        }
        write(CH_LINE_BREAK);
        for (int j = 0; j <= m; ++j) {
            // выводим горизонтальную стенку снизу от точки (i, j)
            if (walls_h[i][j])  // ниже точки (i, j) есть стенка
                write(CH_HORIZ_LINE);
            else
                write(CH_SPACE);
            // выводим узловой символ в правом нижнем углу квадратика
            write_node({walls_h[i][j], walls_h[i][j+1],
                walls_v[i][j], walls_v[i+1][j]});
        }
        write(CH_LINE_BREAK);
    }
}

// вывести лабиринт в файл (поток) out
// p - текущее местоположение
void Maze::print (Point p, FILE *out)
{
    /* заполняем матрицу пунктов лабиринта */
    // [0..n, 0..m]Char c
    vector<vector<char> > c(n + 1);
    for (int i = 0; i <= n; ++i)
        c[i].resize(m + 1, CH_POINT);
    c[p.i][p.j] = CH_UNIT;

    print_maze(c, out);
}

// вывести путь в лабиринте в файл (поток) out
void Maze::print_path (Path path, FILE *out)
{
    /* заполняем матрицу пунктов лабиринта */
    // [0..n, 0..m]Char c
    vector<vector<char> > c(n + 1);
    for (int i = 0; i <= n; ++i)
        c[i].resize(m + 1, CH_POINT);

    // перечисляем пункты (p) пути в лабиринте
    for (auto p : path) {
        c[p.i][p.j] = CH_UNIT;
    }
    c[path.front().i][path.front().j] = 'S';
    c[path.back().i][path.back().j] = 'F';
    /* матрица заполнена */

    print_maze(c, out);

    // вывести длину пути
    fprintf(out, "\nLength = %d\n", path.size() - 1);
}

// вывести путь в лабиринте на экран с паузами delay_ms мс
void Maze::animate_path (Maze::Path path, int delay_ms)
{
    // перечисляем пункты (p) пути в лабиринте
    for (auto p : path) {
        console::clear_screen();
        print(p);
        console::delay(delay_ms);
    }
}

/***********************************************/


// walls[] = { wall_left, wall_right, wall_up, wall_down }
void write_node (array<bool, 4> walls)
{
    console_chars node_chars[16] = {
        CH_NODE_0000, CH_NODE_0001, CH_NODE_0010, CH_NODE_0011,
        CH_NODE_0100, CH_NODE_0101, CH_NODE_0110, CH_NODE_0111,
        CH_NODE_1000, CH_NODE_1001, CH_NODE_1010, CH_NODE_1011,
        CH_NODE_1100, CH_NODE_1101, CH_NODE_1110, CH_NODE_1111
    };
    int ind = 0;  // индекс двоичной последовательности из 4 элементов
    int z = 1;
    for (int i = 0; i < 4; ++i) {
        // z = 2^i
        ind += walls[3 - i] * z;
        z *= 2;
    }
    write(node_chars[ind]);
}
