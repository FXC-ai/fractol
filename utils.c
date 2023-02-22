/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:19:25 by fcoindre          #+#    #+#             */
/*   Updated: 2023/02/22 18:32:43 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int convert_to_color(int nb_iterations, int max_iterations)
{
    double  coef;
    int     r;
    int     g;
    int     b;

    if (nb_iterations == -2)
        return (create_trgb(0,0,0,0));
    coef = log((double)nb_iterations) / log((double)max_iterations);
    if (nb_iterations == max_iterations)
        return (create_trgb(0,0,0,0));
    if (nb_iterations >=1 && nb_iterations < 5)
        return create_trgb(0,0,120,140);
    else if (nb_iterations % 2 == 0)
    {
        r = 0.1*255;
        g = (1-coef)*255;
        b = coef*255;
    }
    else
    {
        r = 0.4*coef*255;
        g = coef*255;
        b = (1-coef)*255;
    }
    return create_trgb (0, r,g,b);
}

void initialise_datas(t_datas *datas, t_vars *vars, t_img *img, char *fractal)
{
    vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGH, "Fractol");
    
    datas->vars = vars;
    datas->img = img;
    datas->ini_color = create_trgb(18,0,255,0);
    datas->ini_x = 0;
    datas->ini_y = 0;
    datas->zoom = 120;

    datas->fractal = fractal;
    datas->c.im = 0.75;
    datas->c.re = -0.12;
}



void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	dst = img->first_pix + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}