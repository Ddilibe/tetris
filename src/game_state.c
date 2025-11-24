// game_state.c

#include "game_state.h"

static int GAME_STATE = 0;
static int MOVING = 0;
static LinkedList_Parent LINKED_LIST;
static ScoreList *Score_List;
static BLOCKTYPE CurrentBlock;
static Color CurrentColor;
static FIFOStack *Stack;
static int long long UNIVERSALINSTANCE = 0;
static BitboardList *Bitboard;
// static int **CurrentBlock;

/**
 * We have 18 columns and 23 rows
 */

int get_game_state(void)
{
    return GAME_STATE;
}

void set_game_state(int state)
{
    GAME_STATE = state;
}

LinkedList_Parent *get_linked_list(void)
{
    return &LINKED_LIST;
}

void set_linked_list(LinkedList_Parent *new_list)
{
    LINKED_LIST = *new_list;
}

void initialize_game_state(void)
{
    GAME_STATE = 0;
    LINKED_LIST.head = NULL;
    Score_List = create_score_list();
    // BLOCKTYPE *block = &BLOCKS[rand() % sizeof(BLOCKS)];
    BLOCKTYPE *block = &BLOCKS[rand() % 7];
    set_current_block(block);
    set_current_color(COLORS[rand() % 21]);
    logger_init("log.txt", LOG_LEVEL_WARN);
    init_and_fill_stack();
    init_bitboard();
}

void add_node_to_game_list(int dimension[3][3], char *direction, Color color)
{
    if (LINKED_LIST.head == NULL)
    {
        LinkedList_Parent *new_list = create_linked_list(dimension, direction, color);
        set_linked_list(new_list);
    }
    else
    {
        add_node(&LINKED_LIST, dimension, direction, color);
    }
}

ScoreList *get_score_list(void)
{
    return Score_List;
}

void set_current_block(BLOCKTYPE *block)
{
    memcpy(&CurrentBlock, block, sizeof(BLOCKTYPE));
}

BLOCKTYPE *get_current_block()
{
    return &CurrentBlock;
}

void move_current_block()
{
    BLOCKTYPE *block = get_current_block();
    // Logic to move the block down by one unit
    int length = 800 / BLOCK_SIZE;

    if (IsKeyPressed(KEY_LEFT) && left_check(block))
    {
        block->dimension[0] = block->dimension[0] - 1;
        block->number = block->number >> 1;
    }
    if (IsKeyPressed(KEY_RIGHT) && right_check(block))
    {
        block->dimension[0] = block->dimension[0] + 1;
        block->number = block->number << 1;
    }
    if (IsKeyPressed(KEY_DOWN) && down_check(block))
    {
        block->dimension[1] = block->dimension[1] + 1;
        block->number = block->number >> length;
    }
    if (IsKeyPressed(KEY_UP) && up_check(block))
    {
        block->dimension[1] = block->dimension[1] - 1;
        block->number = block->number << length;
    }
    if (IsKeyPressed(KEY_R))
    {
        int **rotated = Rotate_Matrix(block, ROTATE_CW);
        print_2d_array(rotated, 3, 3);
        int newshape[3][3];
        memcpy(newshape, block->shape, sizeof(int[3][3]));
        memcpy(block->shape, rotated, sizeof(int[3][3]));

        if (!rotation_check(block))
            memcpy(block->shape, newshape, sizeof(int[3][3]));
        // block->shape = rotated;
    }
}

void automate_moving_down()
{
    if (down_check(get_current_block()))
    {
        if (MOVING % 20 == 0)
        {
            BLOCKTYPE *block = get_current_block();
            int length = (800 / BLOCK_SIZE) - 3;

            block->dimension[1] = block->dimension[1] + 1;
            block->number = block->number >> length;

            printf("INFO: Dimension: X-> %d Y-> %d\n", block->dimension[0], block->dimension[1]);
        }
    }
    else
    {
        change_block();
    }
}

void set_moving_state(int num)
{
    MOVING = num;
}

void update_moving_state()
{
    MOVING += 1;
}

int get_moving_state()
{
    return MOVING;
}

FIFOStack *init_and_fill_stack()
{
    Stack = malloc(sizeof(FIFOStack));
    Stack->items = malloc(sizeof(BLOCKTYPE) * STACK_CAPACITY);
    Stack->size = 0;

    for (int i = 0; i < STACK_CAPACITY; i++)
    {
        BLOCKTYPE *blk = &BLOCKS[rand() % 7];
        Color color = COLORS[rand() % 21];

        Stack->items[Stack->size] = *blk;
        Stack->color[Stack->size] = color;

        Stack->size++;
    }

    return Stack;
}

BLOCKTYPE *push_fifo(BLOCKTYPE newBlock)
{
    BLOCKTYPE toReturn = Stack->items[0];
    Color oldColor = Stack->color[0];
    // memcpy(&toReturn, &Stack->items[0], sizeof(BLOCKTYPE));
    if (Stack->size == STACK_CAPACITY)
    {
        // shift everything left (remove first)
        for (int i = 1; i < STACK_CAPACITY; i++)
        {
            Stack->items[i - 1] = Stack->items[i];
            Stack->color[i - 1] = Stack->color[i];
        }
        Stack->items[STACK_CAPACITY - 1] = newBlock;
        Stack->color[STACK_CAPACITY - 1] = COLORS[rand() % 21];
    }
    else
    {
        Stack->items[Stack->size++] = newBlock;
        Stack->color[Stack->size] = COLORS[rand() % 21];
    }
    set_current_block(&toReturn);
    set_current_color(oldColor);
    return &toReturn;
}

BLOCKTYPE *get_fifo_index(int index)
{
    if (index >= 3)
    {
        printf("ERROR: Invalid index for FIFO Stack");
        return NULL;
    }
    if (index < 0)
    {
        printf("ERROR: Invalid index for FIFO Stack");
        return NULL;
    }

    return &Stack->items[index];
}

Color get_color_index(int index)
{
    if (index >= 3)
    {
        printf("ERROR: Invalid index for FIFO Stack");
        return RED;
    }
    if (index < 0)
    {
        printf("ERROR: Invalid index for FIFO Stack");
        return RED;
    }

    return Stack->color[index];
}

void change_block()
{
    BLOCKTYPE *blk = &BLOCKS[rand() % 7];
    BLOCKTYPE *oldblk = push_fifo(*blk);

    // set_current_block(oldblk);
}

BitboardList *get_bitboard()
{
    return Bitboard;
}

void *init_bitboard(void)
{
    Bitboard = malloc(sizeof(BitboardList));
    Bitboard->head = NULL;
    Bitboard->value = 0;
}

Color get_current_color()
{
    return CurrentColor;
}

void set_current_color(Color color)
{
    CurrentColor = color;
}