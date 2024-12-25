#ifndef ACTIVEPIECE_H
#define ACTIVEPIECE_H

typedef struct
{
    int width;
    int height;
    char *type;
    char *next_piece;
    char *hold_piece;
    int piece_size;
    int piece_index;
    int rounds;
    int cords_y[4];
    int cords_x[4];
} ActivePiece;

#endif