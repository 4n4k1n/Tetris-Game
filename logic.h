#ifndef LOGIC_H
#define LOGIC_H

#include "setstruct.h"
#include "activepiece.h"

void move_piece(char **field, ActivePiece *piece, int height, int width, int *points, int *gameover, Settings settings);

#endif