/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_for_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 18:32:09 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/21 18:32:13 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rcast.h"

/*
** Функции вычисления информации для отрисовки изображения.
*/

void	first_step_raycast(t_data *d, int x)
{
	double camera;

	camera = 2 * x / (double)d->win.width - 1;
	d->ray.ray_dir_x = d->player.dir_x + d->player.plane_x * camera;
	d->ray.ray_dir_y = d->player.dir_y + d->player.plane_y * camera;
	d->ray.map_x = (int)d->player.pos_x;
	d->ray.map_y = (int)d->player.pos_y;
	d->ray.d_dist_x = fabs(1 / d->ray.ray_dir_x);
	d->ray.d_dist_y = fabs(1 / d->ray.ray_dir_y);
	d->ray.hit = 0;
}

void	second_step_raycast(t_data *d)
{
	if (d->ray.ray_dir_x < 0)
	{
		d->ray.step_x = -1;
		d->ray.s_dist_x = (d->player.pos_x - d->ray.map_x) * d->ray.d_dist_x;
	}
	else
	{
		d->ray.step_x = 1;
		d->ray.s_dist_x = (d->ray.map_x + 1.0 - d->player.pos_x) *
		d->ray.d_dist_x;
	}
	if (d->ray.ray_dir_y < 0)
	{
		d->ray.step_y = -1;
		d->ray.s_dist_y = (d->player.pos_y - d->ray.map_y) * d->ray.d_dist_y;
	}
	else
	{
		d->ray.step_y = 1;
		d->ray.s_dist_y = (d->ray.map_y + 1.0 - d->player.pos_y) *
		d->ray.d_dist_y;
	}
}

void	third_step_raycast(t_data *d)
{
	while (d->ray.hit == 0)
	{
		if (d->ray.s_dist_x < d->ray.s_dist_y)
		{
			d->ray.s_dist_x += d->ray.d_dist_x;
			d->ray.map_x += d->ray.step_x;
			d->ray.side = 0;
		}
		else
		{
			d->ray.s_dist_y += d->ray.d_dist_y;
			d->ray.map_y += d->ray.step_y;
			d->ray.side = 1;
		}
		if (d->map[d->ray.map_x][d->ray.map_y] == '1')
			d->ray.hit = 1;
	}
	if (d->ray.side == 0)
		d->ray.p_wall_d = (d->ray.map_x - d->player.pos_x +
		(1 - d->ray.step_x) / 2) / d->ray.ray_dir_x;
	else
		d->ray.p_wall_d = (d->ray.map_y - d->player.pos_y +
		(1 - d->ray.step_y) / 2) / d->ray.ray_dir_y;
}

void	fourth_step_raycast(t_data *d)
{
	d->ray.line_h = (int)(d->win.hight / d->ray.p_wall_d);
	d->ray.dstart = -d->ray.line_h / 2 + d->win.hight / 2;
	d->ray.dend = d->ray.line_h / 2 + d->win.hight / 2;
	if (d->ray.dend >= d->win.hight)
		d->ray.dend = d->win.hight - 1;
	if (d->ray.side == 0)
		d->ray.wallx = d->player.pos_y + d->ray.p_wall_d * d->ray.ray_dir_y;
	else
		d->ray.wallx = d->player.pos_x + d->ray.p_wall_d * d->ray.ray_dir_x;
	d->ray.wallx -= floor(d->ray.wallx);
}

/*
** Функция put_in_img находится в утилитах.
*/

void	fifth_step_raycast(t_data *d, int x)
{
	int y;

	if (d->ray.dstart < 0)
		y = 0;
	else
		y = d->ray.dstart;
	while (y <= d->ray.dend)
	{
		if (d->ray.side == 0 && d->ray.ray_dir_x < 0)
			put_in_img(d, &d->no, x, y);
		if (d->ray.side == 0 && d->ray.ray_dir_x > 0)
			put_in_img(d, &d->so, x, y);
		if (d->ray.side == 1 && d->ray.ray_dir_y < 0)
			put_in_img(d, &d->we, x, y);
		if (d->ray.side == 1 && d->ray.ray_dir_y > 0)
			put_in_img(d, &d->ea, x, y);
		y++;
	}
}
