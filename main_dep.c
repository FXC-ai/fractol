#include "libft/libft.h"
#include <stdio.h>
#include <mlx.h>
#define WINDOW_WIDTH 800
#define WINDOW_LNGTH 400

typedef struct s_data
{
    void    *img;
    void    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_data;

typedef struct s_vars
{
    void    *mlx;
    void    *win;
}   t_vars;



void    fx_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    fx_display_t_data(t_data image)
{
    printf("IMG WIDTH x LENGHT = %d x %d\n", WINDOW_WIDTH, WINDOW_LNGTH);
    printf("void *img          = %p\n", image.img);
    printf("void *addr         = %p\n", image.addr);
    printf("int  *bpp          = %d bytes/pixel\n", image.bits_per_pixel);
    printf("int  *line_length  = %d bytes/line\n", image.line_length);
    printf("int  endian        = %d\n", image.endian);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void    fx_display_square(int size_square, t_data *img)
{
    double i;
    double j;
    
    i = 0;
    j = 0;
    while (i <= size_square)
    {
        j = 0;
        while (j <= size_square)
        {
            if (i >= 0 && i <= size_square)
            {
                fx_mlx_pixel_put(img, i, j, create_trgb(0,0,255,255));
            }
            j++;
        }
        i++;
    }
}

void    fx_display_circle(int size_circle, t_data *img)
{
    double i, j;

    i = 0;
    j = 0;
    while (i <= 2 * size_circle)
    {
        j = 0;
        while (j <= 2 * size_circle)
        {
            if (((i - size_circle) * (i - size_circle) + (j - size_circle) * (j - size_circle)) == (size_circle * size_circle))
            {
                fx_mlx_pixel_put(img, i, j, create_trgb(0,254,0,0));
            }
            j += 1;
        }  
        i += 1;
    }

}

int fx_kboard_hook(int key_code, t_vars *vars)
{
    if (key_code == 53)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    return (0);
}

int fx_mouse_hook(int key_code, t_vars *vars)
{

    (void) vars;

    //printf("key_code = %d\n", key_code);

    if (key_code == 1)
    {
        printf("clic gauche\n");
    }
    

    return (0);
}


int main()
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;
    t_vars  vars;

    int a;
    a = create_trgb(128,255,255,255);
    printf("a = %d\n", a);


    mlx = mlx_init();
    vars.mlx = mlx;


    mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_LNGTH, "fractol");
    vars.win = mlx_win;

    img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_LNGTH);


    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    //fx_display_square(15, &img);
    //fx_display_circle(40, &img);
    //fx_mlx_pixel_put(&img, 100, 100, create_trgb(0, 250,222,22));

    mlx_pixel_put(mlx, mlx_win, 15, 67, create_trgb(0,10,255,10));


    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    fx_display_t_data(img);


    mlx_mouse_hook(vars.win, fx_mouse_hook, &vars);
    mlx_key_hook(mlx_win, fx_kboard_hook, &vars);
    



    mlx_loop(mlx);

    return (0);

}
