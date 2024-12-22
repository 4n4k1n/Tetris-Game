#ifndef VALID_H
#define VALID_H

#include "activepiece.h"

int piece_is_valid(char **field, ActivePiece piece, char action);
void check_rows(char **field, int height, int width, int *points);
void check_game_status(char **field, int *gameover, int width);

#endif