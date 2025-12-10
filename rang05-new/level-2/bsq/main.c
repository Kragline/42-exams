#include "bsq.h"

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		t_map	map;
		if (read_map_stdin(&map) && solve_bsq(&map))
			print_map(&map);
		else
			map_error();
		free_map(&map);
		return (0);
	}

	for (int i = 1; i < argc; i++)
	{
		t_map	map;

		if (read_map(argv[i], &map) && solve_bsq(&map))
			print_map(&map);
		else
			map_error();

		free_map(&map);

		if (i < argc - 1)
			fputc('\n', stdout);
	}
	return (0);
}
