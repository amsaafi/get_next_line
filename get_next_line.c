#include "get_next_line.h"

char	*ft_join_and_free(char *stash, char *buffer)
{
	char	*ptr;

	ptr = ft_strjoin(stash, buffer);
	free(stash);
	return (ptr);
}

char	*read_file(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		stash = ft_join_and_free(stash, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	if (bytes_read == 0 && (!stash || ft_strlen(stash) == 0))
	{
		free(stash);
		return (NULL);
	}
	if (bytes_read == -1)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

char	*get_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
	}
	return (line);
}

char	*ft_reset_stash(char *stash)
{
	char	*new_stash;

	int i, j;
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(stash + i + 1);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_calloc(1, sizeof(char));
	if (!ft_strchr(stash, '\n'))
		stash = read_file(fd, stash);
	if (!stash)
	{
		free(stash);
		return (NULL);
	}
	line = get_line(stash);
	stash = ft_reset_stash(stash);
	return (line);
}

int	main(void)
{
	char	*result;
	int		fd;

	fd = open("lines.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open the file.\n");
		return (1);
	}
	while ((result = get_next_line(fd)) != NULL)
	{
		printf("%s", result);
		free(result);
	}
	close(fd);
	return (0);
}
