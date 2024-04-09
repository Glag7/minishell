/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:14:44 by glaguyon          #+#    #+#             */
/*   Updated: 2024/04/05 17:56:05 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdlib.h>//rm in the future
# include <unistd.h>

//structs
typedef struct s_list
{
	union
	{
		void			*content;
		size_t			unum;
		ssize_t			num;
	};
	struct s_list	*next;
}	t_list;

typedef struct s_dlst
{
	union
	{
		void			*content;
		size_t			unum;
		ssize_t			num;
	};
	struct s_dlst	*next;
	struct s_dlst	*prev;
}	t_dlst;

typedef struct s_str
{
	char	*s;
	size_t	len;
}	t_str;

//arr
ssize_t	ft_chrarr_int(const int *restrict arr, int tofind, size_t len);
ssize_t	ft_chrarr_len(const void *restrict arr, const void *restrict tofind,
			size_t flen, size_t len);
ssize_t	ft_chrarr_long(const ssize_t *restrict arr, ssize_t tofind, size_t len);
ssize_t	ft_chrarr_ptr(const void *restrict arr, const void *restrict tofind,
			size_t len,
			char (*cmp)(const void *restrict, const void *restrict));
void	ft_delarr(void *restrict arr, void (del)(void *restrict));
void	ft_delnarr(void *restrict arr, void (del)(void *restrict), size_t n);
void	ft_freearr(void *restrict arr);
void	ft_freenarr(void *restrict arr, size_t n);
void	ft_sortint(int *restrict arr, size_t len, char rev);
void	ft_sortlen(void *restrict arr, size_t len, char rev, size_t memlen);
void	ft_sortlong(long *restrict arr, size_t len, char rev);
void	ft_sortptr(void *restrict arr, size_t len, char rev,
			char (*cmp)(void *restrict, void *restrict));
void	ft_swapint(int *a, int *b);
void	ft_swaplen(void *a, void *b, size_t len);
void	ft_swaplong(ssize_t *a, ssize_t *b);
void	ft_swapptr(void *a, void *b);

//char
# define ASCII 1
# define PRINT 2
# define LOWER 4
# define UPPER 8
# define SPACE 16
# define DIGIT 32
# define XDIGIT 64
# define PUNCT 128
# define ALPHA 12
# define ALNUM 44

bool	ft_is(int bitmask, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
//

//dlst
t_dlst	*ft_dlstnew(void *content);
t_dlst	*ft_dlstremove(t_dlst **lst, ssize_t n);
void	ft_dlstadd_back(t_dlst **dlst, t_dlst *new);
void	ft_dlstadd_front(t_dlst **dlst, t_dlst *new);
void	ft_dlstclear(t_dlst **dlst, void (*del)(void *));
void	ft_dlstswap(t_dlst **dlst);

//file
t_str	ft_gnl_tstr(int fd, size_t bsize);
char	*ft_gnl(int fd, size_t bsize);

//lst
t_list	*ft_lstat(t_list *lst, size_t n);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
t_str	ft_lsttstr_to_tstr(t_list **lst, size_t len, void (del)(void *),
			short (end)(t_str *));
size_t	ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstinsert(t_list **lst, t_list *node, size_t n);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstpop(t_list **lst, void (del)(void *), int n);
char	*ft_lsttstr_to_str(t_list **lst, size_t len, void (del)(void *),
			short (end)(t_str *));

//math
int64_t	ft_max(int64_t a, int64_t b);
int64_t	ft_min(int64_t a, int64_t b);
int64_t	ft_powi(int64_t x, unsigned int n);
int64_t	ft_sqrti(uint64_t n);
//

//mem
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

//print
# define NOLEN 0xFFFFFFFFFFFFFFFFULL
# define IDK 0xFFFFFFFFFFFFFFFFULL

void	ft_printmem_fd(void *addr, int fd, size_t size);
void	ft_putendl_fd(char *s, int fd, size_t len);
void	ft_putnbr_fd(int64_t n, int fd);
void	ft_putnbrbase_fd(int64_t n, int fd, char *base);
void	ft_putstr_fd(char *s, int fd, size_t len);
//

//str
ssize_t	ft_atoi(const char *nptr);
ssize_t	ft_atoibase(const char *nptr, const char *base);
ssize_t	ft_in(char c, const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	**ft_split(char const *s, char c);
char	**ft_split_set(char const *s, const char *c);
char	*ft_itoa(ssize_t n);
char	*ft_itoabase(ssize_t n, const char *base);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//tstr
t_list	*ft_tstr_to_lst(t_str tstr, char *charset);
short	ft_iseol(t_str *tstr);
t_str	ft_tstr_dupstr(char *s, size_t len);
t_str	ft_tstrnew(char *str, size_t len);
void	ft_tstrdel(void *tstr);
void	ft_tstrfree(void *tstr);

#endif
