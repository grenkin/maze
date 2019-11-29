#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

// закомментировать в Linux
#define WIN_CONSOLE

namespace console {
    void clear_screen ();
    void delay (int ms);
    void pause ();
    void write (char ch, FILE *out = stdout);
}

#endif // CONSOLE_H_INCLUDED
