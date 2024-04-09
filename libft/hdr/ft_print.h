/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:45:13 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/05 17:43:29 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H

# include <unistd.h>
# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>

# define NOLEN 0xFFFFFFFFFFFFFFFFULL
# define PRINT 2

size_t	ft_strlen(const char *s);
bool	ft_is(int bitmask, int c);

#endif
