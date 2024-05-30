/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:16:23 by ttrave            #+#    #+#             */
/*   Updated: 2024/05/28 18:18:30 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(int argc, char **argv, t_envp *envp_status, int *fds)
{
	char	*buffer;
	ssize_t	res;
	size_t	len;

	(void)argc;
	(void)argv;
	(void)envp_status;
	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
	{
		ft_perror("minishell: pwd: getcwd(): malloc(): \
		failed memory allocation\n");
		return (2);
	}
	len = ft_strlen(buffer);
	buffer[len] = '\n';
	res = write(fds[WRITE], buffer, len + 1);
	free(buffer);
	if (res == -1)
		return (1);
	return (0);
}
