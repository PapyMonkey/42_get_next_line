/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiri <aguiri@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:45:20 by aguiri            #+#    #+#             */
/*   Updated: 2022/02/12 23:47:37 by aguiri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	int		i;
	char	*out;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	out = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (out == NULL)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		out[i] = (char) s1[i];
		i++;
	}
	i = 0;
	while (i < len_s2)
	{
		out[i + len_s1] = (char) s2[i];
		i++;
	}
	out[len_s1 + len_s2] = '\0';
	return (out);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (c == 0)
		return ((char *)s + ft_strlen(s));
	else
	{
		i = 0;
		while (s[i])
		{
			if (s[i] == (char)c)
				return ((char *)s + i);
			i++;
		}
		return (NULL);
	}
}

char	*ft_strdup(char *src)
{	
	int		i;
	int		len;
	char	*cpy;

	i = 0;
	len = ft_strlen(src);
	cpy = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		*(cpy + i) = *(src + i);
		i++;
	}
	cpy[len] = '\0';
	return (cpy);
}
