#include "activepiece.h"
#include "action.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

int piece_is_valid(char **field, ActivePiece piece, char action)
{
    int i;
    int j;

    if (action == 'l')
        piece.width--;
    else if (action == 'r')
        piece.width++;
    else if (action == 'd')
        piece.height++;
    else if (action == 'c')
        piece.piece_index = (piece.piece_index + 1) % 4;
    else if (action == 's')
        piece.type = piece.hold_piece;
    i = 0;
    while (i < piece.piece_size)
    {
        j = 0;
        while (j < piece.piece_size)
        {
            if (piece.type[((i * piece.piece_size) + j) + (piece.piece_index * 16)] == '#' && field[piece.height + i][piece.width + j] != ' ')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

void check_rows(char **field, int height, int width, int *points)
{
    int i;
    int j;
    int clear;
    int count;

    count = 0;
    i = 2;
    while (i < height - 2)
    {
        j = 2;
        clear = 1;
        while (j < width - 2 && field[i][j] != '\0')
        {
            if (field[i][j] == ' ')
            {
                clear = 0;
                break;
            }
            j++;
        }
        if (clear)
        {
            clear_row(field[i], width);
            push_down(field, i, width);
            count++;
        }
        i++;
    }
    *points += ((count * count) * 100);
    
}

void check_game_status(char **field, int *gameover, int width)
{
    int i;
    
    i = 0;
    while (i < width)
    {
        if (field[3][i] != ' ')
        {
            *gameover = 1;
            break;
        }
        i++;
    }
}

void egg(void)
{
    int key;
    clear();
    printw(" _        _______           _______  _______  ______   _______  _______ \n");
    printw("( (    /|(  ___  )|\\     /|(  ____ \\(       )(  ___ \\ (  ____ \\(  ____ )\n");
    printw("|  \\  ( || (   ) || )   ( || (    \\/| () () || (   ) )| (    \\/| (    )|\n");
    printw("|   \\ | || |   | || |   | || (__    | || || || (__/ / | (__    | (____)|\n");
    printw("| (\\ \\) || |   | |( (   ) )|  __)   | |(_)| ||  __ (  |  __)   |     __)\n");
    printw("| | \\   || |   | | \\ \\_/ / | (      | |   | || (  \\ \\ | (      | (\\ (   \n");
    printw("| )  \\  || (___) |  \\   /  | (____/\\| )   ( || )___) )| (____/\\| ) \\ \\__\n");
    printw("|/    )_)(_______)   \\_/   (_______/|/     \\||/ \\___/ (_______/|/   \\__/\n");
    printw("\n\n");
    printw(" _______ _________ _______  _______ _________ *        *______ \n");
    printw("(  ____ )\\__   **/( **__ \\(  ____ \\\\__   **/( (    /|(  **__ \\\n");
    printw("| (    )|   ) (   | (    \\/| (    \\/   ) (   |  \\  ( || (    \\/\n");
    printw("| (____)|   | |   | (_____ | |         | |   |   \\ | || (__    \n");
    printw("|  _____)   | |   (_____  )| |         | |   | (\\ \\) ||  **)   \n");
    printw("| (         | |         ) || |         | |   | | \\   || (      \n");
    printw("| )      **_) (___/\\____) || (____/\\___) (___| )  \\  || (____/\\\n");
    printw("|/       \\_______/\\_______)(______/\\_______/|/    )_)(_______/\n");
    printw("\n\n");
    printw(" _______  _______  _______    ___   \n");
    printw("/ ___   )(  **   )/ **_   )  /   )  \n");
    printw("\\/   )  || (  )  |\\/   )  | / /) |  \n");
    printw("    /   )| | /   |    /   )/ (_) (_ \n");
    printw("  */   / | (/ /) |  */   /(____   *)\n");
    printw(" /   */  |   / | | /   */      ) (  \n");
    printw("(   (*_/\\|  (__) |(   (__/\\    | |  \n");
    printw("\\_______/(_______)\\_______/    (_)\n");
    printw("\nPRESS 'ESC'");
    refresh();
    key = 0;
    while (key != 27)
    {
        timeout(1000);
        key = getch();
    }
    system("xdg-open https://www.youtube.com/watch?v=o-YBDTqX_ZU");
}
