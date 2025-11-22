// game_state.h

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "tetris.h"

// The functions are declared here without the 'static' keyword
// so they can be called from other source files (main.c, etc.).
// Their definition will be in the .c file.

/**
 * set_game_state
 * @brief Sets the current game state
 * @param state The new game state to set
 */
void set_game_state(int state);
/**
 * get_game_state
 * @brief Gets the current game state
 * @return The current game state
 */
int get_game_state();
/**
 * add_node_to_game_list
 * @brief Adds a new node to the game's linked list
 * @param dimension A 3x3 matrix representing the block's shape
 * @param direction The direction associated with the new node
 * @param color The color associated with the new node
 */
void add_node_to_game_list(int dimension[3][3], char *direction, Color color);
/**
 * initialize_game_state
 * @brief Initializes the game state and linked list
 */
void initialize_game_state(void);
/**
 * set_linked_list
 * @brief Sets the linked list to a new list
 * @param new_list A pointer to the new linked list parent structure
 */
void set_linked_list(LinkedList_Parent *new_list);
/**
 * get_linked_list
 * @brief Gets the current linked list
 * @return A pointer to the current linked list parent structure
 */
LinkedList_Parent *get_linked_list(void);
/**
 * get_score_list
 * @brief Gets the current score list
 * @return The current score list
 */
ScoreList *get_score_list(void);
/**
 * get_current_block
 * @brief Gets the current block
 * @return The current block as a pointer to a 2D array
 */
BLOCKTYPE *get_current_block();
/**
 * set_current_block
 * @brief Sets the current block
 * @param block A pointer to a 2D array representing the new current block
 */
void set_current_block(BLOCKTYPE *block);

#endif // GAME_STATE_H