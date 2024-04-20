/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:16:23 by ttrave            #+#    #+#             */
/*   Updated: 2024/04/20 19:16:32 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(int argc, char **argv, char **envp)
{
	char	*buffer;
	ssize_t	res;
	size_t	len;

	argc = 0;
	argv = NULL;
	envp = NULL;
	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
		return (2);
	len = ft_strlen(buffer);
	buffer[len] = '\n';
	res = write(1, buffer, len + 1);
	free(buffer);
	if (res < 0)
		return (2);
	return (0);
}
