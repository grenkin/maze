#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <thread>
#include "maze.h"

using namespace std;

/***********************************************/
#define WIN_CONSOLE

#ifdef WIN_CONSOLE
enum console_chars {
    CH_POINT      = 249,
    CH_VERT_LINE  = 179,
    CH_HORIZ_LINE = 196,
    CH_SPACE      = ' ',
    CH_LINE_BREAK = '\n'
#else
    CH_POINT      = '.',
    CH_VERT_LINE  = '|',
    CH_HORIZ_LINE = '-',
    CH_SPACE      = ' ',
    CH_LINE_BREAK = '\n'
#endif
};

void clear_screen ();
void delay (int ms);
void write (console_chars ch) { putc(ch, stdout); }

/***********************************************/

// вывести лабиринт на экран
void Maze::print ()
{
    clear_screen();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            write(CH_POINT);
            if (j < m) {
                if (walls_v[i][j])
                    write(CH_VERT_LINE);
                else
                    write(CH_SPACE);
            }
        }
        write(CH_LINE_BREAK);
        if (i < n) {
            for (int j = 1; j <= m; ++j) {
                if (walls_h[i][j])
                    write(CH_HORIZ_LINE);
                else
                    write(CH_SPACE);
                write(CH_SPACE);
            }
            write(CH_LINE_BREAK);
        }
    }
}

/***********************************************/

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
