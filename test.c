#include "fractol.h"
#include "libft/libft.h"
#include "mlx.h"
#define ON_DESTROY 17

#define WIDTH 1920
#define HEIGH 1080

// Pour compiler : gcc test.c -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework Appkit -o test

int main()
{
    void	*mlx;
	void	*img;
    void    *win;
    void    *first_pix;



	char	*relative_path = "./test.xpm";
	int		img_width;
	int		img_height;

    int     line_lenght;
    int     bbp;
    int     endian;


	mlx = mlx_init();
    win = mlx_new_window(mlx, WIDTH, HEIGH, "TEST");
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);

    first_pix = mlx_get_data_addr(img, &bbp, &line_lenght, &endian);


    mlx_put_image_to_window(mlx, win, img, 0, 0);
    mlx_loop(mlx);

    return (0);
}