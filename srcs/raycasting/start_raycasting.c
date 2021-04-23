/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:46:20 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/21 19:46:23 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rcast.h"

/*
** В зависимости от взгляда игрока в файле конфигурации
** устанавливает необходимые вектор направления и вектор плоскости камеры.
*/

void	put_dir_plane(t_data *data, char c)
{
	if (c == 'N')
	{
		data->player.dir_x = -1;
		data->player.plane_y = AS;
	}
	if (c == 'S')
	{
		data->player.dir_x = 1;
		data->player.plane_y = -AS;
	}
	if (c == 'W')
	{
		data->player.dir_y = -1;
		data->player.plane_x = -AS;
	}
	if (c == 'E')
	{
		data->player.dir_y = 1;
		data->player.plane_x = AS;
	}
}

/*
** Функция заполняет структуру для рейкастинга.
** Принимает 2 структуры. И переносит всю необходимую
** информацию из структуры парсинга.
*/

int		put_info_in_data(t_all_info *info, t_data *data)
{
	mlx_get_screen_size(&data->win.width, &data->win.hight);
	return_struct(data);
	if (data->win.width > info->width)
		data->win.width = info->width;
	if (data->win.hight > info->higth)
		data->win.hight = info->higth;
	data->player.pos_x = info->player_x;
	data->player.pos_y = info->player_y;
	put_dir_plane(data, info->player_see);
	data->we.path = info->path_we;
	data->so.path = info->path_so;
	data->ea.path = info->path_ea;
	data->no.path = info->path_no;
	data->s.path = info->path_s;
	data->count_sp = info->num_spr;
	data->spr = info->spr;
	data->win.color_c = create_rgb(info->color_c_r,
	info->color_c_g, info->color_c_b);
	data->win.color_f = create_rgb(info->color_f_r,
	info->color_f_g, info->color_f_b);
	if (open_texture(data, info) == 0)
		return (0);
	data->map = info->finish_map;
	return (1);
}

/*
** Функция удаляет созданные окна и изображения и выходит из программы.
*/

void	my_destroy(t_data *d)
{
	mlx_destroy_image(d->win.mlx, d->win.img);
	mlx_destroy_image(d->win.mlx, d->no.img);
	mlx_destroy_image(d->win.mlx, d->so.img);
	mlx_destroy_image(d->win.mlx, d->we.img);
	mlx_destroy_image(d->win.mlx, d->ea.img);
	mlx_destroy_image(d->win.mlx, d->s.img);
	mlx_destroy_window(d->win.mlx, d->win.win);
}

int		my_exit(t_data *d)
{
	my_destroy(d);
	exit(0);
}

/*
** Функция создает записывает в структуру необходимую информацию.
** Создает окно и задает события. При необходимости запускает функцию
** для создания скриншота.
*/

int		start_raycasting(t_all_info *info, int i)
{
	t_data d;

	d.win.mlx = mlx_init();
	if (put_info_in_data(info, &d) == 0)
		return (0);
	d.win.win = mlx_new_window(d.win.mlx, d.win.width, d.win.hight, "H");
	d.win.img = mlx_new_image(d.win.mlx, d.win.width, d.win.hight);
	d.win.addr = mlx_get_data_addr(d.win.img, &d.win.bits_per_pixel,
	&d.win.line_length, &d.win.endian);
	if (i == 1)
	{
		if (make_screenshot(&d, info) == NULL)
			return (0);
		return (1);
	}
	mlx_hook(d.win.win, 3, 1L << 1, key_hook, &d);
	mlx_hook(d.win.win, 2, 1L << 0, key_press, &d);
	mlx_hook(d.win.win, 17, 1, my_exit, &d);
	mlx_loop_hook(d.win.mlx, move, &d);
	mlx_loop(d.win.mlx);
	return (1);
}
