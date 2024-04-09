/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <glaguyon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:18:30 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/04 16:48:11 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEM_H
# define FT_MEM_H

# include <stdint.h>
# include <stddef.h>
# include <stdlib.h>

# define OPSIZE 8

void	ft_bzero(void *restrict s, size_t n);
void	*ft_memcpy(void *restrict dest, const void *restrict src, size_t n);

#endif
