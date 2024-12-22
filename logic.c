#include <ncurses.h>
#include "action.h"
#include "field.h"
#include "setstruct.h"
#include "activepiece.h"
#include "valid.h"

void move_piece(char **field, ActivePiece *piece, int height, int width, int *points, int *gameover, Settings settings)
{
    int key;
	int i;
    static int speed = 50;
    char *switch_piece;

    if (!piece_is_valid(field, *piece, 'x'))
    {
        *gameover = 1;
        return ;
    }
	i = 1;
    switch_piece = NULL;
    while (piece->height < height - 3)
    {
        place_piece(field, *piece, width, height);
        put_field(field, height, *points, (*piece).next_piece, (*piece).hold_piece);
        remove_piece(field, *piece);
        timeout(speed);
        key = getch();
        if (key == settings.left)
        {
            if (piece_is_valid(field, *piece, 'l'))
                piece->width--;
        }
        else if (key == settings.right)
        {
            if (piece_is_valid(field, *piece, 'r'))
                piece->width++;
        }
        else if (key == settings.soft)
        {
            if (piece_is_valid(field, *piece, 'd'))
            {
                piece->height++;
                i = 1;
            }
        }
        else if (key == settings.rotate)
        {
            if (piece_is_valid(field, *piece, 'c'))
                piece->piece_index = (piece->piece_index + 1) % 4;
        }
        else if (key == settings.hard)
        {
            while (piece_is_valid(field, *piece, 'd'))
            {
                piece->height++;
            }
            break;
        }
        else if (key == 27)
        {
            *gameover = 1;
            return ;
        }
        else if (key == settings.hold && switch_piece == NULL)
        {
            if (piece->hold_piece == NULL)
                {
                    piece->hold_piece = piece->type;
                    return;
                }
            else if (piece_is_valid(field, *piece, 's'))
            {
                piece->height = 2;
                piece->width = 4;
                switch_piece = piece->type;
                piece->type = piece->hold_piece;
                piece->hold_piece = switch_piece;
            }
        }
		if (i % 20 == 0)
        {
            if (!piece_is_valid(field, *piece, 'd'))
                break;
			piece->height++;
        }
        clear();
		i++;
    }
    place_piece(field, *piece, width, height);
    put_field(field, height, *points, (*piece).next_piece, (*piece).hold_piece);
    check_rows(field, height, width, points);
    if (piece->rounds % 10 == 0 && speed > 20)
        speed -= 2;
    clear();
}
