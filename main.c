/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:44:01 by fcoindre          #+#    #+#             */
/*   Updated: 2023/02/22 18:37:54 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	**ft_create_tab_char(int argc, char *argv[]);
char	*ft_join_args(int argc, char *argv[]);
int	ft_size_table(char **tab_char);
void	ft_free_tab_char(char **tab, int tablen);

int main(int argc, char *argv[])
{
	t_img	        img;
    t_vars          vars;
    t_datas         datas;

    char **tab_char;

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

        tab_char = ft_create_tab_char(argc, argv);
        

        if (ft_strncmp(tab_char[0], "Mandelbrot", 11) == 0)
        {
            initialise_datas(&datas, &vars, &img, "Mandelbrot");

        }
        else if (ft_strncmp(tab_char[0], "Julia", 6) == 0)
        {
            initialise_datas(&datas, &vars, &img, "Julia");

        }

        
        
        ft_free_tab_char(tab_char, ft_size_table(tab_char));
        printf(":::: %s ::::\n", datas.fractal);

        
        

    }
    


    /*

    mlx_hook(vars.win, ON_DESTROY, 0, close_window, &datas);
    mlx_key_hook(vars.win, fx_kboard_hook, &datas);
    mlx_mouse_hook(vars.win, fx_mouse_hook, &datas);
    mlx_loop_hook(vars.mlx, &main_loop, &datas);
	mlx_loop(vars.mlx);
    */
    return (0);
}

int	ft_size_table(char **tab_char)
{
	int	i;

	i = 0;
	while (tab_char[i] != NULL)
		i++;
	return (i);
}

void	ft_free_tab_char(char **tab, int tablen)
{
	int	i;

	i = 0;
	while (i <= tablen)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}


char	*ft_join_args(int argc, char *argv[])
{
	int		i;
	char	*result;
	char	*temp;

	i = 1;
	result = ft_strdup(argv[1]);
	while (i < (argc - 1))
	{
		temp = ft_strdup(result);
		free(result);
		result = ft_strjoin(temp, " ");
		free(temp);
		temp = ft_strdup(result);
		free(result);
		i++;
		result = ft_strjoin(temp, argv[i]);
		free(temp);
	}
	return (result);
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

            datas->ini_color = convert_to_color(calcute_iterations(z, datas->c, 256, z2_plus_c), 256);

            //datas->ini_color = convert_to_color(mandelbrot(z,500), 500);

            my_mlx_pixel_put(datas->img, x, y, datas->ini_color);

            y++;
        }
        x++;
    }
}
