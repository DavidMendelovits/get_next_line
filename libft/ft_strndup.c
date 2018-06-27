/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 10:23:29 by dmendelo          #+#    #+#             */
/*   Updated: 2018/06/26 10:27:12 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*new;

	new = (char*)malloc(n + 1);
	if (new)
	{
		ft_strncpy(new, (char*)s, n);
		new[n] = '\0';
	}
	return (new);
}
