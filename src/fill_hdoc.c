/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:46:04 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/04 13:39:44 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inc_name(char *name)
{
	int		i;
	char	done;

	name++;
	i = 0;
	done = 1;
	while ((i == 0 || !done) && name[i])
	{
		if (name[i] == 'Z')
		{
			name[i] = '0';
			done = 0;
		}
		else
		{
			if (name[i] == 'z')
				name[i] = 'A';
			else if (name[i] == '9')
				name[i] = 'a';
			else
				name[i]++;
			done = 1;
		}
		i++;
	}
}

static int	open_file(char *name)
{
	int	fd;
	int	err;

	fd = -1;
	ft_memset(name, '0', 52);
	name[1] = 47;
	name[51] = 0;
	name[0] = '.';
	while (fd == -1)
	{
		inc_name(name);
		if (access(name, F_OK))
		{
			fd = open(name, O_CREAT | O_EXCL | O_WRONLY, 0644);
			if (fd == -1 && errno != EEXIST)
			{
				err = errno;
				ft_perror("minishell: heredoc: ");
				ft_perror(strerror(err));
				ft_perror("\n");
				return (-1);
			}
		}
	}
	return (fd);
}

//free name si err
static int	fill_file(char *name, t_str lim, t_list **hdocs, int *err) 
{
	int	fd;

	fd = open_file(name);
	if (fd == -1)
	{
		free(name);
		return (1);
	}
	//add to hdocs
	//input
}

//unlink where (il faut unlink les fichiers crees)
//faire une liste chainee
int	fill_heredocs(t_list *lst, t_list **hdocs, int *exc, int *err)
{
	t_str	name;

	while (lst)
	{
		if (((t_tok *)lst->content)->tok == HDOC)
		{
			name = (t_str){malloc(52), 51};
			if (name.s == NULL)
			{
				*err = ERR_AINTNOWAY;
				*exc = 2;
				return (93);
			}
			if (fill_file(name.s,
				((t_tok *)lst->content)->hdoc.lim, hdocs, err))
			{
				*exc = 2;
				return (12345);
			}
			free(((t_tok *)lst->content)->hdoc.lim.s);
			((t_tok *)lst->content)->hdoc.lim = name;
		}
		lst = lst->next;
	}
	return (0);
}
