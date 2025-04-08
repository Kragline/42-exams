#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE  42
#endif

char *ft_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

size_t ft_strlen(const char *str)
{
	size_t i = 0;

	// check later the null
	while (str[i])
		i++;
	return (i);
}

void ft_strcpy(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

char *ft_strjoin(char *s1, char *s2)
{
	size_t len1 = ft_strlen(s1);
	size_t len2 = ft_strlen(s2);
	char *joined = (char *)malloc(sizeof(char) * (len1 + len2 + 1));

	if (!s1 || !s2 || !joined)
		return (NULL);
	ft_strcpy(joined, s1);
	ft_strcpy((joined + len1), s2);
	free(s1);
	return (joined);
}

char *ft_strdup(char *str)
{
	char *dup = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	
	if (!dup)
		return (NULL);
	ft_strcpy(dup, str);
	return (dup);
}

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE + 1];
	char *line;
	char *newline;
	int c_read;
	int c_copied;

	line = ft_strdup(buf);
	while (!(newline = ft_strchr(line, '\n')) && (c_read = read(fd, buf, BUFFER_SIZE)))
	{
		buf[c_read] = '\0';
		line = ft_strjoin(line, buf);
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	if (newline)
	{
		c_copied = newline - line + 1;
		ft_strcpy(buf, newline + 1);
	}
	else
	{
		c_copied = ft_strlen(line);
		buf[0] = '\0';
	}
	line[c_copied] = '\0';
	return (line);
}

int main() {
    int fd;
    char *line;

    fd = open("get_next_line.c", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
    close(fd);
    return 0;
}