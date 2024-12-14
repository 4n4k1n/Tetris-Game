#ifndef FIELD_H
#define FIELD_H

char **create_game_field(int height, int width);
void fill_field_for_start(char **field, int height, int width);
void put_row(char *row);
void put_field(char **field, int height, int points);
void free_field(char **field, int height);

#endif