#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <thread>
#include "maze.h"

using namespace std;

/***********************************************/
// закомментировать в Linux
#define WIN_CONSOLE

// символы для вывода на экран
enum console_chars {
#ifdef WIN_CONSOLE
    CH_POINT      = 249,
    CH_VERT_LINE  = 179,
    CH_HORIZ_LINE = 196,
    CH_SPACE      = ' ',
    CH_LINE_BREAK = '\n',
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
#else
    CH_POINT      = '.',
    CH_VERT_LINE  = '|',
    CH_HORIZ_LINE = '-',
    CH_SPACE      = ' ',
    CH_LINE_BREAK = '\n',
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
#endif
};

void clear_screen ();
void delay (int ms);
void write (console_chars ch) { putc(ch, stdout); }
// вывести узловой символ по данным о том, есть ли стенки слева, справа, сверху и снизу
// walls[] = { wall_left, wall_right, wall_up, wall_down }
void write_node (array<bool, 4> walls);


/***********************************************/

// вывести лабиринт на экран
void Maze::print ()
{
    clear_screen();
    for (int i = 0; i <= n; ++i) {
        /* выводим квадратик 2x2, соответствующий точке (i, j) */
        for (int j = 0; j <= m; ++j) {
            // выводим содержимое точки (i, j)
            if (i > 0 && j > 0)
                write(CH_POINT);
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
            write_node({walls_h[i][j], walls_h[i][j+1], walls_v[i][j], walls_v[i+1][j]});
            //write(CH_SPACE);
        }
        write(CH_LINE_BREAK);
    }
}


// бинарная случайная величина
//   1 - с вероятностью p%, 0 - с вероятностью (1-p)%
bool random_binary (int p)
{
    int random_value = rand();  // 0..RAND_MAX
    return (random_value < (double)RAND_MAX * p / 100);
}

// случайная генерация лабиринта
//   каждая стенка ставится с вероятностью prob процентов
//   srand() не вызывается
void Maze::generate_random (int prob)
{
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            // перечисляем все внутренние стенки:
            //   справа и снизу от клеточек (i, j), i=1..n-1, j=1..m-1
            //   справа от клеточек (i, j), i=n, j=1..m-1
            //   снизу от клеточек (i, j), i=1..n-1, j=m

            // с вероятностью prob% ставим стенку справа от клеточки (i, j)
            if (j < m && random_binary(prob))
                walls_v[i][j] = true;
            // с вероятностью prob% ставим стенку под клеточкой (i, j)
            if (i < n && random_binary(prob))
                walls_h[i][j] = true;
        }
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

void clear_screen ()
{
#ifndef WIN_CONSOLE
    // https://stackoverflow.com/questions/17335816/clear-screen-using-c
    cout << "\033[2J\033[1;1H";
#else
    system("cls");
#endif
}

void delay (int ms)
{
    // https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
    this_thread::sleep_for(chrono::nanoseconds(1000000 * ms));
}
