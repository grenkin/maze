#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "console.h"

using namespace std;

namespace console {

    void clear_screen ()
    {
    #ifndef WIN_CONSOLE
        // https://stackoverflow.com/questions/17335816/clear-screen-using-c
        cout << "\033[2J\033[1;1H";
    #else
        system("cls");
    #endif // WIN_CONSOLE
    }

    void delay (int ms)
    {
        // https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
        this_thread::sleep_for(chrono::nanoseconds(1000000 * ms));
    }

    void pause ()
    {
        // https://stackoverflow.com/questions/1449324/how-to-simulate-press-any-key-to-continue
    #ifdef WIN_CONSOLE
        system("pause");
    #else
        system("read");
    #endif // WIN_CONSOLE
    }

    void write (char ch, FILE *out)
    {
        putc(ch, out);
    }

}
