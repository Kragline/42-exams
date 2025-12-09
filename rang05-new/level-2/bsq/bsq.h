#ifndef BSQ_H
# define BSQ_H

# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_map {
    int rows;
    int cols;
    char empty;
    char obstacle;
    char full;
    char **grid;
} t_map;

/* Parsing */
int     read_map(const char *filename, t_map *map);
int     read_map_stdin(t_map *map);
void    free_map(t_map *map);

/* Solver */
int     solve_bsq(t_map *map);
void    print_map(t_map *map);

/* Utils */
void    map_error(void);
int     is_all_space(char *line);

#endif
