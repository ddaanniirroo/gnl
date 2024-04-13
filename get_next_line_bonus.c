/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoronin <dvoronin@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:42:16 by dvoronin          #+#    #+#             */
/*   Updated: 2024/04/13 17:59:37 by dvoronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *buf, char *str)
{
	int		byte;

	byte = 1;
	while (ft_strchr(str, '\n') == 0 && byte != 0)
	{
		byte = read(fd, buf, BUFFER_SIZE);
		if (byte < 0)
		{
			free(buf);
			free(str);
			return (0);
		}
		buf[byte] = '\0';
		if (!str)
			str = ft_substr(buf, 0, byte);
		else
			str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*ft_remainder(char	*str)
{
	char	*rem;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	i++;
	rem = ft_substr(str, i, ft_strlen(str));
	free(str);
	return (rem);
}

char	*ft_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	i++;
	line = ft_substr(str, 0, i);
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buf;
	static char		*str[OPEN_MAX];

	if (BUFFER_SIZE < 1 || fd < 0 || fd > OPEN_MAX)
		return (0);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	str[fd] = ft_read(fd, buf, str[fd]);
	if (!str[fd] || str[fd][0] == '\0')
	{
		free(str[fd]);
		str[fd] = 0;
		return (NULL);
	}
	line = ft_line(str[fd]);
	str[fd] = ft_remainder(str[fd]);
	return (line);
}

// int main()
// {
// 	int i = 0;
// 	// int fd = open("2.txt", O_RDONLY);
// 	// int	fd2 = open("q.txt", O_RDONLY);
// 	while (i < 1)
// 	{
// 		printf("%s", get_next_line(-1));
// 		// printf("%s", get_next_line(fd2));
// 		i++;
// 	}
// 	// close(fd);
// 	return (0);
// }
