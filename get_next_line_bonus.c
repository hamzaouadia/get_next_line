/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouadia <haouadia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:31:05 by haouadia          #+#    #+#             */
/*   Updated: 2022/11/08 07:56:06 by haouadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*rest_save(char *save)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	s = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!s)
		return (NULL);
	j = 0;
	while (save[++i])
		s[j++] = save[i];
	s[j] = '\0';
	free(save);
	return (s);
}

char	*save_line(char *save)
{
	int		i;
	char	*s;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	s = malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		s[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		s[i] = save[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*read_n_save(int fd, char *save)
{
	char	*readed;
	int		bytes;

	bytes = 1;
	readed = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!readed)
		return (NULL);
	while (!ft_strchr(save, '\n') && bytes != 0)
	{
		bytes = read(fd, readed, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(save);
			free(readed);
			return (NULL);
		}
		readed[bytes] = '\0';
		save = ft_strjoin(save, readed);
	}
	free(readed);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save[fd] = read_n_save(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = save_line(save[fd]);
	save[fd] = rest_save(save[fd]);
	return (line);
}
