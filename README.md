# fract’ol

## Captures d'écran
[Capture1](https://github.com/FXC-ai/fractol/blob/master/pictures/1.png)
[Capture2](https://github.com/FXC-ai/fractol/blob/master/pictures/2.png)
[Capture3](https://github.com/FXC-ai/fractol/blob/master/pictures/3.png)
[Capture4](https://github.com/FXC-ai/fractol/blob/master/pictures/4.png)
[Capture5](https://github.com/FXC-ai/fractol/blob/master/pictures/5.png)
[Capture6](https://github.com/FXC-ai/fractol/blob/master/pictures/6.png)
[Capture7](https://github.com/FXC-ai/fractol/blob/master/pictures/7.png)
[Capture8](https://github.com/FXC-ai/fractol/blob/master/pictures/8.png)
[Capture9](https://github.com/FXC-ai/fractol/blob/master/pictures/9.png)
[Capture10](https://github.com/FXC-ai/fractol/blob/master/pictures/10.png)

## Fonctionnement le la MinilibX

Les variables sont stockees dans la stack et on les modifie par référence 

```c
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
    // line_lenght = image_width * (bpp / 8)
    *(unsigned int*)dst = color;
    //cast le int en parametre dans un unsigned int, puis derefence afin d'asigner la valeur de color a dst

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
    double i, j;
    
    i = 0;
    j = 0;
    while (i <= size_square)
    {
        j = 0;
        while (j <= size_square)
        {
            if (i <= 0 || i <= size_square || j <= 0 || j <= size_square)
            {
                fx_mlx_pixel_put(img, i, j, create_trgb(0,51,51,255));
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

    printf("key_code = %d\n", key_code);

    //mlx_mouse_get_pos(vars->win, &x, &y);

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

    //printf("a = %d\n", a);
    //printf("a = %d\n", OxFF);

    //initialize the connection between the software and the display
    mlx = mlx_init();
    vars.mlx = mlx;

    //creates a new window, using the size_x and size_y parameters. The mlx_ptr parameter
    // is the connection identifier returned by mlx_init. It returns a void * window 
    // identifier that can be used by other MiniLibX calls.
    mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_LNGTH, "fractol");
    vars.win = mlx_win;

    // mlx_new_image creates a new image in memory. 
    // It returns a void * identifier needed to manipulate this image later.
    img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_LNGTH); //(pointer, x, y)

    //Returns ...
    //The img_ptr parameter specifies the image  to  use.
    //bits_per_pixel will be filled with the number of bits needed to represent a pixel color
    //size_line is the number of bytes used to store one line of  the  image  in  memory
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    fx_display_square(150, &img);
    fx_display_circle(40, &img);

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    fx_display_t_data(img);

    mlx_mouse_hook(vars.win, fx_mouse_hook, &vars);
    mlx_key_hook(mlx_win, fx_kboard_hook, &vars);
    

    mlx_loop(mlx);

    return (0);

}
```

## Sources

[GitHub - pvaladares/42cursus-02-fract-ol: Discover 2D programming and the psychedelic universe of fractals in this project, using minilibX.](https://github.com/pvaladares/42cursus-02-fract-ol)

[GitHub - terry-yes/mlx_example: Some examples for those who try to use MLX library for 42 subject CUB3D or miniRT. And some helpful links.](https://github.com/terry-yes/mlx_example)

Exemples pour apprendre à utiliser la minilibx : [42-Fractol/man_mlx_new_image.md at master · nmei-42/42-Fractol](https://github.com/nmei-42/42-Fractol/blob/master/minilibx/man_mlx_new_image.md), [Getting started](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html)

Documentation sur la minilibx : [The Julia and Mandelbrot Set](https://lodev.org/cgtutor/juliamandelbrot.html)

Cheat codes pour le projet ? : [ft_libgfx AKA b_gfx overload](https://qst0.github.io/ft_libgfx/#getting-started-with-fractol-ft_fractal)

Commencer avec le projet fractol : [Pixel drawing with the miniblix](https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx)

Tutoriel MinilibX : [RGB Color Codes Chart](https://www.rapidtables.com/web/color/RGB_Color.html)

Pour les couleurs : [Auto-Math](https://www.auto-math.be/public/8/module/18/theorie/74)

Pour les mathématiques du plan complexe : [A propos des fractales](https://www.youtube.com/watch?v=Y4ICbYtBGzA)
