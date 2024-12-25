#include <stdlib.h>
#include <ncurses.h>
#include "activepiece.h"

void reset_cords(ActivePiece *piece)
{
    int i;

    i = 0;
        while (i < 4)
        {
            piece->cords_y[i] = 0;
            piece->cords_x[i] = 0;
            i++;
        }
}

void clear_row(char *row, int width)
{
	int i;

	i = 2;
    while (i < width - 2)
    {
        row[i] = ' ';
        i++;
    }
}

void push_down(char **field, int row, int width)
{
    int i;

    while (row > 2)
    {
        i = 2;
        while (i < width - 2)
        {
            field[row][i] = field[row - 1][i];
            i++;
        }
        row--;
    }
}

void place_piece(char **field, ActivePiece *piece, int width, int height)
{
    int i;
    int j;
    int k;
    int row;
    int col;
    
    if (field == NULL || piece->type == NULL) {
        return;
    }
    i = 0;
    while (i < piece->piece_size) {
        j = 0;
        while (j < piece->piece_size) {
            k = 0;
            col = piece->width + j;
            row = piece->height + i;
            if (col >= 0 && col < width && 
                row >= 0 && row < height)
            {
                if (piece->type[((i * piece->piece_size) + j) + (piece->piece_index * 16)] == '#')
                {
                    field[row][col] = '#';
                    if (piece->cords_x[j] == 0 && piece->cords_y[j] == 0)
                    {
                        while (field[row + k + 1][col] != '#' && field[row + k + 1][col] != '-' && field[row + k + 1][col] != '!')
                            k++;
                        piece->cords_x[j] = col;
                        piece->cords_y[j] = row + k;
                        field[row + k][col] = '!';
                    }
                }
            }
            j++;
        }
        i++;
    }
}

void remove_piece(char **field, ActivePiece piece)
{
	int i;
	int j;

    i = 0;
    while (i < 4)
    {
        field[piece.cords_y[i]][piece.cords_x[i]] = ' ';
        i++;
    }
	i = 0;
	while (i < piece.piece_size)
    {
        j = 0;
        while (j < piece.piece_size)
        {
            if (piece.type[((i * piece.piece_size) + j) + (piece.piece_index * 16)] == '#')
                field[piece.height + i][piece.width + j] = ' ';
            j++;
        }
        i++;
    }
}
