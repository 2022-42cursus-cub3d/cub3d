/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 10:25:16 by hyojlee           #+#    #+#             */
/*   Updated: 2021/11/29 14:47:47 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	isin_newline(char *str)
{
	int	idx;

	idx = 0;
	if (!str)
		return (-1);
	while (str[idx])
		if (str[idx++] == '\n')
			return (idx - 1);
	return (-1);
}

static int	have_newline(char **tmp, char **line, int idx)
{
	char	*box;
	int		flag;

	flag = 0;
	(*tmp)[idx] = '\0';
	*line = ft_strdup_gnl(*tmp, &flag);
	if (flag)
		return (-1);
	box = ft_strdup_gnl(*tmp + idx + 1, &flag);
	if (flag)
		return (-1);
	free(*tmp);
	*tmp = ft_strdup_gnl(box, &flag);
	if (flag)
		return (-1);
	free(box);
	return (1);
}

static int	nbytes_zero(char **tmp, char **line)
{
	int	flag;
	int	idx;

	flag = 0;
	idx = isin_newline(*tmp);
	if (idx >= 0)
		return (have_newline(tmp, line, idx));
	if (!*tmp)
	{
		*tmp = (char *)malloc(sizeof(char) * 1);
		if (!*tmp)
			return (-1);
		*tmp[0] = '\0';
	}
	*line = ft_strdup_gnl(*tmp, &flag);
	if (flag)
		return (-1);
	free(*tmp);
	*tmp = 0;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*tmp[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	int			idx;
	ssize_t		nbytes;
	int			flag;

	flag = 0;
	if (!line || BUFFER_SIZE < 1)
		return (-1);
	nbytes = read(fd, buf, BUFFER_SIZE);
	while (nbytes > 0)
	{
		buf[nbytes] = '\0';
		tmp[fd] = ft_strjoin_gnl(tmp[fd], buf, &flag);
		if (flag)
			return (-1);
		idx = isin_newline(tmp[fd]);
		if (idx >= 0)
			return (have_newline(&tmp[fd], line, idx));
	}
	if (nbytes == 0)
		return (nbytes_zero(&tmp[fd], line));
	return (-1);
}
