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

/*
char	*ft_read_fd_extend(char *buff_static, char *buff, int r)
{
	char	*tmp;

	if (r == -1)
	{
    ft_free_strs(
		free(buff);
		free(buff_static);
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
	return (tmp);
}
*/

//char	*ft_read_fd(const int fd, char *buff_keep)

void	gnl_read_fd(const int fd, char **buff_keep)
{
	char	*buff;
	char	*tmp;
	int		r;

	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return ;
	r = 1;
	while (r != 0 && !ft_strchr(*buff_keep, '\n'))
	{
		r = read(fd, buff, BUFFER_SIZE);
		//buff_keep = ft_read_fd_extend(buff_keep, buff, r);
    if (r == -1)
    {
      ft_free_strs(&buff, buff_keep, 0);
      return ;
    }
    buff[r] = '\0';
    tmp = ft_strjoin(*buff_keep, buff);
    ft_free_strs(buff_keep, 0, 0);
    *buff_keep = tmp;
	}
  ft_free_strs(&buff, 0, 0);
}

char	*gnl_get_current_line(char *tmp_keep)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	len = 0;
	while (tmp_keep[len] != '\0')
	{
		if (tmp_keep[len] == '\n')
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
		line[i] = tmp_keep[i];
		i++;
	}
	return (line);
}

char	*gnl_backup(char *tmp_keep)
{
	int		i;
	char	*out;

	i = 0;
	while (tmp_keep[i])
	{
		if (tmp_keep[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	out = ft_strdup(tmp_keep + i);
	if (!out)
		return (NULL);
	return (out);
}

char  *gnl_parsing(char **buff_keep)
{
  char  *tmp_keep;
  char  *line;

  tmp_keep = ft_strdup(*buff_keep);
  ft_free_strs(buff_keep, 0, 0);
  line = gnl_get_current_line(tmp_keep);
  *buff_keep = gnl_backup(tmp_keep);
  ft_free_strs(&tmp_keep, 0, 0);
  return (line);
}

char	*get_next_line(int fd)
{
	static char	*backup[1024];
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
  //if (backup[fd] == NULL)
		//backup[fd] = ft_strdup("");
  line = NULL;

  gnl_read_fd(fd, &backup[fd]);

  // A enlever la ligne du dessous ?
	//if (backup[fd] == NULL)
		//return (NULL);

	if (!backup[fd] && *backup[fd] != '\0')
    line = gnl_parsing(&backup[fd]);
	//backup[fd] = ft_gnl_backup(backup[fd]);
  
  // A enlever la ligne du dessous ?
	//if (backup[fd] == NULL)
		//return (NULL);
	if (!line || line[0] == '\0')
	{
    ft_free_strs(&backup[fd], &line, 0);
		return (NULL);
	}
	return (line);
}
