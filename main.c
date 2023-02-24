/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:44:01 by fcoindre          #+#    #+#             */
/*   Updated: 2023/02/24 16:07:33 by fcoindre         ###   ########.fr       */
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
        print_arguments();
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
        else if (ft_strncmp(argv[1], "z2plusc2",12) == 0)
        {

            initialise_datas(&datas, &vars, &img, 3);
        }
        else
        {
            print_arguments();
            return (0);
        }
    }
    
    mlx_key_hook(vars.win, fx_kboard_hook, &datas);
    mlx_mouse_hook(vars.win, fx_mouse_hook, &datas);
    mlx_hook(vars.win, ON_DESTROY, 0, close_window, &datas);
    mlx_loop_hook(vars.mlx, &main_loop, &datas);
	mlx_loop(vars.mlx);
    
    return (0);
}


