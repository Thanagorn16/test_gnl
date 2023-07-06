#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*tmp;
	int		i;

	tmp = (char *)malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*str3;
	int		i;
	int		j;

	if (str2[0] == '\0')
		return (str1);
	str3 = (char *)malloc(sizeof(char) * ft_strlen(str1) + ft_strlen(str2) + 1);
	i = 0;
	while (str1[i])
	{
		str3[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
	{
		str3[i] = str2[j];
		i++;
		j++;
	}
	str3[i] = '\0';
	free(str1);
	return (str3);
}

int	find_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1) ;
		i++;
	}
	return (0);
}

void	read_all(char **line, int fd)
{
	char	*buff;
	int		rd;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	rd = 1;
	while (rd != 0)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		buff[rd] = '\0';
		if (!(*line))
			*line = ft_strdup(buff);
		else
			*line = ft_strjoin(*line, buff);
	}
	free(buff);
}

char	*get_next_line(int fd)
{
	static char	*line;
	int			len;
	int			i;
	static int	j;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line)
		read_all(&line, fd);
	len = find_n(&line[j]);
	if (!len)
		len = ft_strlen(&line[j]);
	new_line = (char *)malloc(sizeof(char) * len + 1);
	i = 0;
	while (i < len)
	{
		new_line[i] = line[j];
		i++;
		j++;
	}
	new_line[i] = '\0';
	if (i == 0)
	{
		free(new_line);
		// free(line);
		return (NULL);
	}
	return (new_line);
}

// int	main()
// {
// 	int	fd;
// 	char	*line;

// 	// fd = open("buffer.text", O_RDONLY);
// 	fd = open("em.text", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("%s", line); //1
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line); //2
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line); //3
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line); // 4
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line); //5
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s\n", line); //6
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line); //7
// 	free(line);
// 	// line = read_all(fd);
// 	return (0);
// }