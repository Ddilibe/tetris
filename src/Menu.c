#include "tetris.h"
#include "game_state.h"

bool IsButtonClicked(int x, int y, int width, int height)
{
    Vector2 mousePos = GetMousePosition();
    Rectangle buttonRect = {x - width / 2, y - height / 2, width, height};

    return CheckCollisionPointRec(mousePos, buttonRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void DrawButton(int x, int y, int width, int height, const char *text)
{
    Vector2 mousePos = GetMousePosition();
    Rectangle buttonRect = {x - width / 2, y - height / 2, width, height};

    // Check if mouse is hovering over the button
    bool isHovered = CheckCollisionPointRec(mousePos, buttonRect);

    // Draw button with different color if hovered
    Color buttonColor = isHovered ? SKYBLUE : DARKBLUE;
    DrawRectangle(buttonRect.x, buttonRect.y, buttonRect.width, buttonRect.height, buttonColor);

    // Draw button border
    DrawRectangleLines(buttonRect.x, buttonRect.y, buttonRect.width, buttonRect.height, WHITE);

    // Draw the text centered on the button
    int textWidth = MeasureText(text, 20);
    DrawText(text, x - textWidth / 2, y - 10, 20, WHITE);
}

void display_menu()
{
    char *title = "Tetris Menu";
    int titleLength = MeasureText(title, 90);
    DrawText(title, (GetScreenWidth() / 2) - titleLength / 2, 200, 90, WHITE);
    DrawButton(540, 400, 200, 50, "Start Game");
    DrawButton(540, 450, 200, 50, "High Scores");
    DrawButton(540, 500, 200, 50, "Options");
    DrawButton(540, 550, 200, 50, "Instructions");
    DrawButton(540, 600, 200, 50, "Exit");

    // Check for button clicks and handle them
    if (IsButtonClicked(540, 400, 200, 50))
    {
        set_game_state(GAME_PLAY);
    }
    else if (IsButtonClicked(540, 450, 200, 50))
    {
        set_game_state(HIGH_SCORES);
    }
    else if (IsButtonClicked(540, 500, 200, 50))
    {
        set_game_state(OPTIONS);
    }
    else if (IsButtonClicked(540, 600, 200, 50))
    {
        set_game_state(EXIT_GAME);
    }
    else if (IsButtonClicked(540, 550, 200, 50))
    {
        set_game_state(INSTRUCT);
    }
}