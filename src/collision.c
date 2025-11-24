#include "tetris.h"
#include "game_state.h"

bool right_check(BLOCKTYPE *block)
{
    int number = 0;
    if (block->dimension[0] < 39)
        return true;
    else
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (block->shape[i][2] == 1)
                number += 1;
        }

        return number == 0;
    }
}

bool left_check(BLOCKTYPE *block)
{
    int number = 0;
    if (block->dimension[0] > 24)
        return true;
    else
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (block->shape[i][0] == 1)
                number += 1;
        }

        return number == 0;
    }
}

bool up_check(BLOCKTYPE *block)
{
    int number = 0;

    if (block->dimension[1] > 3)
        return true;
    else
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (block->shape[0][i] == 1)
                number += 1;
        }

        return number == 0 && (block->dimension[1] > 3);
    }
}

bool down_check(BLOCKTYPE *block)
{
    int number = 0;
    if (block->dimension[1] < 24)
        return true;
    else
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (block->shape[2][i] == 1)
                number += 1;
        }

        return number == 0 && block->dimension[1] < 24;
    }
}

bool rotation_check(BLOCKTYPE *block)
{

    if (!up_check(&block))
        return false;
    if (!down_check(&block))
        return false;
    if (!left_check(&block))
        return false;
    if (!right_check(&block))
        return false;
    return true;
}