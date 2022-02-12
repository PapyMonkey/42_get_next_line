/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiri <aguiri@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 22:19:04 by aguiri            #+#    #+#             */
/*   Updated: 2022/02/12 15:34:36 by aguiri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	ft_read_fd(int fd, char **buff_static)
{
	char	*buff;
	char	*tmp;
	int		r;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return ;
	r = 1;
	while (r != 0 && !ft_strchr(*buff_static, '\n'))
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
		{
			// Do something to free everything
			break ;
		}
		buff[BUFFER_SIZE] = '\0';
		tmp = ft_strjoin(*buff_static, buff);
		//tmp = ft_strdup(*buff_static);
		if (!tmp)
		{
			break ;
		}
		free(*buff_static);
		*buff_static = tmp;
		free(tmp);
	}
	free(buff);
}

char	*ft_get_current_line(char *buff_static)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	len = 0;
	while (buff_static[len])
	{
		len++;
		if (buff_static[len] == '\n')
			break ;
	}
	printf("len = %d\n", len);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
	{
		printf("TEST IF LINE\n");
		return (NULL);
	}
	line[len] = '\0';
	while (i < len)
	{
		line[i] = buff_static[i];
		i++;
	}
	return (line);
}

static char	*ft_gnl_backup(char *buff_static)
{
	int		i;
	char	*tmp;

	i = 0;
	while (buff_static[i])
	{
		i++;
		if (buff_static[i] == '\n')
			break ;
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
	ft_read_fd(fd, &backup);
	line = ft_get_current_line(backup);
	backup = ft_gnl_backup(backup);
	if (backup == NULL)
		return (NULL);
	/*
	printf("TEST\n");
	printf("backup address : %p\n", backup);
	printf("line address : %p\n", line);
	printf("line value : %s\n", line);
	*/
	if (line[0] == '\0')
	{
		free(backup);
		//free(line);
		return (NULL);
	}
	else
		return (line);
}
