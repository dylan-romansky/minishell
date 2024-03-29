/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:29:25 by dromansk          #+#    #+#             */
/*   Updated: 2019/08/19 23:44:28 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*make_env(char *s1, char *s2)
{
	char	*s;
	char	*t;

	s = ft_strjoin(s1, "=");
	t = ft_strjoin(s, s2 ? s2 : "");
	free(s);
	return (t);
}

int		check_env(char *env, char *var)
{
	int		ret;
	char	**s;

	s = ft_strsplit(env, '=');
	ret = ft_strcmp(*s, var);
	free_split(s);
	return (ret);
}

char	**ft_setenv(char **args, char **env)
{
	int		i;

	i = 0;
	if (!args[1])
		return (ft_env(args, env));
	while (env[i] && check_env(env[i], args[1]))
		i++;
	if (env[i])
	{
		free(env[i]);
		env[i] = make_env(args[1], args[2]);
	}
	else
		env = array_join(env, make_env(args[1], args[2]));
	return (env);
}

char	**ft_unsetenv(char **args, char **env)
{
	int		i;
	int		len;
	char	**e;

	i = 0;
	len = 0;
	while (env[len])
		len++;
	while (args[1] && env[i] && check_env(env[i], args[1]))
		i++;
	if (args[1] && env[i])
	{
		e = (char **)malloc(sizeof(char *) * len);
		len = -1;
		while (++len < i)
			e[len] = env[len];
		free(env[i++]);
		while (env[i])
			e[len++] = env[i++];
		e[len] = NULL;
		free(env);
		env = e;
	}
	return (env);
}

char	**ft_env(char **args, char **env)
{
	int		i;

	i = 0;
	if (args && env)
		while (env[i])
			ft_printf("%s\n", env[i++]);
	return (env);
}
