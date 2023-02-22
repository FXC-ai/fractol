#ifndef FRACTOL_H
# define FRACTOL_H

#include "libft/libft.h"
#include "mlx/mlx.h"
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

typedef struct s_im_num
{

    double  re;
    double  im;

}   t_im_num;

typedef struct s_datas
{
    t_vars  *vars;
    t_img   *img;

    int     ini_color;
    double     ini_x;
    double     ini_y;
    double  zoom;

    t_im_num c;   


}   t_datas;

int mandelbrot(t_im_num c, int max_iterations);
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
int calcute_iterations (t_im_num z_ini, t_im_num c, int max_iterations, t_im_num (fractal)(t_im_num, t_im_num));
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);


#endif