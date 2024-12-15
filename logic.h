#ifndef LOGIC_H
#define LOGIC_H

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

int piece_is_valid(char **field, ActivePiece piece, char action);
void check_rows(char **field, int height, int width, int *points);
void move_piece(char **field, ActivePiece *piece, int height, int width, int *points, int *gameover);
void check_game_status(char **field, int *gameover, int width);
void gameover_sign(int points);

#endif