#include "tetris.h"

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