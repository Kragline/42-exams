#include "bsq.h"

int	solve_bsq(t_map *map)
{
	int	**dp = calloc(map->rows, sizeof(int *));
	if (!dp)
		return (0);

	for (int i = 0; i < map->rows; i++)
		dp[i] = calloc(map->cols, sizeof(int));

	int	best = 0, best_i = 0, best_j = 0;

	for (int i = 0; i < map->rows; i++)
	{
		for (int j = 0; j < map->cols; j++)
		{
			if (map->grid[i][j] == map->empty)
			{
				if (i == 0 || j == 0)
					dp[i][j] = 1;
				else
				{
					int	up = dp[i-1][j];
					int	left = dp[i][j-1];
					int	diag = dp[i-1][j-1];
					int	min = up < left ? up : left;
					if (diag < min)
						min = diag;
					dp[i][j] = 1 + min;
				}

				if (dp[i][j] > best)
				{
					best = dp[i][j];
					best_i = i;
					best_j = j;
				}
			}
		}
	}

	/* Draw the square */
	for (int i = best_i - best + 1; i <= best_i; i++)
		for (int j = best_j - best + 1; j <= best_j; j++)
			map->grid[i][j] = map->full;

	for (int i = 0; i < map->rows; i++)
		free(dp[i]);
	free(dp);

	return (1);
}
