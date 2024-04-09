/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glag <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:23:38 by glag              #+#    #+#             */
/*   Updated: 2024/04/03 19:25:26 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CHAR_H
# define FT_CHAR_H

# include <stdint.h>
# include <stdbool.h>

# define TOLOWER 223
# define TOUPPER 32

# define TOO_BIG -128

# define ASCII 1
# define PRINT 2
# define LOWER 4
# define UPPER 8
# define SPACE 16
# define DIGIT 32
# define XDIGIT 64
# define PUNCT 128

enum	e_chars
{
	C000 = ASCII,
	C001 = ASCII,
	C002 = ASCII,
	C003 = ASCII,
	C004 = ASCII,
	C005 = ASCII,
	C006 = ASCII,
	C007 = ASCII,
	C008 = ASCII,
	C009 = ASCII | SPACE,
	C010 = ASCII | SPACE,
	C011 = ASCII | SPACE,
	C012 = ASCII | SPACE,
	C013 = ASCII | SPACE,
	C014 = ASCII,
	C015 = ASCII,
	C016 = ASCII,
	C017 = ASCII,
	C018 = ASCII,
	C019 = ASCII,
	C020 = ASCII,
	C021 = ASCII,
	C022 = ASCII,
	C023 = ASCII,
	C024 = ASCII,
	C025 = ASCII,
	C026 = ASCII,
	C027 = ASCII,
	C028 = ASCII,
	C029 = ASCII,
	C030 = ASCII,
	C031 = ASCII,
	C032 = ASCII | PRINT | SPACE,
	C033 = ASCII | PRINT | PUNCT,
	C034 = ASCII | PRINT | PUNCT,
	C035 = ASCII | PRINT | PUNCT,
	C036 = ASCII | PRINT | PUNCT,
	C037 = ASCII | PRINT | PUNCT,
	C038 = ASCII | PRINT | PUNCT,
	C039 = ASCII | PRINT | PUNCT,
	C040 = ASCII | PRINT | PUNCT,
	C041 = ASCII | PRINT | PUNCT,
	C042 = ASCII | PRINT | PUNCT,
	C043 = ASCII | PRINT | PUNCT,
	C044 = ASCII | PRINT | PUNCT,
	C045 = ASCII | PRINT | PUNCT,
	C046 = ASCII | PRINT | PUNCT,
	C047 = ASCII | PRINT | PUNCT,
	C048 = ASCII | PRINT | DIGIT | XDIGIT,
	C049 = ASCII | PRINT | DIGIT | XDIGIT,
	C050 = ASCII | PRINT | DIGIT | XDIGIT,
	C051 = ASCII | PRINT | DIGIT | XDIGIT,
	C052 = ASCII | PRINT | DIGIT | XDIGIT,
	C053 = ASCII | PRINT | DIGIT | XDIGIT,
	C054 = ASCII | PRINT | DIGIT | XDIGIT,
	C055 = ASCII | PRINT | DIGIT | XDIGIT,
	C056 = ASCII | PRINT | DIGIT | XDIGIT,
	C057 = ASCII | PRINT | DIGIT | XDIGIT,
	C058 = ASCII | PRINT | PUNCT,
	C059 = ASCII | PRINT | PUNCT,
	C060 = ASCII | PRINT | PUNCT,
	C061 = ASCII | PRINT | PUNCT,
	C062 = ASCII | PRINT | PUNCT,
	C063 = ASCII | PRINT | PUNCT,
	C064 = ASCII | PRINT | PUNCT,
	C065 = ASCII | PRINT | UPPER | XDIGIT,
	C066 = ASCII | PRINT | UPPER | XDIGIT,
	C067 = ASCII | PRINT | UPPER | XDIGIT,
	C068 = ASCII | PRINT | UPPER | XDIGIT,
	C069 = ASCII | PRINT | UPPER | XDIGIT,
	C070 = ASCII | PRINT | UPPER | XDIGIT,
	C071 = ASCII | PRINT | UPPER,
	C072 = ASCII | PRINT | UPPER,
	C073 = ASCII | PRINT | UPPER,
	C074 = ASCII | PRINT | UPPER,
	C075 = ASCII | PRINT | UPPER,
	C076 = ASCII | PRINT | UPPER,
	C077 = ASCII | PRINT | UPPER,
	C078 = ASCII | PRINT | UPPER,
	C079 = ASCII | PRINT | UPPER,
	C080 = ASCII | PRINT | UPPER,
	C081 = ASCII | PRINT | UPPER,
	C082 = ASCII | PRINT | UPPER,
	C083 = ASCII | PRINT | UPPER,
	C084 = ASCII | PRINT | UPPER,
	C085 = ASCII | PRINT | UPPER,
	C086 = ASCII | PRINT | UPPER,
	C087 = ASCII | PRINT | UPPER,
	C088 = ASCII | PRINT | UPPER,
	C089 = ASCII | PRINT | UPPER,
	C090 = ASCII | PRINT | UPPER,
	C091 = ASCII | PRINT | PUNCT,
	C092 = ASCII | PRINT | PUNCT,
	C093 = ASCII | PRINT | PUNCT,
	C094 = ASCII | PRINT | PUNCT,
	C095 = ASCII | PRINT | PUNCT,
	C096 = ASCII | PRINT | PUNCT,
	C097 = ASCII | PRINT | LOWER | XDIGIT,
	C098 = ASCII | PRINT | LOWER | XDIGIT,
	C099 = ASCII | PRINT | LOWER | XDIGIT,
	C100 = ASCII | PRINT | LOWER | XDIGIT,
	C101 = ASCII | PRINT | LOWER | XDIGIT,
	C102 = ASCII | PRINT | LOWER | XDIGIT,
	C103 = ASCII | PRINT | LOWER,
	C104 = ASCII | PRINT | LOWER,
	C105 = ASCII | PRINT | LOWER,
	C106 = ASCII | PRINT | LOWER,
	C107 = ASCII | PRINT | LOWER,
	C108 = ASCII | PRINT | LOWER,
	C109 = ASCII | PRINT | LOWER,
	C110 = ASCII | PRINT | LOWER,
	C111 = ASCII | PRINT | LOWER,
	C112 = ASCII | PRINT | LOWER,
	C113 = ASCII | PRINT | LOWER,
	C114 = ASCII | PRINT | LOWER,
	C115 = ASCII | PRINT | LOWER,
	C116 = ASCII | PRINT | LOWER,
	C117 = ASCII | PRINT | LOWER,
	C118 = ASCII | PRINT | LOWER,
	C119 = ASCII | PRINT | LOWER,
	C120 = ASCII | PRINT | LOWER,
	C121 = ASCII | PRINT | LOWER,
	C122 = ASCII | PRINT | LOWER,
	C123 = ASCII | PRINT | PUNCT,
	C124 = ASCII | PRINT | PUNCT,
	C125 = ASCII | PRINT | PUNCT,
	C126 = ASCII | PRINT | PUNCT,
	C127 = ASCII
};

bool	ft_is(int bitmask, int c);

#endif
