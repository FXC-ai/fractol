#include "fractol.h"
#include "libft/libft.h"
#include "mlx.h"
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

    int     color;
    int     x;
    int     y;

}   t_datas;

int close_window (t_datas *datas);
int	create_trgb(int t, int r, int g, int b);
int main_loop(t_datas *datas);
int fx_kboard_hook(int key_code, t_datas *datas);
int close_window (t_datas *datas);
void initialise_datas(t_datas *datas, t_vars *vars, t_img *img);

#define WIDTH 1920
#define HEIGH 1080



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

    datas->color = create_trgb(0,255,0,0);

    datas->x = 0;
    datas->y = 0;


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
        datas->color = create_trgb(0,0,255,255);
        datas->y += 50;
    }
    else if (key_code == 126)
    {
        datas->color = create_trgb(0,255,0,0);
        datas->y -= 50;
    }
    else if (key_code == 124)
    {
        datas->color = create_trgb(0,0,0,255);
        datas->x += 50;
    }
    else if (key_code == 123)
    {
        datas->color = create_trgb(0,0,255,0);
        datas->x -= 50;
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
            my_mlx_pixel_put(datas->img, datas->x+i, datas->y+j, datas->color);
            j++;
        }
        
        i++;
    }
    
}

int main_loop(t_datas *datas)
{
    datas->img->img = mlx_new_image(datas->vars->mlx, WIDTH, HEIGH);
    datas->img->first_pix = mlx_get_data_addr(datas->img->img, 
                                        &datas->img->bits_per_pixel, 
                                        &datas->img->line_length,
                                        &datas->img->endian);
    


    fx_display_square(50, datas);

	mlx_put_image_to_window((datas->vars)->mlx, (datas->vars)->win, (datas->img)->img, 0, 0);
    return (0);
}



