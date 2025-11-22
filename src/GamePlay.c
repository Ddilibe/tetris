#include "tetris.h"
#include "game_state.h"

int score = 0;
int level = 1;
int main_block[3][3];

void play_game()
{
    // int **current_block = get_current_block();
    // memcpy(main_block, BLOCKA, sizeof(BLOCKA));
    // Texture wabbit = LoadTexture("wabbit_alpha.png");
    score += 1 ? level % 20 == 0 : score;

    DrawText(TextFormat("Tetris %d", score), 200, 200, 20, WHITE);
    DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), GREEN);

    if (IsKeyPressed(KEY_R))
    {
        int **rotated = Rotate_Matrix(main_block, ROTATE_CW);
        memcpy(main_block, rotated, sizeof(main_block));
    }
    else if (IsKeyPressed(KEY_P))
    {
        set_game_state(PAUSE_MENU);
    }

    draw_grid();

    DrawButton(300, 650, 100, 50, "Pause");
    DrawButton(220, 710, 100, 50, "Reset");
    DrawButton(380, 710, 100, 50, "Menu");

    if (IsButtonClicked(300, 650, 100, 50))
    {
        set_game_state(PAUSE_MENU);
    }
    if (IsButtonClicked(220, 710, 100, 50))
    {
        set_game_state(RESET);
    }
    if (IsButtonClicked(380, 710, 100, 50))
    {
        set_game_state(MAIN_MENU);
    }

    DrawRectangleLines(50, 250, 100, 100, GRAY);
    DrawRectangleLines(200, 250, 100, 100, GRAY);
    DrawRectangleLines(350, 250, 100, 100, GRAY);

    // DrawMatrix(BLOCKS[rand() % sizeof(BLOCKS)], 51, 251, BLOCK_SIZE, COLORS[rand() % sizeof(COLORS)]);

    // DrawGrid(10, 20);
    BLOCKTYPE *block = get_current_block();
    DrawMatrix(block->shape, 600, 200, 30, RED);

    level += 1;
}

void display_game_over()
{
    DrawText("Game Over!", 350, 200, 40, RED);
    DrawText("Press ENTER to return to the main menu", 200, 300, 20, WHITE);
}

void reset_game()
{
    score = 0;
    level = 1;
}

void display_pause_menu()
{
    if (get_game_state() == PAUSE_MENU)
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            set_game_state(GAME_PLAY);
        }
    }
    DrawText("Game Paused", 350, 200, 40, YELLOW);
    DrawText("Press P to Resume", 300, 300, 20, WHITE);
}

void display_high_scores()
{
    char *menu = "High Scores";
    int menuLength = MeasureText(menu, 90);
    DrawText(menu, (GetScreenWidth() / 2) - menuLength / 2, 200, 90, GOLD);
    ScoreList *list = get_score_list();

    if (list != NULL)
    {
        if (list->entries != NULL)
        {
            for (size_t i = 0; i < list->size; i++)
            {
                char scoreEntry[100];
                snprintf(scoreEntry, sizeof(scoreEntry), "%zu. \t%s - %d", i + 1, list->entries[i].name, list->entries[i].score);
                DrawText(scoreEntry, 600, 400 + (i * 30), 20, WHITE);
            }
            return;
        }
    }
    char *high_score_text = "No high scores available.";
    int length = MeasureText(high_score_text, 20);
    DrawText("No high scores available.", length / 2, 400, 20, WHITE);
    return;
}
