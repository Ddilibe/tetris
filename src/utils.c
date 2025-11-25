#include "tetris.h"
#include "logger.h"

void print_2d_array(int **array, int rows, int cols)
{
    printf("2D ARRAY (%d x %d):\n", rows, cols);

    for (int i = 0; i < rows; i++)
    {
        printf("[ ");
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", (array + i) + j);
        }
        printf("]\n");
    }

    printf("\n");
}
/**
 *  def get_binary(j: int):
 *      w = 0
 *      for i in range(414):
 *          if i == j:
 *              w = pow(2, i)
 *              continue
 *          if i == 18:
 *              continue
 *          if i%18 == 0:
 *              w += pow(2, i)
 *      return w
 *
 *  def display_binary(i: int):
 *      binary = f"{bin(i)[2:]}"
 *      for i in range(23):
 *          print(binary[(18*i-18): (18*i)])
 *
 * */

void print_block(Linked_Node *node)
{
    printf("INFO: LinkedNode with Address %p\n", node);
    printf("\tDimension: x->%d, y->%d\n", node->dimension[0], node->dimension[1]);
    printf("\tColor: %d\n", node->color);
    LOG_INFO("Printing BLOCK");
}
