#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "player_struct.h"

int create_table(sqlite3 *db)
{
    int rc;
    char *errMsg = NULL;
    char *sql = 
        "CREATE TABLE IF NOT EXISTS Players("
        "   name VARCHAR(50) UNIQUE NOT NULL,"
        "   score INT NOT NULL);";

    clear();
    rc = sqlite3_exec(db, sql, NULL, NULL, &errMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        refresh();
        sqlite3_free(errMsg);
        return (0);
    }
    return (1); 
}

int check_best_player(sqlite3 *db, Player *best_player)
{
    const char *sql = "SELECT name, score FROM Players ORDER BY score DESC LIMIT 1;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return (0);
    }
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        strcpy(best_player->name, (const char *)sqlite3_column_text(stmt, 0));
        best_player->score = sqlite3_column_int(stmt, 1);
    }
    sqlite3_finalize(stmt);
    return (1);
}

void check_current_player(sqlite3 *db, Player *current_player)
{
    const char *sql = "SELECT score FROM Players WHERE name = ?";
    sqlite3_stmt *stmt = NULL;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, current_player->name, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int current_score = sqlite3_column_int(stmt, 0);
            if (current_player->score > current_score)
            {
                const char *update_sql = "UPDATE Players SET score = ? WHERE name = ?";
                sqlite3_stmt *update_stmt = NULL;
                if (sqlite3_prepare_v2(db, update_sql, -1, &update_stmt, 0) == SQLITE_OK)
                {
                    sqlite3_bind_int(update_stmt, 1, current_player->score);
                    sqlite3_bind_text(update_stmt, 2, current_player->name, -1, SQLITE_STATIC);
                    sqlite3_step(update_stmt);
                }
                sqlite3_finalize(update_stmt);
            }
        }
        else
        {
            const char *insert_sql = "INSERT INTO Players (name, score) VALUES (?, ?)";
            sqlite3_stmt *insert_stmt = NULL;
            if (sqlite3_prepare_v2(db, insert_sql, -1, &insert_stmt, 0) == SQLITE_OK)
            {
                sqlite3_bind_text(insert_stmt, 1, current_player->name, -1, SQLITE_STATIC);
                sqlite3_bind_int(insert_stmt, 2, current_player->score);
                sqlite3_step(insert_stmt);
            }
            sqlite3_finalize(insert_stmt);
        }
    }
    sqlite3_finalize(stmt);
}

int check_highscore(Player *current_player, Player *best_player)
{
    sqlite3 *db;
    int rc;

    clear();
    rc = sqlite3_open("players.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cant open the database: %s\n", sqlite3_errmsg(db));
        refresh();
        return(0);
    }
    if (!create_table(db))
    {
        sqlite3_close(db);
        return (0);
    }
    if (!check_best_player(db, best_player))
    {
        sqlite3_close(db);
        return (0);
    }
    check_current_player(db, current_player);
    sqlite3_close(db);
    return (1);
}
