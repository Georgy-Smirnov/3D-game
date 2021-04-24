/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_head.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:51:09 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/17 18:29:01 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_HEAD_H
# define PARS_HEAD_H

# include "libft.h"

typedef struct	s_sprite
{
	double sp_x;
	double sp_y;
}				t_sprite;

typedef struct	s_all_info
{
	int			ident_r;
	int			width;
	int			higth;
	int			ident_no;
	char		*path_no;
	int			ident_so;
	char		*path_so;
	int			ident_we;
	char		*path_we;
	int			ident_ea;
	char		*path_ea;
	int			ident_s;
	char		*path_s;
	int			ident_f;
	int			color_f_r;
	int			color_f_g;
	int			color_f_b;
	int			ident_c;
	int			color_c_r;
	int			color_c_g;
	int			color_c_b;
	char		player_see;
	double		player_x;
	double		player_y;
	int			num_spr;
	t_sprite	*spr;
	char		**finish_map;

}				t_all_info;

int				check_digit(char *str);
void			rebut_all_info(t_all_info *info);
void			free_list(t_list *head);
void			free_finish_map(char **map);
void			free_struct_info(t_all_info *info);
int				map_create(t_list *tmp, t_all_info *info);
int				write_fc_color(char ident, char *str, t_all_info *info);
int				check_string_before_map(char *str, t_all_info *info);
t_all_info		*make_info(t_list **head);
void			free_struct_info(t_all_info *info);
void			free_list(t_list *head);
t_list			*read_file(char *argv);
void			*error_step(char *message, t_list *head, t_all_info *info);
int				check_map_name(char *name);
int				start_raycasting(t_all_info *q, int i);
void			put_ij_info(int i, int j, int *q, t_all_info *info);
int				check_third_argv(char *str);
int				check_filling(char filling);

#endif
