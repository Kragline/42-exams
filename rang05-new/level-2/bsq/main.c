#include "bsq.h"

void	print_map(t_map *map)
{
	for (int i = 0; i < map->rows; i++)
		fprintf(stdout, "%s\n", map->grid[i]);
}

void    free_map(t_map *map)
{
	if (!map || !map->grid)
		return;
	for (int i = 0; i < map->rows; i++)
		free(map->grid[i]);
	free(map->grid);
}

int main(int argc, char **argv)
{
	t_map	map;

	map.rows = 0;
	map.cols = 0;
	map.grid = NULL;

	if (argc == 1)
	{
		if (!read_map_stdin(&map))
		{
			free_map(&map);
			fprintf(stdout, "Error: invalid map\n");
			return (1);
		}
		if (!solve_bsq(&map))
		{
			free_map(&map);
			fprintf(stdout, "Error: malloc error\n");
			return (1);
		}
		print_map(&map);
		free_map(&map);
		return (0);
	}

	if (argc != 2)
	{
		fprintf(stdout, "Error: wrong argument count\n");
		return (1);
	}
	
	if (!read_map(argv[1], &map))
	{
		free_map(&map);
		fprintf(stdout, "Error: invalid map\n");
		return (1);
	}
	if (!solve_bsq(&map))
	{
		free_map(&map);
		fprintf(stdout, "Error: malloc error\n");
		return (1);
	}
	print_map(&map);
	free_map(&map);
	return (0);
}
