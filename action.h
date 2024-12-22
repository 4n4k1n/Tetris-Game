#ifndef ACTION_H
#define ACTION_H

#include "activepiece.h"

void clear_row(char *row, int width);
void push_down(char **field, int row, int width);
void place_piece(char **field, ActivePiece piece, int width, int height);
void remove_piece(char **field, ActivePiece piece);

#endif