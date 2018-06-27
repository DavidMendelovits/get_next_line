/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <dmendelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 21:21:48 by dmendelo          #+#    #+#             */
/*   Updated: 2018/06/26 19:40:22 by dmendelo         ###   ########.fr       */
/*   Updated: 2018/06/25 20:19:02 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./libft/libft.h"

int				copy_until(char **dest, char *source, char c)
{
	int		i;
	int		count;
	int		pos;
	char	*tmp;

	i = -1;
	count = 0;
	while (source[++i])
		if (source[i] == c)
			break ;
	pos = i;
//	*dest = ft_strsub(source, 0, i);
	while (source[count] && count < i)
	{
		tmp = ft_strjoinch(*dest, source[count]);
		free(*dest);
		*dest = tmp;
		if (!dest)
			return (0);
		count++;
	}
	return (pos);
}

static fd_list	*find_in_rolodex(fd_list **file, int fd)
{
	fd_list  *temp;

	temp = *file;
    while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	temp = (fd_list *)malloc(sizeof(fd_list));
	temp->content = ft_strnew(1);
	temp->fd = fd;
	ft_fd_lstadd(file, temp);
	temp = *file;
	return (temp);
}

char			*concatenate_str(const char *buf, char *content)
{
	char		*temp;
	char		*trash;

	trash = content;
	temp = ft_strjoin(content, buf);
	free(trash);
	return (temp);
}

char			*shift_overflow(char *content, int i)
{
	char	*temp;
	char	*trash;
	char	*empty;

	temp = ft_strnew(1);
	empty = temp;
	temp = ft_strjoin(empty, content);
	content -= (i + 1);
	trash = content;
	free(trash);
	free(empty);
	return (temp);
}

int				get_next_line(const int fd, char **line)
{
	int				i;
	static  fd_list	*file;
	fd_list			*current;
	char			buf[BUFF_SIZE + 1];
	int				ret;
	char 			*temp;
    
	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	current = find_in_rolodex(&file, fd);
	*line = ft_strnew(1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		temp = current->content;
		NULLCHECK((current->content = concatenate_str(buf, temp)));
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < BUFF_SIZE && !ft_strlen(current->content))
		return (0);
	i = copy_until(line, current->content, '\n');
	(i < (int)ft_strlen(current->content))
	? current->content = shift_overflow(&current->content[i + 1], i)  
	: ft_strclr(current->content);
	return (1);
}
