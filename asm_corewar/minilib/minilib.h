/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihoienko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 14:41:36 by ihoienko          #+#    #+#             */
/*   Updated: 2017/10/27 14:41:37 by ihoienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIB_H
# define MINILIB_H
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# define ENDL '\n'
# define ENDO '\0'
# define BUFF_SIZE 50

typedef struct		s_gnl
{
	int				fd;
	struct s_gnl	*next;
	char			*content;
}					t_gnl;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

size_t				ft_strlen(const char *s);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					ft_strcmp(const char *s1, const char *s2);
int					get_next_line(const int fd, char **line);
void				ft_putchar(char c);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putstr(char const *s);
void				*ft_memalloc(size_t size);
void				ft_strdel(char **as);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_lstappend(t_list **alst, t_list *new);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_putstr_fd(char const *s, int fd);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strnew(size_t size);
int					ft_strequ(char const *s1, char const *s2);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strcpy(char *s1, const char *s2);
char				*ft_strdup(const char *s1);
char				*ft_strchr(const char *s, int c);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *s1, const char *s2);
t_list				*ft_lstnew(void const *content, size_t content_size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);

#endif
