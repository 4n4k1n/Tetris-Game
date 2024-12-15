#include <stdlib.h>
#include <ncurses.h>

typedef struct {
    int width;
    int height;
    char *type;
    char *next_piece;
    char *hold_piece;
    int piece_size;
    int piece_index;
    int rounds;
} ActivePiece;

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

void place_piece(char **field, ActivePiece piece, int width, int height)
{
    int i;
    int j;
    int row;
    int col;
    
    if (field == NULL || piece.type == NULL) {
        return;
    }
    i = 0;
    while (i < piece.piece_size) {
        j = 0;
        while (j < piece.piece_size) {
            col = piece.width + j;
            row = piece.height + i;
            if (col >= 0 && col < width && 
                row >= 0 && row < height)
            {
                if (piece.type[((i * piece.piece_size) + j) + (piece.piece_index * 16)] == '#')
                    field[row][col] = '#';
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
