#include <stdio.h>
#include <stdlib.h>

/* global size so we don't have a lot of copies from recursion. */
int size;

/* Queen linked list. We don't need to store row since that is
 * handled by the recursion and iterators. 
 */
typedef struct Queen
{
	int col;
	unsigned int diff;
	unsigned int sum;
	struct Queen *next;
	struct Queen *first;
} Queen;

/**
 * nqueen - computes 8 queen style solutions for n square size boards
 *
 * row - row of queen we're computing
 * col - column of queen we're computing
 * size - board size
 * prev - pointer to previous queen
 *
 * return void
 */
void nqueen(int row, int col, int size, Queen *prev)
{
	Queen *current = prev->next;
	Queen *qptr = prev->first;

	current->col = col;
	current->diff = row - col;
	current->sum = row + col;

	/* Check if we have a valid placement. If not, return and
	 * try next col. There is nothing else to do here. */
	while(qptr != current)
	{
		if(current->col == qptr->col
		   || current->diff == qptr->diff
		   || current->sum == qptr->sum)
			return;
		qptr = qptr->next;
	}
	/* We can save a bit of memory by reusing col for an iterator
	 * here for the next queen since we only needed it to set the
	 * current queen's position. */
	for(col = 1; col <= size; col++)
	{
		/* If we're the last queen, print solution and return.
		 * We don't need to check the rest of the cols as
		 * they're taken by prior queens. */
		if (current->next == NULL)
		{
			qptr = current->first;
			row = 1;
			while(qptr != NULL)
			{
				printf("Q%d:%d,%d ", row, row, qptr->col);
				qptr = qptr->next;
				row++;
			}
			printf("\n");
			return;
		}
		else
			nqueen(row + 1, col, size, current);
		/* If we're not the last queen, call nqueen for
		 * next queen.
		 */
	}
}
/**
 * main - compute all solutions to 8 queen style problems with
 * arbitrary size boards
 *
 * arugments: single integer for square board size
 *
 * return: 0 on success
 */
int main(int argc, char **argv)
{
	int i, j;
	Queen *first = malloc(sizeof(Queen));
	Queen *qptr;

	size = atoi(argv[1]);

	qptr = first;

	/* Allocate queens now so it's not checked
	 * continually in placement for speed. If we wind up
	 * a lot of queens this could take some time.
	 * It will also crash faster if out of memory.	
	 */
	for (i = 1; i < size; i++)
	{
		qptr->next = malloc(sizeof(Queen));
		qptr->first = first;
		qptr = qptr->next;
	}
	qptr->first = first;

	for (i = 1; i <= size; i++)
	{
		first->col = i;
		first->sum = 1 + i;
		first->diff = 1 - i;

		for (j = 1; j <= size; j++)
		{
			nqueen(2, j, size, first);
		}
	}
	return 0;
}
