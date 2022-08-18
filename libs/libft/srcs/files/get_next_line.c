/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:32:40 by gudias            #+#    #+#             */
/*   Updated: 2022/01/14 20:11:36 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<stdio.h>

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*newstr;
	size_t	s1_len;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen (s1);
	newstr = malloc(sizeof (char) * (s1_len + ft_strlen(s2) + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[i - s1_len] != '\0')
	{
		newstr[i] = s2[i - s1_len];
		i++;
	}
	newstr[i] = '\0';
	free(s1);
	free(s2);
	return (newstr);
}

static char	*rd_file(int fd)
{
	int		rd;
	char	*buf;

	buf = malloc (sizeof (char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	rd = read(fd, buf, BUFFER_SIZE);
	if (rd <= 0)
	{
		free(buf);
		return (NULL);
	}
	buf[rd] = '\0';
	return (buf);
}

static char	*clean_save(char *save, char *newline)
{
	char	*newsave;
	size_t	len;

	if (*newline == '\0' || *(newline + 1) == '\0')
	{
		free(save);
		return (NULL);
	}
	len = ft_strlen(save) - (newline - save);
	newsave = ft_substr(save, newline - save + 1, len);
	free(save);
	return (newsave);
}

static char	*update_line(char *line, char *save, char *newline)
{
	if (!line)
		line = ft_substr(save, 0, newline - save + 1);
	else
		line = ft_strjoin_gnl(line, ft_substr(save, 0, newline - save + 1));
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*newline;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!save)
		save = rd_file(fd);
	newline = NULL;
	line = NULL;
	while (save)
	{
		newline = ft_strchr_nl(save);
		line = update_line(line, save, newline);
		if (*newline == '\n')
		{
			save = clean_save(save, newline);
			break ;
		}
		free(save);
		save = rd_file(fd);
	}
	return (line);
}
