/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiri <aguiri@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 22:19:04 by aguiri            #+#    #+#             */
/*   Updated: 2022/02/12 23:50:05 by aguiri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*gnl_read_fd_extend(char *buff_keep, char *buff, int r)
{
	char	*tmp;

	if (r == -1)
	{
		free(buff);
		free(buff_keep);
		return (NULL);
	}
	buff[r] = '\0';
	tmp = ft_strjoin(buff_keep, buff);
	if (!tmp)
	{
		free(tmp);
		free(buff_keep);
		free(buff);
		return (NULL);
	}
	free(buff_keep);
	return (tmp);
}

char	*gnl_read_fd(const int fd, char *buff_keep)
{
	char	*buff;
	int		r;

	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
	{
		free(buff);
		free(buff_keep);
		return (NULL);
	}
	r = 1;
	while (r != 0 && !ft_strchr(buff_keep, '\n'))
	{
		r = read(fd, buff, BUFFER_SIZE);
		buff_keep = gnl_read_fd_extend(buff_keep, buff, r);
		if (!buff_keep)
			return (NULL);
	}
	free(buff);
	return (buff_keep);
}

char	*gnl_get_current_line(char *buff_keep)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	len = 0;
	while (buff_keep[len] != '\0')
	{
		if (buff_keep[len] == '\n')
		{
			len++;
			break ;
		}
		len++;
	}
	line = (char *) malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	line[len] = '\0';
	while (i < len)
	{
		line[i] = buff_keep[i];
		i++;
	}
	return (line);
}

char	*gnl_backup(char *buff_keep)
{
	int		i;
	char	*tmp;

	i = 0;
	while (buff_keep[i])
	{
		if (buff_keep[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	tmp = ft_strdup(buff_keep + i);
	if (!tmp)
		return (NULL);
	free(buff_keep);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*backup[1024];
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (backup[fd] == NULL)
		backup[fd] = ft_strdup("");
	backup[fd] = gnl_read_fd(fd, backup[fd]);
	if (backup[fd] == NULL)
		return (NULL);
	line = gnl_get_current_line(backup[fd]);
	backup[fd] = gnl_backup(backup[fd]);
	if (backup[fd] == NULL)
		return (NULL);
	if (line[0] == '\0')
	{
		free(backup[fd]);
		free(line);
		return (NULL);
	}
	else
		return (line);
}
