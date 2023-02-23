/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:44:01 by fcoindre          #+#    #+#             */
/*   Updated: 2023/02/23 18:34:26 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int main(int argc, char *argv[])
{
	t_img	        img;
    t_vars          vars;
    t_datas         datas;

    if (argc != 2)
    {
        ft_printf ("Choose a fractal :\n");
        ft_printf ("    - Julia\n");
        ft_printf ("    - Mandelbrot\n");
        ft_printf ("    - Burningship");
        return (0);
    }
    else
    {
        if (ft_strncmp(argv[1], "Mandelbrot", 11) == 0)
        {
            initialise_datas(&datas, &vars, &img, 2);
        }
        else if (ft_strncmp(argv[1], "Julia", 6) == 0)
        {
            initialise_datas(&datas, &vars, &img, 1);
        }
        else
        {
            ft_printf ("Choose a fractal :\n");
            ft_printf ("    - Julia\n");
            ft_printf ("    - Mandelbrot\n");
            ft_printf ("    - Burningship\n");            
            return (0);
        }
    }
    
    mlx_hook(vars.win, ON_DESTROY, 0, close_window, &datas);
    mlx_key_hook(vars.win, fx_kboard_hook, &datas);
    mlx_mouse_hook(vars.win, fx_mouse_hook, &datas);
    mlx_loop_hook(vars.mlx, &main_loop, &datas);
	mlx_loop(vars.mlx);
    
    return (0);
}

t_im_num convert_xy_to_z(t_datas *datas, int x, int y)
{
    t_im_num z;


    z.re = (((x - (WIDTH / 2)) / datas->zoom)) + ((((datas->ini_x * datas->step_zoom) / datas->zoom)) /*- ((datas->step_zoom * 25) / datas->zoom)*/);
    
    //z.re = (((((x - datas->ini_x)- (WIDTH / 2)) / datas->zoom)));



    z.im = ((((y - (HEIGH / 2)) / datas->zoom)) - (((datas->ini_y / datas->zoom)))) * (-1);

    return (z);
}

void fx_display_pix_complex(t_datas *datas)
{

    t_im_num z;


    int x = 0;
    int y = 0;
    int nb_iter;

    while (x < WIDTH)
    {
        y = 0;
        nb_iter = 0;
        while(y < HEIGH)
        {

            z = convert_xy_to_z(datas, x, y);

            if (datas->fractal == 1)
            {
                datas->ini_color = convert_to_color(calcute_iterations(z, datas->c, 200, z2_plus_c), 200);
            }
            else if (datas->fractal == 2)
            {
                datas->ini_color = convert_to_color(mandelbrot(z,200), 200);
            }
            
            my_mlx_pixel_put(datas->img, x, y, datas->ini_color);
            my_mlx_pixel_put(datas->img, 250, 250, create_trgb(0,255,0,0));

            y++;
        }
        x++;
    }
}
