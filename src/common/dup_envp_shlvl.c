/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_envp_shlvl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:45:53 by ttrave            #+#    #+#             */
/*   Updated: 2024/05/03 19:46:41 by ttrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*increment_shlvl(char *old_shlvl)
{
	int		n_lvl;
	char	*lvl;
	char	*new_shlvl;

	n_lvl = (int)ft_atoi(&old_shlvl[6]) + 1;
	lvl = ft_itoa(n_lvl);
	if (lvl == NULL)
		return (NULL);
	if (n_lvl >= 1000)
	{
		ft_perror("minishell: warning: shell level (");
		ft_perror(lvl);
		ft_perror(") too high, resetting to 1\n");
		new_shlvl = ft_strdup("SHLVL=1");
	}
	else
		new_shlvl = ft_strjoin("SHLVL=", lvl);
	free(lvl);
	return (new_shlvl);
}

int	check_numeric(char *str)
{
	size_t	i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_is(str[i], DIGIT) != 0)
	{
		nbr = 10 * nbr + str[i] - 48;
		if (nbr < 0)
			return (0);
		i++;
	}
	return (str[i] == '\0');
}
