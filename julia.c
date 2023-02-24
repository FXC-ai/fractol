/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:48:55 by fcoindre          #+#    #+#             */
/*   Updated: 2023/02/22 15:49:15 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int calcute_iterations (t_im_num z_ini, t_im_num c, int max_iterations, t_im_num (fractal)(t_im_num, t_im_num))
{
    int count;
    t_im_num z_cur;
    
    count = 0;
    while (count < max_iterations)
    {
        z_cur = fractal(z_ini, c);
        z_ini.re = z_cur.re;
        z_ini.im = z_cur.im;
        count++;
        
        if (z_cur.re * z_cur.re + z_cur.im * z_cur.im > 4)
        {
            break;
        }
    }
    return count;

}


t_im_num z2_plus_c(t_im_num z_ini, t_im_num c)
{
        t_im_num z_cur;
    
        z_cur.re = (z_ini.re * z_ini.re) - (z_ini.im * z_ini.im) + c.re;
        z_cur.im = (2 * z_ini.im * z_ini.re) + c.im;

        return z_cur;
}