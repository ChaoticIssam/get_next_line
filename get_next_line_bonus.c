#include "get_next_line_bonus.h"

char	*ft_read_str(int fd, char *str)
{
	char	*buff;
	int		bsread;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bsread = 1;
	while (!ft_strchr(str, '\n') && bsread != 0)
	{
		bsread = read(fd, buff, BUFFER_SIZE);
		if (bsread == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bsread] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*ft_get_line(char *str)
{
	int		i;
	char	*buff;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	buff = (char *)malloc(sizeof(char) * (i + 2));
	if (!buff)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		buff[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		buff[i] = str[i];
		i++;
	}
	buff[i] = '\0';
    return (buff);
}

char	*ft_new_str(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = ft_read_str(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = ft_get_line(str[fd]);
	str[fd] = ft_new_str(str[fd]);
	return (line);
}