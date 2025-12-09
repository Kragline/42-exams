#include "bsq.h"

void    map_error(void)
{
    fputs("map error\n", stderr);
}

void    free_map(t_map *map)
{
    if (!map || !map->grid)
        return;
    for (int i = 0; i < map->rows; i++)
        free(map->grid[i]);
    free(map->grid);
}

int is_all_space(char *line)
{
    for (int i = 0; line[i]; i++)
    {
        if (line[i] != ' ' && line[i] != '\t')
            return (0);
    }
    return (1);
}
