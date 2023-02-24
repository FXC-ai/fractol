/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:19:25 by fcoindre          #+#    #+#             */
/*   Updated: 2023/02/24 18:15:15 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	initialise_datas(t_datas *datas, t_vars *vars, t_img *img, int fractal)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGH, "Fractol");
	datas->vars = vars;
	datas->img = img;
	datas->ini_color = create_trgb(18, 0, 255, 0);
	datas->ini_x = 0;
	datas->ini_y = 0;
	datas->zoom = 120;
	datas->step_zoom = 0;
	datas->fractal = fractal;
	datas->c.im = 0.75;
	datas->c.re = -0.12;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->first_pix + (y * img->line_length
			+ x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	print_arguments(void)
{
	ft_printf ("Choose a fractal :\n");
	ft_printf ("    - Julia\n");
	ft_printf ("    - Mandelbrot\n");
	ft_printf ("    - z2plusc2\n");
}
