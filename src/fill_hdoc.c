/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:46:04 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/04 17:03:12 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inc_name(char *name)
{
	int		i;
	char	done;

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

	ft_memcpy(name, "/tmp/./", 6);
	ft_memset(name + 1, '0', 52);
	name[51] = 0;
	while (name[6] == '/' || fd == -1)
	{
		inc_name(name);
		if (access(name, F_OK))
		{
			fd = open(name, O_CREAT | O_EXCL | O_WRONLY, 0644);
			if (fd == -1 && errno != EEXIST)
			{
				fd = errno;
				ft_perror("minishell: heredoc: ");
				ft_perror(strerror(fd));
				ft_perror("\n");
				return (-1);
			}
		}
	}
	return (fd);
}

static int	fill_file(char *name, t_str lim, t_list **hdocs, int *err)
{
	int		fd;
	int		tmperr;
	pid_t	pid;

	fd = open_file(name);
	if (fd == -1)
	{
		free(name);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		tmperr = errno;
		free(name);
		close(fd);
		ft_perror("minishell: fork: ");
		ft_perror(strerror(tmperr));
		ft_perror("\n");
	}
	else if (pid == 0)//free :(
		exit(0);
	else
		waitpid(pid, 0, 0);//signaux
	close(fd);
	return (0);
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
			name = (t_str){malloc(57), 56};
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
			//add to hdocs
			free(((t_tok *)lst->content)->hdoc.lim.s);
			((t_tok *)lst->content)->hdoc.lim = name;
		}
		lst = lst->next;
	}
	return (0);
}
