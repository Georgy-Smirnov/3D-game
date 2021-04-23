/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_calculated.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 18:53:56 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/21 18:54:00 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rcast.h"

/*
** Функции перемещения и вращения игрока.
** ms - скорость перемещения и ts - скорость поворота
** указаны в rcast.h
*/

void	move_w_s(t_data *img, double ms)
{
	double p_x;
	double p_y;
	double d_x;
	double d_y;

	p_x = img->player.pos_x;
	p_y = img->player.pos_y;
	d_x = img->player.dir_x;
	d_y = img->player.dir_y;
	if (img->map[(int)(p_x + d_x * ms)][(int)p_y] != '1')
		img->player.pos_x += d_x * ms;
	if (img->map[(int)p_x][(int)(p_y + d_y * ms)] != '1')
		img->player.pos_y += d_y * ms;
}

void	move_a_d(t_data *img, double ms)
{
	double p_x;
	double p_y;
	double pl_x;
	double pl_y;

	p_x = img->player.pos_x;
	p_y = img->player.pos_y;
	pl_x = img->player.plane_x;
	pl_y = img->player.plane_y;
	if (img->map[(int)(p_x + pl_x * ms)][(int)p_y] != '1')
		img->player.pos_x += pl_x * ms;
	if (img->map[(int)p_x][(int)(p_y + pl_y * ms)] != '1')
		img->player.pos_y += pl_y * ms;
}

void	turn_l_r(t_data *img, double ts)
{
	double old_dx;
	double old_px;

	old_dx = img->player.dir_x;
	old_px = img->player.plane_x;
	img->player.dir_x = img->player.dir_x * cos(ts) -
	img->player.dir_y * sin(ts);
	img->player.dir_y = old_dx * sin(ts) + img->player.dir_y * cos(ts);
	img->player.plane_x = img->player.plane_x * cos(ts) -
	img->player.plane_y * sin(ts);
	img->player.plane_y = old_px * sin(ts) + img->player.plane_y * cos(ts);
}
