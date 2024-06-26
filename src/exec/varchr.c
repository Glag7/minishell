/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:43:20 by glaguyon          #+#    #+#             */
/*   Updated: 2024/05/30 20:01:33 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_str	exitcode(char *numbers, int exc)
{
	t_str	s;

	exc = (unsigned char)exc;
	s.len = 1 + (exc > 9) + (exc > 99);
	if (s.len == 3)
		numbers += 190 + (exc - 100) * 3;
	else if (s.len == 2)
		numbers += 10 + (exc - 10) * 2;
	else if (s.len == 1)
		numbers += exc;
	s.s = numbers;
	return (s);
}

t_str	varchr(t_str s, char **envp, t_mini *mini)
{
	static char	*num = "0123456789101112131415161718192021222324252627282930313"
		"2333435363738394041424344454647484950515253545556575859606162636465666"
		"7686970717273747576777879808182838485868788899091929394959697989910010"
		"1102103104105106107108109110111112113114115116117118119120121122123124"
		"1251261271281291301311321331341351361371381391401411421431441451461471"
		"4814915015115215315415515615715815916016116216316416516616716816917017"
		"1172173174175176177178179180181182183184185186187188189190191192193194"
		"1951961971981992002012022032042052062072082092102112122132142152162172"
		"1821922022122222322422522622722822923023123223323423523623723823924024"
		"1242243244245246247248249250251252253254255";

	if (s.len == 1 && s.s[0] == '?')
		return (exitcode(num, mini->exc));
	if (!envp)
		return ((t_str){0, 0});
	while (*envp)
	{
		if (ft_strncmp(s.s, *envp, s.len) == 0
			&& (*envp)[s.len] == '=')
			return ((t_str){envp[0] + s.len + 1,
				ft_strlen(*envp) - s.len - 1});
		envp++;
	}
	return ((t_str){0, 0});
}
