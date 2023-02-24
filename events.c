/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:04:01 by fcoindre          #+#    #+#             */
/*   Updated: 2023/02/24 15:07:26 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void display_datas (t_datas *datas)
{
    printf("fractal = %d\n", datas->fractal);
    printf("ini_x = %f\n", datas->ini_x);
    printf("ini_y = %f\n", datas->ini_y);

}

int fx_mouse_hook(int key_code, int x, int y, t_datas *datas)
{
    if (key_code == 4)
    {
        datas->zoom *= 1.5;
        datas->ini_x = 1.5 * datas->ini_x;
        datas->ini_y = 1.5 * datas->ini_y;
    }
    else if (key_code == 5)
    {
        datas->zoom /= 1.5;
        datas->ini_x = datas->ini_x / 1.5;
        datas->ini_y = datas->ini_y / 1.5;
    }
    else if (key_code == 1)
    {
        ft_printf("x = %d | y = %d\n", x,y);
    }
    return 0;
}

int fx_kboard_hook(int key_code, t_datas *datas)
{
    int x;
    int y;
    t_im_num c;

    if (key_code == 53)
    {
        mlx_destroy_window(datas->vars->mlx, datas->vars->win);
        exit(0);
    }
    else if (key_code == 12)
    {
        mlx_mouse_get_pos(datas->vars->win , &x, &y);
        if (datas->fractal == 1)
        {
            c = convert_xy_to_z(datas, x, y);
            datas->c.re = c.re;
            datas->c.im = c.im;
        }
        display_datas(datas);

    }
    else if (key_code == 125)
    {
        datas->ini_color = create_trgb(0,0,255,0);
        datas->ini_y -= 25;

    }
    else if (key_code == 126)
    {
        datas->ini_color = create_trgb(65,0,255,0);
        datas->ini_y += 25;

    }
    else if (key_code == 124)
    {
        datas->ini_color = create_trgb(127,0,255,0);
        datas->ini_x += 25;

    }
    else if (key_code == 123)
    {
        datas->ini_color = create_trgb(200,0,255,0);
        datas->ini_x -= 25;

    }
    return (0);
}

int close_window (t_datas *datas)
{
    (void) datas;
    exit(0);
    return(0);
}

int main_loop(t_datas *datas)
{
    datas->img->img = mlx_new_image(datas->vars->mlx, WIDTH, HEIGH);
    datas->img->first_pix = mlx_get_data_addr(datas->img->img, 
                                        &datas->img->bits_per_pixel, 
                                        &datas->img->line_length,
                                        &datas->img->endian);
    fx_display_pix_complex(datas);
	mlx_put_image_to_window((datas->vars)->mlx, (datas->vars)->win, (datas->img)->img, 0, 0);
    return (0);
}