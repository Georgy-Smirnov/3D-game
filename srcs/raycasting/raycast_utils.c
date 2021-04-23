/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_result.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:00:29 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/15 14:00:31 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rcast.h"

/*
** Функция получает адрес пикселя и устанавливает там
** необходимый цвет.
*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->win.addr + (y * data->win.line_length + x *
	(data->win.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*
** Функция заменяет цвет в изображении на цвет пискеля из текстуры.
*/

void	put_in_img(t_data *d, t_text *t, int x, int y)
{
	double f;

	d->ray.tex_x = (int)(d->ray.wallx * (double)t->text_w);
	if (d->ray.side == 0 && d->ray.ray_dir_x > 0)
		d->ray.tex_x = t->text_w - d->ray.tex_x - 1;
	if (d->ray.side == 1 && d->ray.ray_dir_y < 0)
		d->ray.tex_x = t->text_w - d->ray.tex_x - 1;
	f = (double)d->ray.line_h / (double)t->text_h;
	d->ray.tex_y = (double)(y - d->ray.dstart);
	d->ray.tex_y = d->ray.tex_y / f;
	if (d->ray.tex_y >= t->text_h)
		d->ray.tex_y = t->text_h - 1;
	d->ray.dst = d->win.addr + (y * d->win.line_length + x *
	(d->win.bits_per_pixel / 8));
	d->ray.src = t->addr + (d->ray.tex_y * t->line_length + d->ray.tex_x *
	(t->bits_per_pixel / 8));
	if (*(unsigned int *)d->ray.src != 0)
		*(unsigned int *)d->ray.dst = *(unsigned int*)d->ray.src;
}

/*
** Проверяет, удалось ли открыть изображение текстур.
*/

void	*check_path(t_data *d, t_all_info *info)
{
	if (d->no.img == NULL)
		return (error_step("Can't open NO texture.", NULL, info));
	if (d->so.img == NULL)
		return (error_step("Can't open SO texture.", NULL, info));
	if (d->we.img == NULL)
		return (error_step("Can't open WE texture.", NULL, info));
	if (d->ea.img == NULL)
		return (error_step("Can't open EA texture.", NULL, info));
	if (d->s.img == NULL)
		return (error_step("Can't open S texture.", NULL, info));
	return (d);
}

/*
** Функция открывает файлы для текстур и получает их адрес.
** В случае ошибки возвращает 0.
*/

int		open_texture(t_data *d, t_all_info *info)
{
	d->no.img = mlx_xpm_file_to_image(d->win.mlx, d->no.path,
	&d->no.text_w, &d->no.text_h);
	d->so.img = mlx_xpm_file_to_image(d->win.mlx, d->so.path,
	&d->so.text_w, &d->so.text_h);
	d->we.img = mlx_xpm_file_to_image(d->win.mlx, d->we.path,
	&d->we.text_w, &d->we.text_h);
	d->ea.img = mlx_xpm_file_to_image(d->win.mlx, d->ea.path,
	&d->ea.text_w, &d->ea.text_h);
	d->s.img = mlx_xpm_file_to_image(d->win.mlx, d->s.path,
	&d->s.text_w, &d->s.text_h);
	if (check_path(d, info) == NULL)
		return (0);
	d->no.addr = mlx_get_data_addr(d->no.img,
	&d->no.bits_per_pixel, &d->no.line_length, &d->no.endian);
	d->so.addr = mlx_get_data_addr(d->so.img,
	&d->so.bits_per_pixel, &d->so.line_length, &d->so.endian);
	d->we.addr = mlx_get_data_addr(d->we.img,
	&d->we.bits_per_pixel, &d->we.line_length, &d->we.endian);
	d->ea.addr = mlx_get_data_addr(d->ea.img,
	&d->ea.bits_per_pixel, &d->ea.line_length, &d->ea.endian);
	d->s.addr = mlx_get_data_addr(d->s.img,
	&d->s.bits_per_pixel, &d->s.line_length, &d->s.endian);
	return (1);
}

/*
** Функция отрисовывает верхнюю и нижнюю половину окна
** в соответствии с задаными цветами.
*/

void	my_clear_window(t_data *img)
{
	int i;
	int j;

	i = 0;
	while (i < img->win.hight / 2)
	{
		j = 0;
		while (j < img->win.width)
		{
			my_mlx_pixel_put(img, j, i, img->win.color_c);
			j++;
		}
		i++;
	}
	while (i < img->win.hight)
	{
		j = 0;
		while (j < img->win.width)
		{
			my_mlx_pixel_put(img, j, i, img->win.color_f);
			j++;
		}
		i++;
	}
}
