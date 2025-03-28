/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:21:37 by jodiaz-a          #+#    #+#             */
/*   Updated: 2025/02/19 08:49:32 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

# include <ctype.h>
# include <string.h>
# include <stddef.h>

# include <stdarg.h>

# include "../garbage_collector/includes/garbage_collector.h"

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isgraph(int arg);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_atoi(const char *nptr);
long int	ft_atol(const char *nptr);
void		*ft_calloc(size_t nmeb, size_t size);
char		*ft_strdup(const char *s);

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/* Bonus */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ft_printf */
int			ft_printf(const char *format, ...);
int			ft_print_c(int c);
int			ft_print_d_and_i(int num);
int			ft_print_p(unsigned long long int num);
int			ft_print_s(const char *string);
int			ft_print_u(unsigned int num);
int			ft_print_xx(unsigned int num, const char f);

/* gnl*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000

char		*get_next_line_bonus(int fd);
int			ft_strlen1(char *s);
char		*ft_strjoin1(char *start_point, char *buffer_rd);
char		*ft_read_fd(int fd, char *start_point);
char		*ft_get_line(char *start_point);
char		*ft_new_start_point(char *start_point);
char		*ft_strchr1(char *start_point, int bn);

// char	*get_next_line(int fd);
// int		ft_strlen_gnl(char *s);
// char	*ft_strjoin_gnl(char *start_point_buff, char *buffer_readed);
// char	*ft_read_fd(int fd, char *start_point_buff);
// char	*ft_get_line(char *start_point_buff);
// char	*ft_find_new_start(char *start_point_buff);
// char	*ft_strchr_gnl(char *start_point_buff, int bn);

double		ft_abs(double n);

# endif
#endif
