/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:10:32 by ttrave            #+#    #+#             */
/*   Updated: 2024/05/31 22:05:44 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sig;

static bool	get_option_nl(char **argv, size_t *i_ptr)
{
	bool	nl;
	char	*option;
	size_t	i;
	size_t	i_option;

	i = 1;
	nl = 1;
	option = argv[1];
	while (option != NULL && option[0] == '-' && option[1] == 'n')
	{
		i_option = 2;
		while (option[i_option] == 'n')
			i_option++;
		if (option[i_option] != '\0')
			break ;
		nl = 0;
		i++;
		option = argv[i];
	}
	*i_ptr = i;
	return (nl);
}

static char	*join_arg(char *toprint, char **argv, size_t i)
{
	char	*tmp;

	if (i)
		tmp = ft_strjoin(toprint, argv[i]);
	else
		tmp = ft_strdup(argv[i]);
	free(toprint);
	if (tmp == NULL)
	{
		ft_perror3("minishell: echo:", strerror(errno), "\n");
		return (NULL);
	}
	toprint = tmp;
	if (argv[i + 1])
	{
		tmp = ft_strjoin(toprint, " ");
		free(toprint);
	}
	if (tmp == NULL)
	{
		ft_perror3("minishell: echo:", strerror(errno), "\n");
		return (NULL);
	}
	return (tmp);
}

static int	print_arg(char *toprint, int nl, int fd)
{
	size_t	len;

	len = ft_strlen(toprint);
	if (nl == 1)
		toprint[len++] = '\n';
	if (write(fd, toprint, len) == -1)
	{
		free(toprint);
		ft_perror3("minishell: echo:", strerror(errno), "\n");
		return (1);
	}
	free(toprint);
	return (0);
}

static int	join_loop(char **argv, bool nl, int fd)
{
	char	*toprint;
	size_t	i;

	i = 0;
	toprint = NULL;
	while (argv[i])
	{
		toprint = join_arg(toprint, argv, i);
		if (toprint == NULL)
			return (2);
		i++;
	}
	if (g_sig == 2)
	{
		free(toprint);
		if (write(fd, "\n", 1) == -1)
		{
			ft_perror3("minishell: echo:", strerror(errno), "\n");
			return (1);
		}
		return (130);
	}
	return (print_arg(toprint, nl, fd));
}

int	builtin_echo(size_t argc, char **argv, t_envp *envp_status, int *fds)
{
	size_t	i;
	int		nl;

	(void)argc;
	(void)envp_status;
	nl = get_option_nl(argv, &i);
	return (join_loop(argv + i, nl, fds[WRITE]));
}
