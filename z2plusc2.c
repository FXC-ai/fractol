/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:51:24 by fcoindre          #+#    #+#             */
/*   Updated: 2023/02/24 14:46:16 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int z2plusc2(t_im_num c, int max_iterations)
{

    t_im_num    z_ini;
    t_im_num    z_cur;

    int         nb_iter;

    z_ini.im = 0;
    z_ini.re = 0;

    z_cur.im = 0;
    z_cur.re = 0;


    nb_iter = 0;

    c.re = c.re * c.re - c.im * c.im;
    c.im = 2 * c.re * c.im;

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