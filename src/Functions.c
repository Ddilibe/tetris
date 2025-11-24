
#include "tetris.h"

int **Rotate_Matrix(BLOCKTYPE *newBLock, char *direction)
{
    int matrix[3][3];
    memcpy(matrix, newBLock->shape, sizeof(int[3][3]));
    static int rotated[3][3];
    int i, j;

    if (strcmp(direction, ROTATE_CW) == 0)
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                rotated[j][2 - i] = matrix[i][j];
            }
        }
    }
    else if (strcmp(direction, ROTATE_CCW) == 0)
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                rotated[2 - j][i] = matrix[i][j];
            }
        }
    }
    else
    {
        // Invalid direction, return the original matrix
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                rotated[i][j] = matrix[i][j];
            }
        }
    }

    // BLOCKTYPE *rotate_block;
    // rotate_block = malloc(sizeof(BLOCKTYPE));
    // // memcpy(rotate_block, newBLock, sizeof(BLOCKTYPE));
    // memcpy(rotate_block->shape, rotated, sizeof(rotated));
    // *rotate_block->dimension = newBLock->dimension;

    return rotated;
}

void DrawMatrix(int matrix[3][3], int startX, int startY, int blockSize, Color color)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix[i][j] != 0)
            {
                DrawRectangle((startX + j) * blockSize, (startY + i) * blockSize, blockSize, blockSize, color);
            }
        }
    }
}

void draw_grid()
{

    Color gridColor = LIGHTGRAY;
    int GRID_ROWS = 800 / BLOCK_SIZE;  // 800
    int GRID_COLS = 1280 / BLOCK_SIZE; // 1280

    for (int row = 3; row < GRID_ROWS; row++)
    {
        // printf("Columns starts from %d to %d\n", row * BLOCK_SIZE, GRID_COLS);
        for (int col = 24; col < GRID_COLS; col++)
        {
            Vector2 mouse_pos = GetMousePosition();
            // printf("Rows: Starts from %d to %d\n", col * BLOCK_SIZE, GRID_ROWS);
            Rectangle block_pos = {col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
            if (IsMouseButtonPressed(1))
            {
                LOG_DEBUG("mouse_pos.x, mouse_pos.y");
            }
            if (CheckCollisionPointRec(mouse_pos, block_pos))
            {
                DrawRectangle(col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLUE);
            }
            else
            {
                DrawRectangle(col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, gridColor);
            }
            DrawRectangleLines(col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, GRAY);
        }
    }
}

