#ifndef ACTIVEPIECE_H
#define ACTIVEPIECE_H

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

#endif