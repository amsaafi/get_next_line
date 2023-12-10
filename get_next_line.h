#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	*ft_calloc(size_t num, size_t size);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_line(char *stash);
char	*read_file(int fd, char *stash);
char	*ft_join_and_free(char *stash, char *buffer);
char	*ft_reset_stash(char *stash);
char	*ft_strdup(const char *s);

#endif
