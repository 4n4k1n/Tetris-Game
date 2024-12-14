#include <ncurses.h>
#include <stdlib.h>
#include "pieces.h"
#include "field.h"
#include <time.h>

typedef struct {
    int width;
    int height;
    char *type;
    int piece_size;
    int piece_index;
} ActivePiece;

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

void check_rows(char **field, int height, int width, int *points)
{
    int i;
    int j;
    int clear;

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
            *points += 100;
        }
        i++;
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
                if (piece.type[j + (piece.piece_index * 16)] == '#')
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

void move_piece(char **field, ActivePiece *piece, int height, int width, int *points)
{
    int key;
	int i;

	i = 1;
    while (piece->height < height - 3)
    {
        place_piece(field, *piece, width, height);
        put_field(field, height, width, *points);
        remove_piece(field, *piece);
        timeout(100);
        key = getch();
        if (key == KEY_LEFT)
        {
            if (piece_is_valid(field, *piece, 'l'))
                piece->width--;
        }
        else if (key == KEY_RIGHT)
        {
            if (piece_is_valid(field, *piece, 'r'))
                piece->width++;
        }
        else if (key == KEY_DOWN)
        {
            if (piece_is_valid(field, *piece, 'd'))
                piece->height++;
        }
        else if (key == KEY_UP)
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
    put_field(field, height, width, *points);
    check_rows(field, height, width, points);
    clear();
}

void check_game_status(char **field, int *gameover, int width)
{
    int i;
    
    i = 0;
    while (i < width)
    {
        if (field[1][i] != ' ' && field[0][i] != ' ')
        {
            *gameover = 1;
            break;
        }
        i++;
    }
}

void push_down(char **field, int height)
{
    int stop;

    stop = 0;
    while (height > 0)
    {

    }
}

int main(void)
{
    int key;
    int width = 10 + 4;
    int height = 20 + 4;
    char **field;
	int gameover;
    ActivePiece piece = {9, 0, pieces[0], 4, 0};
    int points = 0;

	srand(time(NULL));
    field = create_game_field(height, width);
    if (!field)
    {
        printf("Memory allocation failed\n");
        return (1);
    }
    fill_field_for_start(field, height, width);
    initscr();
    keypad(stdscr, TRUE);
	gameover = 0;
	while (!gameover)
	{
		piece.type = pieces[rand() % 7];
		piece.height = 2;
		piece.width = 4;
        move_piece(field, &piece, height, width, &points);
        check_game_status(field, &gameover, width);
	}
    put_field(field, height, width, points);
    key = getch();
    free_field(field, height);
    endwin();
    return (0);
}
