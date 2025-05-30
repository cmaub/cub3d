/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:19:38 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/18 13:35:29 by anvander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_line
{
	char	*read_buf;
	char	*line;
}	t_line;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// get_next_line
char		*get_next_line(int fd);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s);
size_t		ft_strlen(const char *str);
char		*ft_strchr(const char *s, int c);

// is c
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);

// mem
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t length);
void		*ft_memmove(void *dest, const void *src, size_t len);
void		*ft_memset(void *s, int c, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
void		ft_bzero(void *s, size_t len);

// str
int			ft_is_only_spaces(char *str);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
int			ft_strchr_occur(const char *s, int c);
char		*ft_strdup(const char *s);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dst_size);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t dst_size);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strnchr(const char *s, int c, int len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);

// put
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
int			ft_putstr_fd(char *s, int fd);

// conversion type
int			ft_atoi(const char *nptr);
long		ft_atol(const char *str);
char		*ft_itoa(int n);
void		*ft_calloc(size_t nmemb, size_t size);
long long	ft_strtoll(const char *str);
void		*try_malloc(size_t size);

// t_list
void		ft_lstadd_back(t_list **list, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);

#endif //LIBFT_H
