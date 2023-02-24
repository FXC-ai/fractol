/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:04:01 by fcoindre          #+#    #+#             */
/*   Updated: 2023/02/24 13:04:24 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void display_datas (t_datas *datas)
{

    printf("fractal = %d\n", datas->fractal);
    printf("ini_x = %f\n", datas->ini_x);
    printf("ini_y = %f\n", datas->ini_y);
    printf("step_zoom = %d\n", datas->step_zoom);
    printf("step_x = %d\n", datas->step_x);
    printf("step_y = %d\n", datas->step_y);



}

int fx_mouse_hook(int key_code, int x, int y, t_datas *datas)
{
    (void) x;
    (void) y;
    if (key_code == 4)
    {
        datas->zoom *= 1.5;
        datas->ini_x = 1.5 * datas->ini_x;
        datas->ini_y = 1.5 * datas->ini_y;
        //datas->ini_x -= (((datas->ini_x - (WIDTH / 2)) / datas->zoom)) - (((datas->ini_x) / datas->zoom));
        datas->step_zoom += 1;
        
    }
    else if (key_code == 5)
    {
        datas->zoom /= 1.5;
        //datas->ini_x += (((datas->ini_x - (WIDTH / 2)) / datas->zoom)) - (((datas->ini_x) / datas->zoom));
        datas->step_zoom -= 1;
        datas->ini_x = datas->ini_x / 1.5;
        datas->ini_y = datas->ini_y / 1.5;
    }
    else if (key_code == 1)
    {
        ft_printf("x = %d | y = %d\n", x,x);

    }
    return 0;
}

int fx_kboard_hook(int key_code, t_datas *datas)
{
    int x;
    int y;
    t_im_num c;
    printf("ini : %d\n",key_code);
    if (key_code == 53)
    {
        mlx_destroy_window(datas->vars->mlx, datas->vars->win);
        exit(0);
    }
    else if (key_code == 69)
    {
        datas->zoom *= 1.5;

    }
    else if (key_code == 78)
    {
        datas->zoom /= 1.5;
        /*Il faut corriger le data_x->ini ici a chaque chqngement de zoom */



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
        datas->center_x += 25;
        datas->step_y-=1;
    }
    else if (key_code == 126)
    {
        datas->ini_color = create_trgb(65,0,255,0);
        datas->ini_y += 25;
        datas->step_y+=1;
    }
    else if (key_code == 124)
    {
        datas->ini_color = create_trgb(127,0,255,0);
        datas->ini_x += 25;
        /*
        Il y a 2 cas : soit on bouge de 25 parceque on a pas change de zoom avant
        soit on 
        
        */



        datas->step_x+= 1;
    }
    else if (key_code == 123)
    {
        datas->ini_color = create_trgb(200,0,255,0);
        datas->ini_x -= 25;
        datas->step_x -= 1;
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