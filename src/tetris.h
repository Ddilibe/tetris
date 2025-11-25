#if !defined(TETRIS_H)
#define TETRIS_H

// Constants for rotation directions
#define ROTATE_CW "CW"
#define ROTATE_CCW "CCW"

// Game States
#define MAIN_MENU 0
#define GAME_PLAY 1
#define HIGH_SCORES 2
#define OPTIONS 3
#define EXIT_GAME 4
#define PAUSE_MENU 5
#define GAME_OVER 6
#define INSTRUCT 7
#define RESET 8

#define BLOCK_SIZE 30
#define STACK_CAPACITY 3

#define LEFTX GetScreenWidth() / 2 + 20
#define TOPRIGHTY 40
#define RIGHTX GetScreenWidth() - 20
#define TOPLEFTY 40
#define BottomLeftY GetScreenHeight() - 20
#define BOTTOMRIGHTY GetScreenHeight() - 20
#define SCREEN_HEIGHT 600

// Standard Library Includes
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "raylib.h"
#include "logger.h"

// Data Structures
/**
 * Linked Node Structure
 * @brief Represents a node in a doubly linked list containing a 3x3 matrix, color, and pointers to the next and previous nodes
 */
typedef struct Linked_Node
{
    int dimension[3][3];
    Color color;
    struct Linked_Node *next;
    struct Linked_Node *prev;
} Linked_Node;

/**
 * Linked List Parent Structure
 * @brief Represents the parent structure of a doubly linked list containing a pointer to the head node
 */
typedef struct LinkedList
{
    Linked_Node *head;
} LinkedList_Parent;

typedef struct ScoreEntry
{
    char name[50];
    int score;
} ScoreEntry;

typedef struct ScoreList
{
    ScoreEntry *entries;
    size_t size;
    size_t capacity;
} ScoreList;

typedef struct blocktype
{
    int shape[3][3];
    int dimension[2];
    long long number;
} BLOCKTYPE;

typedef struct
{
    BLOCKTYPE *items;
    Color color[3];
    int size;
} FIFOStack;

static BLOCKTYPE BLOCKS[7] = {
    // I Block
    {
        .shape = {{0, 0, 0}, {1, 1, 1}, {0, 0, 0}},
        .dimension = {31, 3},
        .number = 54589},
    // J Block
    {
        .shape = {{1, 0, 0}, {1, 1, 1}, {0, 0, 0}},
        .dimension = {31, 3},
        .number = 54590},
    // L Block
    {
        .shape = {{0, 0, 1}, {1, 1, 1}, {0, 0, 0}},
        .dimension = {31, 3},
        .number = 54591},
    // O Block
    {
        .shape = {{1, 1, 0}, {1, 1, 0}, {0, 0, 0}},
        .dimension = {31, 3},
        .number = 54592},
    // S Block
    {
        .shape = {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}},
        .dimension = {31, 3},
        .number = 54593},
    // T Block
    {
        .shape = {{0, 1, 0}, {1, 1, 1}, {0, 0, 0}},
        .dimension = {31, 3},
        .number = 54594},
    // Z Block
    {
        .shape = {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}},
        .dimension = {31, 3},
        .number = 54595}};

// Predefined 3x3 Matrices for Tetris Blocks
static BLOCKTYPE BLOCKA = {
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 1},
};

static int BLOCKB[3][3] = {
    {0, 0, 0},
    {1, 1, 1},
    {0, 1, 0},
};

static int BLOCKC[3][3] = {
    {1, 1, 0},
    {0, 1, 1},
    {0, 0, 0},
};

static int BLOCKD[3][3] = {
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
};

static int BLOCKE[3][3] = {
    {0, 1, 1},
    {0, 1, 1},
    {0, 0, 0},
};
static int BLOCKF[3][3] = {
    {0, 1, 1},
    {0, 1, 1},
    {0, 1, 1},
};

