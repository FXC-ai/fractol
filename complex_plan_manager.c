/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_plan_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:05:33 by fcoindre          #+#    #+#             */
/*   Updated: 2023/02/24 16:21:35 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_im_num	convert_xy_to_z(t_datas *datas, int x, int y)
{
	t_im_num	z;

	z.re = (((x + datas->ini_x) - (WIDTH / 2)) / datas->zoom);
	z.im = ((((y - (HEIGH / 2)) / datas->zoom))
			- (((datas->ini_y / datas->zoom)))) * (-1);
	return (z);
}

void	fx_display_pix_complex(t_datas *datas)
{
	t_im_num	param;
	int			x;
	int			y;
	int			nb_iter;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		nb_iter = 0;
		while (y < HEIGH)
		{
			param = convert_xy_to_z(datas, x, y);
			if (datas->fractal == 1)
			{
				datas->ini_color = convert_to_color(
						julia(param, datas->c, 200),200);
			}
			else if (datas->fractal == 2)
			{
				datas->ini_color = convert_to_color(mandelbrot(param, 200),
						200);
			}
			else if (datas->fractal == 3)
			{
				datas->ini_color = convert_to_color(z2plusc2(param, 200), 200);
			}
			my_mlx_pixel_put(datas->img, x, y, datas->ini_color);
			y++;
		}
		x++;
	}
}




