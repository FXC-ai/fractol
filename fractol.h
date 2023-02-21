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


typedef struct s_datas
{
    t_vars  *vars;
    t_img   *img;

    int     ini_color;
    double     ini_x;
    double     ini_y;
    double  zoom;

}   t_datas;

typedef struct s_im_num
{

    double  re;
    double  im;

}   t_im_num;

#endif