static Color COLORS[] = {LIGHTGRAY, GRAY, DARKGRAY, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN, SKYBLUE, BLUE, DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, DARKBROWN};

// Function Declarations

/**
 * Rotate_Matrix
 * @brief Rotates a 3x3 matrix either clockwise or counter-clockwise
 * @param matrix The 3x3 matrix to rotate
 * @param direction The direction to rotate ("CW" for clockwise, "CCW" for counter-clockwise)
 * @return A pointer to the rotated matrix
 */
int **Rotate_Matrix(BLOCKTYPE *newBLock, char *direction);
/**
 * DrawMatrix
 * @brief Draws a 3x3 matrix on the screen at the specified position with the given block size and color
 * @param matrix The 3x3 matrix to draw
 * @param startX The starting X position on the screen
 * @param startY The starting Y position on the screen
 * @param blockSize The size of each block in the matrix
 * @param color The color to use for drawing the blocks
 * @return void
 */
void DrawMatrix(int matrix[3][3], int startX, int startY, int blockSize, Color color);
/**
 * create_linked_list
 * @brief Creates a new linked list with the given initial node
 * @param dimension The 3x3 matrix dimension for the initial node
 * @param direction The direction associated with the initial node
 * @param color The color associated with the initial node
 * @return A pointer to the created linked list parent structure
 */
LinkedList_Parent *create_linked_list(int dimension[3][3], char *direction, Color color);
/**
 * add_node
 * @brief Adds a new node to the end of the linked list
 * @param parent The linked list parent structure
 * @param dimension The 3x3 matrix dimension for the new node
 * @param direction The direction associated with the new node
 * @param color The color associated with the new node
 * @return A pointer to the newly added node
 */
Linked_Node *add_node(LinkedList_Parent *parent, int dimension[3][3], char *direction, Color color);
/**
 * get_last_node
 * @brief Retrieves the last node in the linked list
 * @param parent The linked list parent structure
 * @return A pointer to the last node in the linked list
 */
Linked_Node *get_last_node(LinkedList_Parent *parent);
/**
 * display_menu
 * @brief Displays the main menu of the Tetris game
 */
void display_menu();

/**
 * DrawButton
 * @brief Draws an interactive button with hover effects
 * @param x The center X position of the button
 * @param y The center Y position of the button
 * @param width The width of the button
 * @param height The height of the button
 * @param text The text to display on the button
 */
void DrawButton(int x, int y, int width, int height, const char *text);

/**
 * IsButtonClicked
 * @brief Checks if a button was clicked
 * @param x The center X position of the button
 * @param y The center Y position of the button
 * @param width The width of the button
 * @param height The height of the button
 * @return true if the button was clicked, false otherwise
 */
bool IsButtonClicked(int x, int y, int width, int height);
/**
 * play_game
 * @brief Handles the main gameplay logic and rendering
 */
void play_game();
/**
 * create_score_list
 * @brief Creates a new score list with an initial entry
 * @return A ScoreList structure containing the initial entry
 */
ScoreList *create_score_list();
/**
 * free_score_list
 * @brief Frees the memory allocated for the score list
 * @param list A pointer to the ScoreList structure to free
 */
void free_score_list(ScoreList *list);
/**
 * display_game_over
 * @brief Displays the game over screen
 */
void display_game_over();
/**
 * reset_game
 * @brief Resets the game state to initial values
 */
void reset_game();
/**
 * display_pause_menu
 * @brief Displays the pause menu screen
 */
void display_pause_menu();
/**
 * display_high_scores
 * @brief Displays the high scores screen
 */
void display_high_scores();
/**
 *
 */
bool up_check(BLOCKTYPE *block);
bool left_check(BLOCKTYPE *block);
bool down_check(BLOCKTYPE *block);
bool right_check(BLOCKTYPE *block);
bool rotation_check(BLOCKTYPE *block);

FIFOStack *init_and_fill_stack();

void print_2d_array(int **array, int rows, int cols);
void print_block(Linked_Node *node);
#endif // TETRIS_H
