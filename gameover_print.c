#include <ncurses.h>
#include <string.h>
#include "ranking.h"

void get_player_name(Player *current_player)
{
    clear();
    echo();
    printw("ENTER PLAYER NAME: ");
    refresh();
    getnstr(current_player->name, 49);
    clear();
}

void gameover_sign(Player current_player, Player best_player)
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
    if (current_player.score > best_player.score)
        printw("NEW HIGHSCORE >>%d<< BY '%s'\n", current_player.score, current_player.name);
    else
        printw(
            "HIGHSCORE >>%d<< BY '%s'\n"
            "SCORE >>%d<< BY '%s'\n",
            best_player.score, best_player.name, current_player.score, current_player.name);
    printw("\nPress 'ESC' to quit.\n");
    refresh();
    while (end != 27)
    {
        timeout(50000);
        end = getch();
    }
}