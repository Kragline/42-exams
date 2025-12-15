#include "bsq.h"
#include <string.h>
#include <sys/types.h>

/* -------------------- INTERNAL HELPERS -------------------- */

static int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (sign * res);
}

static int	parse_first_line(FILE *f, t_map *map)
{
	char *line = NULL;
	size_t n = 0;

	ssize_t	len = getline(&line, &n, f);
	if (line[len - 1] == '\n')
		line[--len] = '\0';
	
	map->rows = ft_atoi(line);
	if (map->rows <= 0)
		return (free(line), 0);
	int	i = 0;
	while (line[i] && line[i] >= '0' && line[i] <= '9')
		i++;

	if (line[i] == '\0')
		return (free(line), 0);
	map->empty = line[i];
	
	if (line[i + 1] == '\0')
		return (free(line), 0);
	map->obstacle = line[++i];
	
	if (line[i + 1] == '\0')
		return (free(line), 0);
	map->full = line[++i];

	if (line[i + 1] != '\0')
		return (free(line), 0);

	if (map->empty == map->obstacle ||
		map->empty == map->full ||
		map->obstacle == map->full)
		return (free(line), 0);

	return (free(line), 1);
}

static int	load_body(FILE *f, t_map *map)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t len;
	int row = 0;

	map->grid = calloc(map->rows, sizeof(char *));
	if (!map->grid)
		return 0;

	while ((len = getline(&line, &n, f)) != -1)
	{
		/* Skip the empty lines (not sure about this one by the way) */
		if ((len == 1 && line[0] == '\n'))
			continue;

		/* Remove trailing newline (if any) */
		if (line[len - 1] == '\n')
			line[--len] = '\0';

		if (row >= map->rows)
		{
			free(line);
			return (0);
		}

		/* Determine column width from first row */
		if (map->cols == 0)
			map->cols = len;
		else if ((int)len != map->cols)
		{
			free(line);
			return (0);
		}

		/* Validate characters and move to grid */
		map->grid[row] = malloc(map->cols + 1);
		for (int i = 0; i < len; i++)
		{
			if (line[i] == map->empty || line[i] == map->obstacle)
			{
				map->grid[row][i] = line[i];
			}
			else
			{
				free(line);
				return (0);
			}
		}
		map->grid[row][map->cols] = '\0';
		row++;
	}

	free(line);
	return (row == map->rows);
}

/* -------------------- READ FROM FILE -------------------- */

int	read_map(const char *filename, t_map *map)
{
	FILE *f = fopen(filename, "r");
	if (!f)
		return (0);

	if (!parse_first_line(f, map) || !load_body(f, map))
	{
		fclose(f);
		return (0);
	}

	fclose(f);
	return (1);
}

/* -------------------- READ FROM STDIN -------------------- */

int	read_map_stdin(t_map *map)
{
	if (!parse_first_line(stdin, map))
		return (0);

	return (load_body(stdin, map));
}
