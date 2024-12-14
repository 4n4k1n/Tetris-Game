#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "pieces.h"
#include "field.h"
#include "logic.h"

int main(void)
{
    int key;
    int width = 10 + 4;
    int height = 20 + 6;
    char **field;
	int gameover;
    ActivePiece piece = {9, 0, pieces[0], 4, 0, 0};
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
        piece.rounds++;
        move_piece(field, &piece, height, width, &points);
        check_game_status(field, &gameover, width);
	}
    put_field(field, height, points);
    key = getch();
    free_field(field, height);
    endwin();
    if (key == 'q')
        return (1);
    return (0);
}
