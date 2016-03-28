#include <stdlib.h>
#include <stdio.h>
#include "triangle_routines.h"
#define NMOVES 36 /* Maximum possible moves */
#define DIMENSION 15 /* Total number of pegs */

/* List of all possible moves in the Triangle Game */
int moves[NMOVES][3] =
{
    {0, 1, 3},
    {0, 2, 5},
    {1, 3, 6},
    {1, 4, 8},
    {2, 4, 7},
    {2, 5, 9},
    {3, 1, 0},
    {3, 6, 10},
    {3, 7, 12},
    {3, 4, 5},
    {4, 7, 11},
    {4, 8, 13},
    {5, 2, 0},
    {5, 4, 3},
    {5, 8, 12},
    {5, 9, 14},
    {6, 3, 1},
    {6, 7, 8},
    {7, 8, 9},
    {7, 4, 2},
    {8, 4, 1},
    {8, 7, 6},
    {9, 5, 2},
    {9, 8, 7},
    {10, 6, 3},
    {10, 11, 12},
    {11, 12, 13},
    {11, 7, 4},
    {12, 7, 3},
    {12, 11, 10},
    {12, 13, 14},
    {12, 8, 5},
    {13, 8, 4},
    {13, 12, 11},
    {14, 9, 5},
    {14, 13, 12}
};

/* Return the number of pegs on the board. */
int npegs(int board[])
{
    int i;
    int total = 0; /* The current total number of pegs  counted */
    for (i = 0; i < DIMENSION; i++)
    {
        total += board[i];
    }
    return total;
}

/* Return 1 if the move is valid on this board, otherwise return 0. */
int valid_move(int board[], int move[])
{
    if (board[move[0]] == 1 && board[move[1]] == 1 && board[move[2]] == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* Make this move on this board. */
void make_move(int board[], int move[])
{
    board[move[0]] = 0;
    board[move[1]] = 0;
    board[move[2]] = 1;
}

/* Unmake this move on this board. */
void unmake_move(int board[], int move[])
{
    board[move[0]] = 1;
    board[move[1]] = 1;
    board[move[2]] = 0;
}

/* 
 * Solve the game starting from this board.  Return 1 if the game can
 * be solved; otherwise return 0.  Do not permanently alter the board passed
 * in. Once a solution is found, print the boards making up the solution in
 * reverse order. 
 */
int solve(int board[])
{
    int i;
    int s; /* Solved Board */
    static int solved = 0; /* Boolean for whether a solution was found */
    if (npegs(board) == 1) /* Base case: 1 peg remains */
    {
        triangle_print(board);
        solved = 1;
    }
    else /* Recursive step */
    {
        for (i = 0; i < NMOVES; i++) /* For every move possible */
        {
            /* For debugging: printf("Move number %d\n",i); */
            if (valid_move(board, moves[i]) == 1) /* Check if move is
                                                   * allowed */
            {
                make_move(board, moves[i]); /* Apply move */
                /* For debugging: printf("Applied move %d\n",i); */
                s = solve(board); /* Check if modified board satisfies
                                   * base case */
                unmake_move(board, moves[i]);
                if (s == 1)
                {
                    triangle_print(board);
                    return solved;
                }
            }
        }
    }
    /* For debugging: printf("Solved? %d\n", solved); */
    return solved;
}

int main(void)
{
    int board[DIMENSION]; /* Initializing the board */
    triangle_input(board);
    /* For debugging: printf("Solved? %d\n", solve(board)); */
    return solve(board);
}
