#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "pieces.h"
#include "field.h"
#include "logic.h"
#include "setstruct.h"
#include "settings.h"
#include "ranking.h"
#include "activepiece.h"
#include "valid.h"
#include "gameover_print.h"

int main(void)
{
    int width = 10 + 4;
    int height = 20 + 6;
    char **field;
	int gameover;
    ActivePiece piece = {9, 0, NULL, NULL, NULL, 4, 0, 0, {0, 0, 0, 0}, {0, 0, 0, 0}};
    Settings settings = {KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, ' ', 'z'};
    int points = 0;
    int highscore;

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
    get_settings(&settings);
    noecho();
	gameover = 0;
    piece.next_piece = pieces[rand() % 7];
	while (!gameover)
	{
		piece.type = piece.next_piece;
        piece.next_piece = pieces[rand() % 7];
		piece.height = 2;
		piece.width = 4;
        piece.rounds++;
        move_piece(field, &piece, height, width, &points, &gameover, settings);
        check_game_status(field, &gameover, width);
	}
    put_field(field, height, points, piece.next_piece, piece.hold_piece);
    free_field(field, height);
    highscore = check_highscore("highscore.txt", points);
    gameover_sign(points, highscore);
    endwin();
    return (0);
}
