#include "field.h"
#include "action.h"
#include <ncurses.h>
#include <stdlib.h>

char **create_game_field(int height, int width)
{
    char **field;
    int i;
    
    field = (char **)malloc(sizeof(char *) * height); 
    if (!field)
        return (NULL);
    
    i = 0;
    while (i < height)
    {
        field[i] = (char *)malloc(sizeof(char) * (width + 1)); 
        if (!field[i])
        {
            while (i > 0)
            {
                i--;
                free(field[i]);
            }
            free(field);
            return (NULL);
        }
        i++;
    }
    return (field);
}

void fill_field_for_start(char **field, int height, int width)
{
    int i_height;
	int	j_width;
    
    i_height = 0;
    while (i_height < height)
    {
        j_width = 0;
        while (j_width < width)
        {
            if (i_height >= 0 && i_height <= 3 )
                field[i_height][j_width] = ' ';
            else if (j_width == 0 || j_width == 1 || j_width == width - 1 || j_width == width - 2)
                field[i_height][j_width] = '|';
            else if (i_height == height - 1 || i_height == height - 2)
                field[i_height][j_width] = '-';
            else    
                field[i_height][j_width] = ' ';
            j_width++;
        }
        field[i_height][j_width] = '\0';
        i_height++;
    }
}

void put_row(char *row)
{
    printw("%s", row);
}

void put_next_piece(char *row, int index)
{
    int i;

    i = 0;
    while (i < 4)
    {
        printw("%c", row[i + (4 * index)]);
    }
    printw("|");
}


void put_field(char **field, int height, int points, char *next_piece, char *hold_piece)
{
    int i;

    i = 0;
    while (i < height)
    {
        if (i >= 4 && i <= 10)
        {
            if (i == 4)
                printw("         HOLD ");
            else if (i == 5 || i == 10)
                printw("       -------");
            else
            {
                if (hold_piece == NULL)
                    printw("       |      ");
                else
                    printw("       | %c%c%c%c ", hold_piece[((i - 6) * 4)], hold_piece[((i - 6) * 4) + 1], hold_piece[((i - 6) * 4) + 2], hold_piece[((i - 6) * 4) + 3]);
            }
        }
        else
            printw("              ");
        put_row(field[i]);
        if (i >= 4 && i <= 10)
        {
            if (i == 4)
                printw(" NEXT");
            else if (i == 5 || i == 10)
                printw("-------");
            else
                printw(" %c%c%c%c |", next_piece[((i - 6) * 4)], next_piece[((i - 6) * 4) + 1], next_piece[((i - 6) * 4) + 2], next_piece[((i - 6) * 4) + 3]);
        }
        printw("\n");
        i++;
    }
    printw("Points: %d", points);
    refresh();
}

void free_field(char **field, int height)
{
    int i;
    
    i = 0;
    while (i < height)
    {
        free(field[i]);
        i++;
    }
    free(field);
}
