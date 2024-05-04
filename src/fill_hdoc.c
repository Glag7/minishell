/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:46:04 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/04 20:45:42 by glaguyon         ###   ########.fr       */
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

static int	add_name(t_mini *mini, char *name)
{
	t_list	*tmp;

	tmp = ft_lstnew(name);
	if (name == NULL || tmp == NULL)
	{
		mini->err = ERR_AINTNOWAY;
		mini->exc = 2;
		unlink(name);
		free(name);
		free(tmp);
		ft_lstclear(&mini->hdocs, &wrap_unlink);
		return (1);
	}
	ft_lstadd_back(&mini->hdocs, tmp);
	return (0);
}

static int	get_fd(char *name)
{
	int	fd;

	fd = -1;
	ft_memset(name + 6, '0', 50);
	ft_memcpy(name, "/tmp/./", 7);
	name[56] = 0;
	while (fd == -1)
	{
		inc_name(name + 6);
		if (access(name, F_OK))
		{
			fd = open(name, O_CREAT | O_EXCL | O_WRONLY, 0644);
			if (fd == -1 && errno != EEXIST)
			{
				fd = errno;
				ft_perror("minishell: heredoc: ");
				ft_perror(strerror(fd));
				ft_perror("\n");
				free(name);
				return (-1);
			}
		}
	}
	return (fd);
}

static int	open_file(t_mini *mini, char *name)
{
	int	fd;

	if (name == NULL)
	{
		mini->err = ERR_AINTNOWAY;
		mini->exc = 2;
		ft_lstclear(&mini->hdocs, &wrap_unlink);
		return (-1);
	}
	fd = get_fd(name);
	if (fd != -1 && add_name(mini, name))
	{
		close(fd);
		fd = -1;
	}
	return (fd);
}

//XXX passer ne void
int	fill_heredocs(t_list *lst, t_mini *mini)
{
	t_str	name;

	while (lst)
	{
		if (((t_tok *)lst->content)->tok == HDOC)
		{
			name = (t_str){malloc(57), 56};
			if (fill_file(open_file(mini, name.s),
					((t_tok *)lst->content)->hdoc.lim, mini))
				return (12345);//XXX garder le return
			free(((t_tok *)lst->content)->hdoc.lim.s);
			((t_tok *)lst->content)->hdoc.lim = name;
		}
		lst = lst->next;
	}
	return (0);
}
