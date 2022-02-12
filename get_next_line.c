/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiri <aguiri@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 22:19:04 by aguiri            #+#    #+#             */
/*   Updated: 2022/02/12 19:02:32 by aguiri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_read_fd(const int fd, char *buff_static)
{
	char	*buff;
	char	*tmp;
	int		r;

	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
	{
		free(buff);
		free(buff_static);
		return (NULL);
	}
	r = 1;
	while (r != 0 && !ft_strchr(buff_static, '\n'))
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
		{
			free(buff_static);
			free(buff);
			return (NULL);
		}
		buff[r] = '\0';
		tmp = ft_strjoin(buff_static, buff);
		if (!tmp)
		{
			free(tmp);
			free(buff_static);
			free(buff);
			return (NULL);
		}
		free(buff_static);
		buff_static = tmp;
	}
	free(buff);
	return (buff_static);
}

char	*ft_get_current_line(char *buff_static)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	len = 0;
	while (buff_static[len] != '\0')
	{
		if (buff_static[len] == '\n')
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
		line[i] = buff_static[i];
		i++;
	}
	return (line);
}

char	*ft_gnl_backup(char *buff_static)
{
	int		i;
	char	*tmp;

	i = 0;
	while (buff_static[i])
	{
		if (buff_static[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	tmp = ft_strdup(buff_static + i);
	if (!tmp)
		return (NULL);
	free(buff_static);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (backup == NULL)
		backup = ft_strdup("");
	backup = ft_read_fd(fd, backup);
	if (backup == NULL)
		return (NULL);
	line = ft_get_current_line(backup);
	/*
	//printf("backup address : %p\n", backup);
	printf("\nbackup value : %s\n", backup);
	//printf("line address : %p\n", line);
	printf("line value : %s\n", line);
	*/
	backup = ft_gnl_backup(backup);
	if (backup == NULL)
		return (NULL);
	if (line[0] == '\0')
	{
		free(backup);
		free(line);
		return (NULL);
	}
	else
		return (line);
}
