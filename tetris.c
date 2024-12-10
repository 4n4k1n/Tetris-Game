#include <ncurses.h>
#include <stdlib.h>

typedef struct {
    int width;
    int height;
    char type;
} ActivePiece;

char **create_game_field(int height, int width)
{
    char **field;
    int i;
    
    field = (char **)malloc(sizeof(char *) * height); 
    if (!field)
        return (NULL);
    
    i = 0;
    while (i < height)
    {
        field[i] = (char *)malloc(sizeof(char) * (width + 1)); 
        if (!field[i])
        {
            while (i > 0)
            {
                i--;
                free(field[i]);
            }
            free(field);
            return (NULL);
        }
        i++;
    }
    return (field);
}

void fill_field_for_start(char **field, int height, int width)
{
    int i_height;
	int	j_width;
    
    i_height = 0;
    while (i_height < height)
    {
        j_width = 0;
        while (j_width < width)
        {
            field[i_height][j_width] = ' ';
            j_width++;
        }
        field[i_height][j_width] = '\0';
        i_height++;
    }
}

void put_row(char *row)
{
    printw("|%s|", row);
}

void put_field(char **field, int height, int width)
{
    int i;

    i = 0;
    while (i < height)
    {
        put_row(field[i]);
        printw("\n");
        i++;
    }
    i = 0;
    printw("+");
    while (i < width)
    {
        printw("-");
        i++;
    }
    printw("+");
    refresh();
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

void clear_row(char *row)
{
    while (*row)
    {
        *row = ' ';
        row++;
    }
}

void check_rows(char **field, int height)
{
    int i;
    int j;
    int clear;

    while (i < height)
    {
        j = 0;
        clear = 1;
        while (field[j][i])
        {
            if (field[j][i] == ' ')
            {
                clear = 0;
                break;
            }
            j++;
        }
        if (clear)
            clear_row(field[i]);
        i++;
    }
}

void move_piece(char **field, ActivePiece *piece, int height, int width)
{
    int i;
    int key;

    piece->height = 0;
    while (piece->height < height)
    {
        i = 0;
        while (i < 10)
        {
            field[piece->height][piece->width] = piece->type;
            put_field(field, height, width);
            field[piece->height][piece->width] = ' ';
            timeout(100);
            key = getch();
            if (key == KEY_LEFT)
                piece->width--;
                if (piece->width < 0)
                    piece->width++;
            else if (key == KEY_RIGHT)
                piece->width++;
                if (piece->width > height - 1)
                    piece->width--;
            i++;
            clear();
        }
        field[piece->height][piece->width] = piece->type;
        put_field(field, height, width);
        if (piece->height == height - 1)
        {
            check_rows(field, height);
            clear();
            break;
        }
        if (field[piece->height + 1][piece->width] != ' ')
        {
            check_rows(field, height);
            clear();
            break;
        }
        field[piece->height][piece->width] = ' ';
        piece->height++;
        clear();
    }
}

void check_game_status(char **field, int *gameover, int width)
{
    int i;
    
    i = 0;
    while (i < width)
    {
        if (field[0][i] != ' ')
        {
            *gameover = 1;
            break;
        }
        i++;
    }
}

int main(void)
{
    int key;
    int width = 20;
    int height = 20;
    char **field;
    int gameover;
    ActivePiece piece = {0, 0, '#'};

    initscr();
    keypad(stdscr, TRUE);
    field = create_game_field(height, width);
    if (!field)
    {
        printw("Memory allocation failed\n");
        return (1);
    }
    fill_field_for_start(field, height, width);
    put_field(field, height, width);
    gameover = 0;
    while (!gameover)
    {
        move_piece(field, &piece, height, width);
        check_game_status(field, &gameover, width);
        if (piece.width == width - 1)
            piece.width = 0;
        else
            piece.width++;
    }
    free_field(field, height);
    key = getch();
    endwin();
    return (0);
}
