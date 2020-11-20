#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 1024

int     get_next_line(int fd, char **line);
int	ft_stdin_or_read_file(char **line, char **save, int fd);
int	ft_find_line(char **line, char **save, char *buf);
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s);
void	ft_strlcpy_ex(char *dst, char *src, size_t dstsize);
char	*ft_strjoin_ex(char *s1, char *s2, size_t len2);
size_t	ft_strchr_ex(char *s, char c);

#endif