/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_ctl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:12:46 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/05 16:16:38 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_ctl(bool show)
{
	struct termios	termios_data;

	tcgetattr(0, &termios_data);
	if (show)
		termios_data.c_lflag |= ECHOCTL;
	else
		termios_data.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_data);
}
