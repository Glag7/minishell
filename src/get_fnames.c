/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fnames.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:38:58 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/22 15:59:07 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_file(t_mini *mini, t_str **fnames,
	size_t *i, struct dirent *dir)
{
	(*fnames)[*i] = (t_str){ft_strdup(dir->d_name), ft_strlen(dir->d_name)};
	if ((*fnames)[*i].s == NULL)
	{
		free_fnames(*fnames);
		*fnames = NULL;
		mini->err = ERR_AINTNOWAY;
		mini->exc = 2;
		return (1);
	}
	(*i)++;
	(*fnames)[*i] = (t_str){NULL, 0};
	return (0);
}

static int	chk_len(t_mini *mini, t_str **fnames, size_t i, size_t *len)
{
	t_str	*tmp;

	if (i + 2 <= *len)
		return (0);
	if (!*len)
	{
		*fnames = NULL;
		(*len)++;
	}
	*len *= 2;
	tmp = malloc(*len * sizeof(*tmp));
	if (tmp == NULL)
	{
		free_fnames(*fnames);
		*fnames = NULL;
		mini->err = ERR_AINTNOWAY;
		mini->exc = 2;
		return (1);
	}
	ft_memcpy(tmp, *fnames, i * sizeof(t_str));
	free(*fnames);
	*fnames = tmp;
	return (0);
}

int	get_fnames(t_mini *mini, t_str **strs)
{
	DIR				*dir;
	struct dirent	*curr;
	size_t			len;
	size_t			i;

	dir = opendir(".");
	if (dir == NULL)
	{
		ft_perror3("minishell: opendir: ", strerror(errno), "\n");
		mini->err = ERR_SHUTUP;
		mini->exc = 2;
		return (1);
	}
	len = 0;
	i = 0;
	curr = readdir(dir);
	while (curr)
	{
		if (chk_len(mini, strs, i, &len) || add_file(mini, strs, &i, curr))
			return (1);
		curr = readdir(dir);
	}
	closedir(dir);
	return (0);
}
