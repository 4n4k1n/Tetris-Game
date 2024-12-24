#include <ncurses.h>

void gameover_sign(int points, int highscore)
{
    char end;

    end = 0;
    clear();
    printw("  __ _  __ _ _ __ ___   ___  _____   _____ _ __ \n");
    printw(" / _` |/ _` | '_ ` _ \\ / _ \\/ _ \\ \\ / / _ \\ '__|\n");
    printw("| (_| | (_| | | | | | |  __/ (_) \\ V /  __/ |  \n");
    printw(" \\__, |\\__,_|_| |_| |_|\\___|\\___/ \\_/ \\___|_| \n");
    printw("  __/ |                               @SKYW4LK3R\n");
    printw(" |___/   \n\n");
    if (points > highscore)
        printw("NEW HIGHSCORE >>%d<<\n\n", points);
    else
        printw("HIGHSCORE >>%d<<\nSCORE >%d<\n\n", highscore, points);
    printw("Press 'ESC' to quit.\n");
    refresh();
    while (end != 27)
    {
        timeout(50000);
        end = getch();
    }
}