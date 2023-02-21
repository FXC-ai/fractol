/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:44:01 by fcoindre          #+#    #+#             */
/*   Updated: 2023/02/21 22:32:17 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int close_window (t_datas *datas);
int	create_trgb(int t, int r, int g, int b);
int main_loop(t_datas *datas);
int fx_kboard_hook(int key_code, t_datas *datas);
int close_window (t_datas *datas);
void initialise_datas(t_datas *datas, t_vars *vars, t_img *img);
void fx_display_pix_complex(t_datas *datas);
int fx_mouse_hook(int key_code, int x, int y, t_datas *datas);
t_im_num z2_plus_c(t_im_num z_ini, t_im_num c);
int	create_trgb(int t, int r, int g, int b);
int convert_to_color(int nb_iterations, int max_iterations);
int calcute_iterations (t_im_num z_ini, t_im_num c, int max_iterations);

int main()
{


    t_vars          vars;
	t_img	        img;
    t_datas         datas;

    initialise_datas(&datas, &vars, &img);

    /*DESTROY*/
    mlx_hook(vars.win, ON_DESTROY, 0, close_window, &datas);

    /*SURVEY MOUSE*/
    //mlx_hook(vars.win, ON_MOUSEDOWN, 0, fx_mouse_hook, &datas);
    /*PRESS KEY*/
    mlx_key_hook(vars.win, fx_kboard_hook, &datas);

    
    mlx_mouse_hook(vars.win, fx_mouse_hook, &datas);
    /*GENERATEUR IMAGE*/
    mlx_loop_hook(vars.mlx, &main_loop, &datas);

	mlx_loop(vars.mlx);

    return (0);
}

int fx_mouse_hook(int key_code, int x, int y, t_datas *datas)
{
    (void) x;
    (void) y;
    if (key_code == 1)
    {
        printf("zoom = %f\n", datas->zoom);
    
    }
    
    
    //printf("Action mouse = %d", key_code);
    return 0;
}

int calcute_iterations (t_im_num z_ini, t_im_num c, int max_iterations)
{
    int count;
    t_im_num z_cur;
    
    count = 0;
    while (count < max_iterations)
    {
        z_cur = z2_plus_c(z_ini, c);
        z_ini.re = z_cur.re;
        z_ini.im = z_cur.im;
        count++;
        
        if (z_cur.re * z_cur.re + z_cur.im * z_cur.im > 4)
        {
            break;
        }
    }
    return count;

}


t_im_num z2_plus_c(t_im_num z_ini, t_im_num c)
{
        t_im_num z_cur;
    
        z_cur.re = (z_ini.re * z_ini.re) - (z_ini.im * z_ini.im) + c.re;
        z_cur.im = (2 * z_ini.im * z_ini.re) + c.im;

        return z_cur;
}

int convert_to_color(int nb_iterations, int max_iterations)
{

    double  coef;
    int r;
    int g;
    int b;
    int t;

    t = 0;
    coef = log((double)nb_iterations) / log((double)max_iterations);

    if (nb_iterations == max_iterations)
    {
        return create_trgb(0,0,0,0); //NOIR
    }

    
    r = 0.1*coef*255;
    g = (1-coef)*255;
    b = 0.8*coef*255;

    if (r + g + b > 650)
    {
        t = 127;
    }
    

    return create_trgb (t, r,g,b);
    
}

void initialise_datas(t_datas *datas, t_vars *vars, t_img *img)
{

    vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGH, "Fractol");

    datas->vars = vars;
    datas->img = img;

    datas->ini_color = create_trgb(18,0,255,0);

    datas->ini_x = 0;
    datas->ini_y = 0;
    datas->zoom = 120;

}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->first_pix + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



int fx_kboard_hook(int key_code, t_datas *datas)
{
    int x;
    int y;
    double ajust;



    if (key_code == 53)
    {
        mlx_destroy_window(datas->vars->mlx, datas->vars->win);
        exit(0);
    }
    else if (key_code == 69)
    {
        datas->zoom *= 1.2;
        printf("zoom = %f\n", datas->zoom);

    }
    else if (key_code == 78)
    {
        datas->zoom /= 1.2;
        printf("zoom = %f\n", datas->zoom);
    }
    else if (key_code == 12)
    {
        mlx_mouse_get_pos(datas->vars->win , &x, &y);
        ft_printf("[x= %d | y= %d] : ", x, y);
        ajust = 23 / datas->zoom;
        printf("%f + (%fi)",(((((double)x - (WIDTH / 2)) / datas->zoom)) - datas->ini_x),
                              (((((double)y - (HEIGH / 2)) / datas->zoom)) - datas->ini_y - ajust) * (-1));
        printf(" | zoom = %f\n", datas->zoom);
    
    }
    else if (key_code == 125)
    {
        datas->ini_color = create_trgb(0,0,255,0);
        datas->ini_y += 25;
    }
    else if (key_code == 126)
    {
        datas->ini_color = create_trgb(65,0,255,0);
        datas->ini_y -= 25;
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
    t_im_num c;

    int x = 0;
    int y = 0;

    int nb_iter;


    c.re = 0.3;
    c.im = 0.5;

    while (x < WIDTH)
    {
        y = 0;
        nb_iter = 0;
        while(y < HEIGH)
        {
            //ATTENTION IL FAUDRA ADAPTER LE DEPLACEMENT AU ZOOM !!!

            //z_ini.re = ((((x - (WIDTH / 2)) / datas->zoom)) - datas->ini_x);
            //z_ini.im = ((((y - (HEIGH / 2)) / datas->zoom)) - datas->ini_y) * (-1);
            z = convert_xy_to_z(datas, x, y);

            datas->ini_color = convert_to_color(calcute_iterations(z, c, 256), 256);
            my_mlx_pixel_put(datas->img, x, y, datas->ini_color);

            y++;
        }
        x++;
    }
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



