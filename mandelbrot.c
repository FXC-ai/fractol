/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:41:32 by fcoindre          #+#    #+#             */
/*   Updated: 2023/02/23 19:38:02 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int mandelbrot(t_im_num c, int max_iterations)
{

    t_im_num    z_ini;
    t_im_num    z_cur;
    int         nb_iter;

    z_ini.im = 0;
    z_ini.re = 0;

    z_cur.im = 0;
    z_cur.re = 0;


    nb_iter = 0;

    double p;
    p = sqrt((c.re - 0.25) * (c.re - 0.25) + c.im * c.im);

    if (c.re < (p - 2.0 * p * p + 0.25))        
        return (-2);

    if (((c.re + 1) * (c.re + 1) + c.im * c.im) < 0.0625)        
        return (-2);


    while (nb_iter < max_iterations)
    {
        
        z_ini.re = z_cur.re;
        z_ini.im = z_cur.im;
        
        z_cur.re = z_ini.re * z_ini.re - z_ini.im * z_ini.im + c.re;
        z_cur.im = 2 * z_ini.re * z_ini.im + c.im;
        


        if (z_cur.re * z_cur.re + z_cur.im * z_cur.im > 4)
        {
            break;
        }        

        nb_iter++;
    }
    
    return nb_iter;


}