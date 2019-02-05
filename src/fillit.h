/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshpakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 13:02:47 by mshpakov          #+#    #+#             */
/*   Updated: 2018/12/26 18:26:08 by tbujalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFF_SIZE 21
# define FULL '#'
# define EMPTY '.'
# define ERR -1
# define OK 1
# define RET_IF(x, y) if (y) return(x);
# define BREAK_IF(x) if (x) break ;
# define CONT_IF(x) if (x) continue ;
# define IF_DO(x, y) if (x) (y);
# define WHILE_DO(x, y) while (x) (y);
# define TAB shape->tab
# define T shape->type
# define FILL shape->fill
# define LAST shape->last
# define H shape->height
# define W shape->width
# define PREV shape->prev
# define NEXT shape->next
# define SAME sq->same
# define SIDE sq->side
# define NB_SH sq->nb_shapes

typedef struct		s_shape
{
	int				type;
	char			fill;
	int				tab[6];
	int				last[2];
	int				height;
	int				width;
	struct s_shape	*prev;
	struct s_shape	*next;
}					t_shape;

typedef struct		s_sq
{
	int				side;
	int				count;
	int				nb_shapes;
	int				same;
	int				j;
	int				i;
}					t_sq;

typedef struct		s_read
{
	char			buf[BUFF_SIZE + 1];
	ssize_t			ret;
	int				fd;
	char			fill;
}					t_read;

t_shape				*get_shape(t_shape **start, char fill);
int					shape_tab(char **a, t_shape *shape, int j, int i);
void				free_map(char **str);
int					ft_sqrt(int nb);
void				clean_map(char **map, int side, char c);
void				clear_last(t_shape *start);
char				**make_map(t_sq *sq);
int					final(t_shape *start, char fill);
int					arrange(t_shape *shape, char **map, t_sq *sq);
void				ft_putendl(char const *s);
void				ft_bzero(void *s, size_t n);
char				**ft_strsplit(char const *str, char c);
size_t				ft_strlen(const char *s);

#endif
