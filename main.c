#include "fractol.h"
#include "libft/libft.h"
#include "mlx.h"
#include <stdio.h>

#define WIDTH 500
#define HEIGH 500
#define ON_DESTROY 17

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

int close_window (t_datas *datas);
int	create_trgb(int t, int r, int g, int b);
int main_loop(t_datas *datas);
int fx_kboard_hook(int key_code, t_datas *datas);
int close_window (t_datas *datas);
void initialise_datas(t_datas *datas, t_vars *vars, t_img *img);
void fx_display_pix_complex(t_datas *datas, double zoom);


int main()
{
    t_vars          vars;
	t_img	        img;
    t_datas         datas;

    initialise_datas(&datas, &vars, &img);

    /*DESTROY*/
    mlx_hook(vars.win, ON_DESTROY, 0, close_window, &datas);

    /*PRESS KEY*/
    mlx_key_hook(vars.win, fx_kboard_hook, &datas);

    /*GENERATEUR IMAGE*/
    mlx_loop_hook(vars.mlx, &main_loop, &datas);

	mlx_loop(vars.mlx);

    return (0);
}

void initialise_datas(t_datas *datas, t_vars *vars, t_img *img)
{

    vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGH, "Fractol");

    datas->vars = vars;
    datas->img = img;

    datas->ini_color = create_trgb(0,255,0,0);

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

int fx_kboard_hook(int key_code, t_datas *datas)
{
    int x;
    int y;

    if (key_code == 53)
    {
        mlx_destroy_window(datas->vars->mlx, datas->vars->win);
        exit(0);
    }
    else if (key_code == 12)
    {
        mlx_mouse_get_pos(datas->vars->win , &x, &y);
        ft_printf("x= %d et y= %d\n", x, y);
    }
    else if (key_code == 125)
    {
        datas->ini_color = create_trgb(0,0,255,255);
        datas->ini_y += 10;
    }
    else if (key_code == 126)
    {
        datas->ini_color = create_trgb(0,255,0,0);
        datas->ini_y -= 10;
    }
    else if (key_code == 124)
    {
        datas->ini_color = create_trgb(0,0,0,255);
        datas->ini_x += 10;
    }
    else if (key_code == 123)
    {
        datas->ini_color = create_trgb(0,0,255,0);
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

void fx_display_pix_complex(t_datas *datas, double zoom)
{

    double real;
    double imaginary;
    int x = 0;
    int y = 0;


    //printf("ini_x = %d ini_y = %d zoom = %f\n", datas->ini_x, datas->ini_y, datas->zoom);
    while (x < WIDTH)
    {
        y = 0;
        while(y < HEIGH)
        {
            real = (((x - (WIDTH / 2)) / zoom)) - datas->ini_x;
            imaginary = (((y - (HEIGH / 2)) / zoom)) - datas->ini_y;
            if (real == 0 || imaginary == 0)
            {
 
                my_mlx_pixel_put(datas->img, x, y, datas->ini_color);

            }
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
    fx_display_pix_complex(datas, 1);

	mlx_put_image_to_window((datas->vars)->mlx, (datas->vars)->win, (datas->img)->img, 0, 0);
    return (0);
}



