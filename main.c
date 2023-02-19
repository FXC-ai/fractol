/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:44:01 by fcoindre          #+#    #+#             */
/*   Updated: 2023/02/19 18:00:27 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "fractol.h"
#include "libft/libft.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>

#define WIDTH 500
#define HEIGH 500
#define ON_DESTROY 17
#define ON_MOUSEDOWN 4

typedef struct s_vars
{
    void    *mlx;
    void    *win;
}   t_vars;

typedef struct s_img
{
    void    *img;
    void    *first_pix;

    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_img;


typedef struct s_datas
{
    t_vars  *vars;
    t_img   *img;

    int     ini_color;
    int     ini_x;
    int     ini_y;
    double  zoom;

}   t_datas;

typedef struct s_im_num
{

    double  re_part;
    double  im_part;

}   t_im_num;

int close_window (t_datas *datas);
int	create_trgb(int t, int r, int g, int b);
int main_loop(t_datas *datas);
int fx_kboard_hook(int key_code, t_datas *datas);
int close_window (t_datas *datas);
void initialise_datas(t_datas *datas, t_vars *vars, t_img *img);
void fx_display_pix_complex(t_datas *datas);
int fx_mouse_hook(t_datas *datas);
t_im_num z2_plus_c(t_im_num z_ini, t_im_num c);
int	create_trgb(int t, int r, int g, int b);
int convert_to_color(int nb_iterations);
int calcute_iterations (t_im_num z_ini, t_im_num c, int max_iterations);

int main()
{
    //z^2 + c
    t_im_num z_ini;
    z_ini.re_part = 0.05;
    z_ini.im_part = 0.01;

    t_im_num c;
    c.re_part = 0.3;
    c.im_part = 0.5;

    int count = 0;
    int max_iterations = 127;

    count = calcute_iterations(z_ini, c, max_iterations);

    printf("color code = %d", convert_to_color(count));

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

    /*GENERATEUR IMAGE*/
    mlx_loop_hook(vars.mlx, &main_loop, &datas);

	mlx_loop(vars.mlx);

    return (0);
}

int calcute_iterations (t_im_num z_ini, t_im_num c, int max_iterations)
{
    int count;
    t_im_num z_cur;
    
    count = 0;
    while (count < max_iterations)
    {
        z_cur = z2_plus_c(z_ini, c);

        z_ini.re_part = z_cur.re_part;
        z_ini.im_part = z_cur.im_part;
        count++;

        if (z_cur.re_part * z_cur.re_part + z_cur.im_part * z_cur.im_part > 4)
        {
            break;
        }

    }
    return count;

}


t_im_num z2_plus_c(t_im_num z_ini, t_im_num c)
{

        t_im_num z_cur;
    
        z_cur.re_part = (z_ini.re_part * z_ini.re_part) - (z_ini.im_part * z_ini.im_part) + c.re_part;
        z_cur.im_part = (2 * z_ini.im_part * z_ini.im_part) + c.im_part;

        printf("[%f + (%fi)]^2 + [(%f) + (%fi)] = %f + (%fi)\n\n",
                z_ini.re_part,
                z_ini.im_part,
                c.re_part,
                c.im_part,
                z_cur.re_part,
                z_cur.im_part);

        return z_cur;
    
}

int convert_to_color(int nb_iterations)
{

    return create_trgb(0,nb_iterations*2,nb_iterations*2,nb_iterations*2);

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
    datas->zoom = 1;

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

int fx_mouse_hook(t_datas *datas)
{

    printf("mouse up\n");
    printf("zoom = %d\n", datas->ini_x);

    return 0;
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
        datas->zoom += 0.1;
        printf("zoom = %f\n", datas->zoom);

    }
    else if (key_code == 78)
    {
        datas->zoom -= 0.1;
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
        datas->ini_y += 10;
    }
    else if (key_code == 126)
    {
        datas->ini_color = create_trgb(65,0,255,0);
        datas->ini_y -= 10;
    }
    else if (key_code == 124)
    {
        datas->ini_color = create_trgb(127,0,255,0);
        datas->ini_x += 10;
    }
    else if (key_code == 123)
    {
        datas->ini_color = create_trgb(200,0,255,0);
        datas->ini_x -= 10;
    }
    return (0);
}



int close_window (t_datas *datas)
{
    (void) datas;
    exit(0);
    return(0);
}


void    fx_display_square(int size_square, t_datas *datas)
{
    int i;
    int j;
    
    i = 0;
    while (i <= size_square)
    {
        j = 0;
        while (j <= size_square)
        {
            my_mlx_pixel_put(datas->img, datas->ini_x+i, datas->ini_y+j, datas->ini_color);
            j++;
        }
        
        i++;
    }
    
}

void fx_display_pix_complex(t_datas *datas)
{

    double real;
    double imaginary;

    //t_im_num z_ini;

    int x = 0;
    int y = 0;
    //double real_int_part;
    //double imaginary_int_part;



    //printf("ini_x = %d ini_y = %d zoom = %f\n", datas->ini_x, datas->ini_y, datas->zoom);
    while (x < WIDTH)
    {
        y = 0;
        while(y < HEIGH)
        {
            real = ((((x - (WIDTH / 2)) / datas->zoom)) - datas->ini_x);
            imaginary = ((((y - (HEIGH / 2)) / datas->zoom)) - datas->ini_y) * (-1);

            if (real == 0 || imaginary == 0)
            {
 
                my_mlx_pixel_put(datas->img, x, y, datas->ini_color);

            }



            /*
            modf(real, &real_int_part);
            modf(imaginary, &imaginary_int_part);

            if ((((int) real_int_part % 10) == 0) && (((int) imaginary_int_part % 10) == 0))
            {
                my_mlx_pixel_put(datas->img, x, y, create_trgb(0,255,255,255));
            }
            */
            //printf("result = %f + (%fi)\n", real, imaginary);
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
    


    //fx_display_square(50, datas);
    fx_display_pix_complex(datas);

	mlx_put_image_to_window((datas->vars)->mlx, (datas->vars)->win, (datas->img)->img, 0, 0);
    return (0);
}



