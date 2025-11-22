// game_state.c

#include "game_state.h"

static int GAME_STATE = 0;
static LinkedList_Parent LINKED_LIST;
static ScoreList *Score_List;
static BLOCKTYPE CurrentBlock;
// static int **CurrentBlock;

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
    BLOCKTYPE *block = &BLOCKS[rand() % sizeof(BLOCKS)];
    memset(&CurrentBlock, block, sizeof(BLOCKTYPE));
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

BLOCKTYPE *get_current_block(BLOCKTYPE *block)
{
    return &CurrentBlock;
}