#include "bsq.h"
#include <string.h>
#include <sys/types.h>

/* -------------------- INTERNAL HELPERS -------------------- */

static int parse_first_line(FILE *f, t_map *map)
{
    map->rows = 0;
    map->cols = 0;
    map->grid = NULL;

    /* Read: number empty obstacle full */
    int count = fscanf(f, "%d %c %c %c",
                       &map->rows,
                       &map->empty,
                       &map->obstacle,
                       &map->full);

    /* Could not parse header */
    if (count != 4 || map->rows <= 0)
        return 0;

    /* Validate characters */
    if (map->empty == map->obstacle ||
        map->empty == map->full ||
        map->obstacle == map->full)
        return 0;

    return 1;
}

static int load_body(FILE *f, t_map *map)
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
        /* Skip the empty lines */
        if ((len == 1 && line[0] == '\n'))
            continue;

        /* Remove trailing newline (if any) */
        if (line[len - 1] == '\n')
            line[--len] = '\0';
        
        /* Skip leftover after the first */        
        if (row == 0 && is_all_space(line))
            continue;

        if (row >= map->rows)
        {
            free(line);
            return 0;
        }

        /* Determine column width from first row */
        if (map->cols == 0)
            map->cols = len;
        else if ((int)len != map->cols)
        {
            free(line);
            return 0;
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

int read_map(const char *filename, t_map *map)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        return 0;

    if (!parse_first_line(f, map))
    {
        fclose(f);
        return 0;
    }

    if (!load_body(f, map))
    {
        fclose(f);
        return 0;
    }

    fclose(f);
    return 1;
}

/* -------------------- READ FROM STDIN -------------------- */

int read_map_stdin(t_map *map)
{
    if (!parse_first_line(stdin, map))
        return 0;

    return load_body(stdin, map);
}
