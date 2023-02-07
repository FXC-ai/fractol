#include "libft/libft.h"
#include "stdio.h"
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

int main()
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;

    //initialize the connection between the software ans the display
    mlx = mlx_init();

    //creates a new window, using the size_x and size_y parameters. The mlx_ptr parameter
    // is the connection identifier returned by mlx_init. It returns a void * window 
    // identifier that can be used by other MiniLibX calls.
    mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_LNGTH, "Hello world!");

    // mlx_new_image creates a new image in memory. 
    // It returns a void * identifier needed to manipulate this image later.
    img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_LNGTH); //(pointer, x, y)

    //Returns ...
    //The img_ptr parameter specifies the image  to  use.
    //bits_per_pixel will be filled with the number of bits needed to represent a pixel color
    //size_line is the number of bytes used to store one line of  the  image  in  memory
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    double i, j;
    
    i = 0;
    j = 0;
    while (i <= 50)
    {
        j = 0;
        while (j <= 50)
        {
            if (i == 0 || i == 50 || j == 0 || j == 50)
            {
                fx_mlx_pixel_put(&img, i, j, 0x00FF0000);
            }
            j++;
        }  
        i++;
    }

    i = 0;
    j = 0;
    while (i <= 50)
    {
        j = 0;
        while (j <= 50)
        {
            if (((i - 25) * (i - 25) + (j - 25) * (j -25)) == 625)
            {
                fx_mlx_pixel_put(&img, i, j, 0x00FF0000);
            }
            j++;
        }  
        i++;
    }    

    

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    fx_display_t_data(img);

    
    mlx_loop(mlx);

    return (0);

}