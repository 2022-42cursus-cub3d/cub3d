/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 12:38:35 by hyojlee           #+#    #+#             */
/*   Updated: 2021/11/29 14:50:03 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static void	ft_strlcat(char *ret, char *s1, char *s2)
{
	size_t	dst_size;
	size_t	idx;
	size_t	idx2;

	idx = 0;
	idx2 = 0;
	dst_size = ft_strlen(ret);
	while (s1[idx] != '\0')
	{
		ret[idx + dst_size] = s1[idx];
		idx++;
	}
	ret[idx + dst_size] = '\0';
	free(s1);
	dst_size += idx;
	while (s2[idx2] != '\0')
	{
		ret[idx2 + dst_size] = s2[idx2];
		idx2++;
	}
	ret[idx2 + dst_size] = '\0';
}

char	*ft_strjoin_gnl(char *s1, char *s2, int *flag)
{
	char	*ret;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		ret = ft_strdup_gnl(s2, flag);
	else if (!s2)
		ret = s1;
	else
	{
		ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (!ret)
		{
			*flag = 1;
			free(s1);
			return (0);
		}
		ret[0] = '\0';
		ft_strlcat(ret, s1, s2);
	}
	return (ret);
}

char	*ft_strdup_gnl(char *s1, int *flag)
{
	char	*ret;
	int		i;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!ret)
	{
		*flag = 1;
		free(s1);
		return (0);
	}
	i = -1;
	while (s1[++i] != '\0')
		ret[i] = s1[i];
	ret[i] = '\0';
	return (ret);
}
