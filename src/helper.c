/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 22:55:16 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/04 23:06:39 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int		wordlen(char const *str, char *d)
{
	int		i;
	int		j;

	i = 0;
	if (str[i] == '"')
	{
		i++;
		while (str[i] && str[i] != '"')
			i++;
		return (i);
	}
	while (str[i])
	{
		j = 0;
		while (d[j] != str[i])
			j++;
		if (d[j])
			return (i);
		i++;
	}
	return (i);
}

char			**cmd_split(char const *s, char *c)
{
	char	**n;
	int		len;
	int		i;

	if (s == NULL || !(n = (char **)malloc(sizeof(char *))))
		return (NULL);
	*n = NULL;
	while (*s)
	{
		i = 0;
		while (c[i] && c[i] != *s)
			i++;
		if (!c[i])
		{
			len = wordlen(s, c);
			n = array_join(n, ft_strndup(s, (size_t)len));
			s += len;
		}
		else
			s++;
	}
	return (n);
}