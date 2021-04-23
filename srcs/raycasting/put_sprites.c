/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:30:23 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/21 19:30:27 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rcast.h"

/*
** Функции вычеслений информации для отрисовки спрайтов.
*/

void	sort_sprites(int *sp_order, int *sp_distens, int count)
{
	int i;
	int k;
	int tmp;

	i = 1;
	while (i < count)
	{
		k = i;
		while (k > 0 && sp_distens[k - 1] < sp_distens[k])
		{
			tmp = sp_distens[k - 1];
			sp_distens[k - 1] = sp_distens[k];
			sp_distens[k] = tmp;
			tmp = sp_order[k - 1];
			sp_order[k - 1] = sp_order[k];
			sp_order[k] = tmp;
			k--;
		}
		i++;
	}
	i = 0;
}

void	sprite_draw_calc(t_data *d, int i, int *sp_order)
{
	double sprite_x;
	double sprite_y;
	double inv_det;

	sprite_x = d->spr[sp_order[i]].sp_x - d->player.pos_x;
	sprite_y = d->spr[sp_order[i]].sp_y - d->player.pos_y;
	inv_det = 1.0 / (d->player.plane_x * d->player.dir_y -
	d->player.dir_x * d->player.plane_y);
	d->sp.transform_x = inv_det * (d->player.dir_y * sprite_x -
	d->player.dir_x * sprite_y);
	d->sp.transform_y = inv_det * (-d->player.plane_y * sprite_x +
	d->player.plane_x * sprite_y);
	d->sp.sprite_screen_x = (int)((d->win.width / 2) * (1 + d->sp.transform_x /
	d->sp.transform_y));
	d->sp.sprite_height = abs((int)(d->win.hight / d->sp.transform_y));
	d->sp.drawstart_y = -d->sp.sprite_height / 2 + d->win.hight / 2;
	if (d->sp.drawstart_y < 0)
		d->sp.drawstart_y = 0;
	d->sp.drawend_y = d->sp.sprite_height / 2 + d->win.hight / 2;
	if (d->sp.drawend_y >= d->win.hight)
		d->sp.drawend_y = d->win.hight - 1;
	d->sp.sprite_width = abs((int)(d->win.hight / d->sp.transform_y));
}

void	put_sprite_in_img(t_data *d, double *zbufer, int stripe)
{
	int tex_x;
	int tex_y;
	int y;
	int k;

	tex_x = (int)(256 * (stripe - (-d->sp.sprite_width /
	2 + d->sp.sprite_screen_x)) * d->s.text_h / d->sp.sprite_width) / 256;
	if (d->sp.transform_y > 0 && stripe > 0 && stripe < d->win.width &&
	d->sp.transform_y < zbufer[stripe])
	{
		y = d->sp.drawstart_y;
		while (y < d->sp.drawend_y)
		{
			k = y * 256 - d->win.hight * 128 + d->sp.sprite_height * 128;
			tex_y = ((k * d->s.text_h) / d->sp.sprite_height) / 256;
			d->ray.dst = d->win.addr + (y * d->win.line_length + stripe *
			(d->win.bits_per_pixel / 8));
			d->ray.src = d->s.addr + (tex_y * d->s.line_length + tex_x *
			(d->s.bits_per_pixel / 8));
			if (*(unsigned int *)d->ray.src != 0)
				*(unsigned int *)d->ray.dst = *(unsigned int *)d->ray.src;
			y++;
		}
	}
}

void	sprite_second_calc(t_data *d, double *zbufer)
{
	int stripe;

	d->sp.drawstart_x = -d->sp.sprite_width / 2 + d->sp.sprite_screen_x;
	if (d->sp.drawstart_x < 0)
		d->sp.drawstart_x = 0;
	d->sp.drawend_x = d->sp.sprite_width / 2 + d->sp.sprite_screen_x;
	if (d->sp.drawend_x >= d->win.width)
		d->sp.drawend_x = d->win.width - 1;
	stripe = d->sp.drawstart_x;
	while (stripe < d->sp.drawend_x)
	{
		put_sprite_in_img(d, zbufer, stripe);
		stripe++;
	}
}

void	put_sprites(t_data *d, double *zbufer)
{
	int i;
	int sp_order[d->count_sp];
	int sp_distens[d->count_sp];

	i = 0;
	while (i < d->count_sp)
	{
		sp_order[i] = i;
		sp_distens[i] = ((d->player.pos_x - d->spr[i].sp_x) *
		(d->player.pos_x - d->spr[i].sp_x)) +
		((d->player.pos_y - d->spr[i].sp_y) *
		(d->player.pos_y - d->spr[i].sp_y));
		i++;
	}
	sort_sprites(sp_order, sp_distens, d->count_sp);
	i = 0;
	while (i < d->count_sp)
	{
		sprite_draw_calc(d, i, sp_order);
		sprite_second_calc(d, zbufer);
		i++;
	}
}
