#include <ncurses.h>
#include "setstruct.h"

void display_settings(Settings settings, int end)
{
    if (end == '0')
    {
        printw("1. LEFT >>>>>>>>> '%c'\n", settings.left);
        printw("2. RIGHT >>>>>>>> '%c'\n", settings.right);
        printw("3. ROTATE >>>>>>> '%c'\n", settings.rotate);
        printw("4. SOFT DROP >>>> '%c'\n", settings.soft);
        printw("5. HARD DROP >>>> '%c'\n", settings.hard);
        printw("6. HOLD PIECE >>> '%c'\n", settings.hold);
        printw("7. END SETTINGS > 'ENTER'\n");
    }
    else if (end == '1')
        printw("LEFT >> ");
    else if (end == '2')
        printw("RIGHT >> ");
    else if (end == '3')
        printw("ROTATE >> ");
    else if (end == '4')
        printw("SOFT DROP >> ");
    else if (end == '5')
        printw("HARD DROP >> ");
    else if (end == '6')
        printw("HOLD PIECE >> ");
    refresh();
}

void get_settings(Settings *settings)
{
    int end;

    while (end != '\n')
    {
        end = '0';
        display_settings(*settings, end);
        end = getch();
        clear();
        display_settings(*settings, end);
        if (end == '1')
            settings->left = getch();
        else if (end == '2')
            settings->right = getch();
        else if (end == '3')
            settings->rotate = getch();
        else if (end == '4')
            settings->soft = getch();
        else if (end == '5')
            settings->hard = getch();
        else if (end == '6')
            settings->hold = getch();
        clear();
    }
}
