#include "libft/libft.h"
#include <stdio.h>
#include "mlx.h"

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

typedef struct s_coord
{
    int x;
    int y;
}   t_coord;



int closed (t_vars vars);
int display_wait(t_vars vars);
int display_coord(int x, int y, t_vars vars);
int test (int x, int y, void *param);
int on_expose_test (void *param);


int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int fx_kboard_hook(int key_code, t_vars *vars)
{
    int x;
    int y;

    if (key_code == 53)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    if (key_code == 0)
    {
        printf("A appuye\n");
    }
    if (key_code == 12)
    {
        mlx_mouse_get_pos(vars->win , &x, &y);
        printf("x= %d et y= %d\n", x, y);
    }
    
    return (0);
}

int main()
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
    t_vars  vars;


	mlx = mlx_init();

	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");

    vars.mlx = mlx;
    vars.win = mlx_win;

	img.img = mlx_new_image(mlx, 1920, 1080);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    /*PRESS KEY*/
    mlx_key_hook(mlx_win, fx_kboard_hook, &vars);
    /*DESTROY*/
    mlx_hook(vars.win, 17, 0, closed, &vars);
    /*MOUSE MOVE*/
    mlx_hook(vars.win, 6, 0, test, &vars);
    /*ON EXPOSE*/
    mlx_hook(vars.win, 12, 0, on_expose_test, &vars);


	mlx_loop(mlx);

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



