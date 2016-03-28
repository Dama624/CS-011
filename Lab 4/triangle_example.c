#include <stdio.h>
#include "triangle_routines.h"

int main(void)
{
    int board[15];
    triangle_input(board);

    printf("Here is the board you entered:\n");
    triangle_print(board);

    return 0;
}
