#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mlx.h"

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

    int     *color;
    int     *x;
    int     *y;

}   t_datas;



int closed (t_vars vars);
int display_wait(t_vars vars);
int display_coord(int x, int y, t_vars vars);
int test (int x, int y, void *param);
int on_expose_test (void *param);
int main_loop(t_datas *datas);

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
    else if (key_code == 0)
    {
        printf("A appuye\n");
    }
    else if (key_code == 12)
    {
        mlx_mouse_get_pos(datas->vars->win , &x, &y);
        printf("x= %d et y= %d\n", x, y);
    }
    else if (key_code == 125)
    {
        *(datas->y) += 50;
    }
    else if (key_code == 126)
    {
        *(datas->y) -= 50;
    }
    else if (key_code == 124)
    {
        *(datas->x) += 50;
    }
    else if (key_code == 123)
    {
        *(datas->x) -= 50;
    }
    return (0);
}

int main()
{




    t_vars  vars;
	t_img	img;
    t_datas datas;
    int     color = create_trgb(0,255,0,0);
    int     x = 10;
    int     y = 10;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Fractol");

	//img.img = mlx_new_image(vars.mlx, 1920, 1080);
	//img.first_pix = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    datas.vars = &vars;
    datas.img = &img;
    datas.color = &color;
    datas.x = &x;
    datas.y = &y;



    /*PRESS KEY*/
    mlx_key_hook(vars.win, fx_kboard_hook, &datas);
    /*DESTROY*/
    mlx_hook(vars.win, 17, 0, closed, &vars);

    /*MOUSE MOVE*/
    mlx_hook(vars.win, 6, 0, test, &vars);
    /*ON EXPOSE*/
    mlx_hook(vars.win, 12, 0, on_expose_test, &vars);
    
    mlx_loop_hook(vars.mlx, &main_loop, &datas);

	mlx_loop(vars.mlx);

    return (0);
}

int closed (t_vars vars)
{
    (void)vars;
    exit(0);
    return(1);
}

int test (int x, int y, void *param)
{
    (void) x;
    (void) y;
    (void) param;

    printf("la souris bouge : %d %d\n", x, y);
    return (0);
}

int on_expose_test (void *param)
{
    (void) param;

    printf("ON_EXPOSE active\n");

    return (0);
}


void    fx_display_square(int size_square, t_datas *datas)
{
    
    my_mlx_pixel_put(datas->img, *(datas->x), *(datas->y), *(datas->color));

    int i;
    int j;
    i = 0;
    while (i <= size_square)
    {
        j = 0;
        while (j <= size_square)
        {
            my_mlx_pixel_put(datas->img, *(datas->x)+i, *(datas->y)+j, *(datas->color));
            j++;
        }
        
        i++;
    }
    



    /*
    int i;
    int j;
    
    i = *(datas->x);

    while (i <= i + size_square)
    {
        j = *(datas->y);
        while (j <= j + size_square)
        {
            if (i >= *(datas->x) && i <= *(datas->x) + size_square)
            {
                my_mlx_pixel_put(datas->img, i, j, create_trgb(0,0,255,255));
            }
            j++;
        }
        i++;
    }
    */
}

int main_loop(t_datas *datas)
{
    datas->img->img = mlx_new_image(datas->vars->mlx, 1920, 1080);
    datas->img->first_pix = mlx_get_data_addr(datas->img->img, 
                                        &datas->img->bits_per_pixel, 
                                        &datas->img->line_length,
                                        &datas->img->endian);
	//my_mlx_pixel_put(datas->img, *(datas->x), *(datas->y), *(datas->color));

    fx_display_square(50, datas);

	mlx_put_image_to_window((datas->vars)->mlx, (datas->vars)->win, (datas->img)->img, 0, 0);
    return (0);
}



