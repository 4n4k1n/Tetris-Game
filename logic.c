#include <ncurses.h>
#include "action.h"
#include "field.h"

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
    {
        piece.piece_index = (piece.piece_index + 1) % 4;
    }
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

void move_piece(char **field, ActivePiece *piece, int height, int width, int *points)
{
    int key;
	int i;
    static int speed = 100;

	i = 1;
    while (piece->height < height - 3)
    {
        place_piece(field, *piece, width, height);
        put_field(field, height, *points);
        remove_piece(field, *piece);
        timeout(speed);
        key = getch();
        if (key == 'a')
        {
            if (piece_is_valid(field, *piece, 'l'))
                piece->width--;
        }
        else if (key == 'd')
        {
            if (piece_is_valid(field, *piece, 'r'))
                piece->width++;
        }
        else if (key == 's')
        {
            if (piece_is_valid(field, *piece, 'd'))
                piece->height++;
        }
        else if (key == 'w')
        {
            if (piece_is_valid(field, *piece, 'c'))
                piece->piece_index = (piece->piece_index + 1) % 4;
        }
		if (i % 10 == 0)
        {
            if (!piece_is_valid(field, *piece, 'd'))
                break;
			piece->height++;
        }
        clear();
		i++;
    }
    place_piece(field, *piece, width, height);
    put_field(field, height, *points);
    check_rows(field, height, width, points);
    if (piece->rounds % 10 == 0 && speed > 20)
        speed -= 2;
    clear();
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