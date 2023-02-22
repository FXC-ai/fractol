/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:44:01 by fcoindre          #+#    #+#             */
/*   Updated: 2023/02/22 17:28:50 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int main(int argc, char *argv[])
{

    char *tab_char;
    if (argc == 1)
    {
        ft_printf ("Choose a fractal :\n");
        ft_printf ("    - Julia [a][b]\n");
        ft_printf ("    - Mandelbrot\n");
        ft_printf ("    - Burningship");
        return (0);
    }
    else
    {

        tab_char = ft_create_tab_char();


    }
    


    /*
    t_vars          vars;
	t_img	        img;
    t_datas         datas;

    initialise_datas(&datas, &vars, &img);
    mlx_hook(vars.win, ON_DESTROY, 0, close_window, &datas);
    mlx_key_hook(vars.win, fx_kboard_hook, &datas);
    mlx_mouse_hook(vars.win, fx_mouse_hook, &datas);
    mlx_loop_hook(vars.mlx, &main_loop, &datas);
	mlx_loop(vars.mlx);
    */
    return (0);
}

char	**ft_create_tab_char(int argc, char *argv[])
{
	char	*args;
	char	**tab_char;

	if (argc == 2)
	{
		args = ft_strdup(argv[1]);
	}
	else
	{
		args = ft_join_args(argc, argv);
	}
	tab_char = ft_split(args, ' ');
	free(args);
	return (tab_char);
}


t_im_num convert_xy_to_z(t_datas *datas, int x, int y)
{
    t_im_num z;

    z.re = ((((x - (WIDTH / 2)) / datas->zoom)) - (((datas->ini_x) / datas->zoom)));
    z.im = ((((y - (HEIGH / 2)) / datas->zoom)) - (((datas->ini_y) / datas->zoom))) * (-1);

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

            //datas->ini_color = convert_to_color(calcute_iterations(z, datas->c, 256, z2_plus_c), 256);

            datas->ini_color = convert_to_color(mandelbrot(z,500), 500);

            my_mlx_pixel_put(datas->img, x, y, datas->ini_color);

            y++;
        }
        x++;
    }
}
