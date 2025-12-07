#include "bsq.h"

void map_error(void)
{
    fputs("map error\n", stderr);
}

void free_map(t_map *map)
{
    if (!map || !map->grid)
        return;
    for (int i = 0; i < map->rows; i++)
        free(map->grid[i]);
    free(map->grid);
}
