/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rcast.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:31:06 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/21 20:31:11 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RCAST_H
# define RCAST_H

# include "mlx.h"
# include "pars_head.h"
# include <math.h>

/*
** Дефолтные настройки игры.
** Кейкоды для клавиатуры (под MacOS).
** Скорость передвижения, скорость поворота и ширина обзора. 
*/

# define KC_ESC 53
# define KC_W 13
# define KC_A 0
# define KC_D 2
# define KC_S 1
# define KC_LEFT 123
# define KC_RIGHT 124

# define MS 0.08
# define TS 0.05
# define AS 0.66

typedef struct	s_window
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			hight;
	int			color_c;
	int			color_f;
}				t_window;

typedef struct	s_player{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct	s_move_flags{
	int			press_w;
	int			press_a;
	int			press_s;
	int			press_d;
	int			press_left;
	int			press_right;
}				t_mv_flags;

typedef struct	s_ray
{
	double		ray_dir_x;
	double		ray_dir_y;
	double		s_dist_x;
	double		s_dist_y;
	double		d_dist_x;
	double		d_dist_y;
	double		p_wall_d;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			hit;
	int			side;
	int			dstart;
	int			dend;
	double		wallx;
	int			tex_x;
	int			tex_y;
	int			line_h;
	char		*dst;
	char		*src;
}				t_ray;

typedef struct	s_spr
{
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			sprite_width;
	int			drawstart_y;
	int			drawend_y;
	int			drawstart_x;
	int			drawend_x;
}				t_spr;

typedef struct	s_text
{
	void		*img;
	char		*addr;
	int			text_w;
	int			text_h;
	char		*path;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_text;

typedef struct	s_data
{
	t_window	win;
	t_player	player;
	t_mv_flags	move_f;
	t_ray		ray;
	t_text		no;
	t_text		so;
	t_text		we;
	t_text		ea;
	t_text		s;
	int			count_sp;
	t_sprite	*spr;
	t_spr		sp;
	char		**map;
}				t_data;

int				start_raycasting(t_all_info *info, int i);
int				move(t_data *img);
void			put_d(t_data *img);
int				key_hook(int keycode, t_data *img);
int				key_press(int keycode, t_data *img);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				open_texture(t_data *d, t_all_info *info);
void			put_sprites(t_data *d, double *zbufer);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			put_in_img(t_data *d, t_text *t, int x, int y);
void			my_clear_window(t_data *img);
void			move_w_s(t_data *img, double ms);
void			move_a_d(t_data *img, double ms);
void			turn_l_r(t_data *img, double ts);
void			first_step_raycast(t_data *d, int x);
void			second_step_raycast(t_data *d);
void			third_step_raycast(t_data *d);
void			fourth_step_raycast(t_data *d);
void			fifth_step_raycast(t_data *d, int x);
void			*make_screenshot(t_data *d, t_all_info *info);
void			return_struct(t_data *data);
int				create_rgb(int r, int g, int b);
void			my_destroy(t_data *d);
int				my_exit(t_data *d);

#endif
