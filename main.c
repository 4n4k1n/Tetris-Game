#include <unistd.h>
#include <stdlib.h>

typedef struct {
    int width;
    int height;
	char type;
} ActivePiece;


void putstr(char *str)
{
    while (*str)
    {
        write(1, str, 1);
        str++;
    }
}

char **create_game_field(int height, int width)
{
    char **field;
    int i;

    field = (char **)malloc(sizeof(char *) * height); // allocating the height
    if (!field)
        return (NULL);
    i = 0;
    while (i < height)
    {
        field[i] = (char *)malloc(sizeof(char) * (width + 1)); // +1 for the \0 character
        if (!field[i])
            return (NULL);
        i++;
    }
    return (field);
}

void fill_field_for_start(char **field, int height, int width)
{
    int i_height, j_width;

    i_height = 0;
    while (i_height < height)
    {
        j_width = 0;
        while (j_width < width)
        {
            if (i_height == height - 1 && (j_width == 0 || j_width == width - 1))
                field[i_height][j_width] = '+';
            else if (i_height == height - 1)
                field[i_height][j_width] = '-';
            else if (j_width == 0 || j_width == width - 1)
                field[i_height][j_width] = '|';
            else
                field[i_height][j_width] = ' ';
            j_width++;
        }
        field[i_height][j_width] = '\0';
        i_height++;
    }
}

void print_field(char **field, int height)
{
    int i;

	write(1, "\n", 1);
    i = 0;
    while (i < height)
    {
        putstr(field[i]);
        write(1, "\n", 1);
        i++;
    }
}

void free_field(char **field, int height)
{
    int i;

    i = 0;
    while (i < height)
    {
        free(field[i]);
        i++;
    }
    free(field);
}

void place_piece(char **field, ActivePiece piece, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		field[piece.height][10] = piece.type;
		print_field(field, height);
		if (field[piece.height + 1][10] != ' ')
			break ;
		field[piece.height][10] = ' ';
		sleep(1);
		piece.height = i;
		system("clear");
		i++;
	}
}

int main(void)
{
    int height = 21;
    int width = 23;
    char **field;
	ActivePiece piece = {10, 0, '#'};
	
    field = create_game_field(height, width);
    if (!field)
	{
        putstr("Memory allocation failed\n");
        return (1);
    }
    fill_field_for_start(field, height, width);
	for (int i = 0; i < 20; i++)
	{
		place_piece(field, piece, height);
	}
	free_field(field, height);
    return (0);
}
