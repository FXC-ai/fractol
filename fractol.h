#ifndef FRACTOL_H
# define FRACTOL_H

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

    int     *color;
    int     *x;
    int     *y;

}   t_datas;

int close_window (t_datas *datas);
int	create_trgb(int t, int r, int g, int b);
int main_loop(t_datas *datas);
int fx_kboard_hook(int key_code, t_datas *datas);
int close_window (t_datas *datas);
void initialise_datas(t_datas *datas, t_vars *vars, t_img *img);

#endif