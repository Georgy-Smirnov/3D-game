/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjaco <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:46:02 by kjaco             #+#    #+#             */
/*   Updated: 2021/03/21 19:46:05 by kjaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rcast.h"

void	return_struct(t_data *data)
{
	data->move_f.press_a = 0;
	data->move_f.press_w = 0;
	data->move_f.press_s = 0;
	data->move_f.press_d = 0;
	data->move_f.press_left = 0;
	data->move_f.press_right = 0;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
}

int		create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
