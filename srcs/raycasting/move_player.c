/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 18:56:42 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/21 18:56:47 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rcast.h"

/*
** Функции изменяют флаг нажатой кнопки. При нажатии флаг - 1.
** При отпуски клавиши флаг - 0.
*/

int		key_hook(int keycode, t_data *img)
{
	if (keycode == KC_ESC)
		my_exit(img);
	if (keycode == KC_S)
		img->move_f.press_s = 0;
	if (keycode == KC_A)
		img->move_f.press_a = 0;
	if (keycode == KC_D)
		img->move_f.press_d = 0;
	if (keycode == KC_W)
		img->move_f.press_w = 0;
	if (keycode == KC_LEFT)
		img->move_f.press_left = 0;
	if (keycode == KC_RIGHT)
		img->move_f.press_right = 0;
	return (1);
}

int		key_press(int keycode, t_data *img)
{
	if (keycode == KC_ESC)
		my_exit(img);
	if (keycode == KC_S)
		img->move_f.press_s = 1;
	if (keycode == KC_A)
		img->move_f.press_a = 1;
	if (keycode == KC_D)
		img->move_f.press_d = 1;
	if (keycode == KC_W)
		img->move_f.press_w = 1;
	if (keycode == KC_LEFT)
		img->move_f.press_left = 1;
	if (keycode == KC_RIGHT)
		img->move_f.press_right = 1;
	return (1);
}

/*
** Функция начинает алгоритм расчета и отрисовки изображения.
*/

void	put_d(t_data *d)
{
	int		x;
	double	zbufer[d->win.width];

	x = 0;
	while (x < d->win.width)
	{
		first_step_raycast(d, x);
		second_step_raycast(d);
		third_step_raycast(d);
		fourth_step_raycast(d);
		fifth_step_raycast(d, x);
		zbufer[x] = d->ray.p_wall_d;
		x++;
	}
	put_sprites(d, zbufer);
	mlx_put_image_to_window(d->win.mlx, d->win.win, d->win.img, 0, 0);
}

/*
** Функция запускает необходимую функцию в зависимости от
** зажатой клавиши и запускает функцию отрисовки изображения.
** Функция my_clear_window находится в утилитах. Функции движения
** находятся в файле ./move_calculated.c.
*/

int		move(t_data *img)
{
	my_clear_window(img);
	if (img->move_f.press_w)
		move_w_s(img, (double)MS);
	if (img->move_f.press_s)
		move_w_s(img, (double)-MS);
	if (img->move_f.press_a)
		move_a_d(img, (double)-MS);
	if (img->move_f.press_d)
		move_a_d(img, (double)MS);
	if (img->move_f.press_left)
		turn_l_r(img, (double)TS);
	if (img->move_f.press_right)
		turn_l_r(img, (double)-TS);
	put_d(img);
	return (1);
}
