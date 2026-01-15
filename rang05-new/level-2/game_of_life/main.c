#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void print_board(char **new_board, int height, int width)
{
	for (int row = 0; row < height; row++)
    {
		for (int col = 0; col < width; col++)
            putchar(new_board[row][col]);
        putchar('\n');
    }
}

void free_board(char **board, int height)
{
    for (int row = 0; row < height; row++)
        free(board[row]);
    free(board);
}

char **start_board(char **new_board, int width, int height)
{
    char c;
    int index = 0;
    int array = 0;
    int drawing = 0;
    while (read(STDIN_FILENO, &c, 1) > 0)
    {
		if (c == 'x')
			drawing = !drawing;
		else if (c == 'w' && array > 0)
			array--;
		else if (c == 'a' && index > 0)
			index--;
		else if (c == 's' && (array + 1 < height))
			array++;
		else if (c == 'd' && (index + 1 < width))
			index++;
		if (drawing)
			new_board[array][index] = 'O';
    }
	return (new_board);
}

char **board_creation(int width, int height)
{
	char **new_board = calloc(height, sizeof(char *));
	for (int row = 0; row < height; row++)
	{
		new_board[row] = calloc(width, sizeof(char));	
		for (int col = 0; col < width; col++)
			new_board[row][col] = ' ';
	}
	return (new_board);
}

int count_neighbors(char **board, int row, int col, int width, int height)
{
	int count = 0;
	for (int dr = -1; dr <= 1; dr++)
	{
		for (int dc = -1; dc <= 1; dc++)
		{
			if (dr == 0 && dc == 0)
				continue;
			int nr = row + dr;
			int nc = col + dc;
			if (nr >= 0 && nr < height && nc >= 0 && nc < width)
				if (board[nr][nc] == 'O')
					count++;
		}
	}
	return (count);
}

char **next_gen(char **board, int width, int height)
{
	char **new_board = board_creation(width, height);
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int neighbors = count_neighbors(board, row, col, width, height);
			if (board[row][col] == 'O')
			{
				if (neighbors == 2 || neighbors == 3)
					new_board[row][col] = 'O';
			}
			else
				if (neighbors == 3)
					new_board[row][col] = 'O';
		}
	}
	free_board(board, height);
	return (new_board);
}

int main (int argc, char **argv)
{
	if (argc == 4)
	{
		int width = atoi(argv[1]);
		int height = atoi(argv[2]);
		int max_iterations = atoi(argv[3]);
		char **empty_board = board_creation(width, height);
		char **board = start_board(empty_board, width, height);
		while (max_iterations--)
			board = next_gen(board, width, height);
		print_board(board, height, width);
		free_board(board, height);
	}
	return (0);
}