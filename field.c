#include "field.h"
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
            if (i_height == 0 || i_height == 1)
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

void put_field(char **field, int height, int width, int points)
{
    int i;

    i = 0;
    while (i < height)
    {
        put_row(field[i]);
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