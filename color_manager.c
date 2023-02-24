/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:14:12 by fcoindre          #+#    #+#             */
/*   Updated: 2023/02/24 18:14:30 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	calculate_color(double coef, double seed)
{
	int	r;
	int	g;
	int	b;

	r = seed * 255;
	g = coef * 255;
	b = (1 - coef) * 255;
	return (create_trgb(0, r, g, b));
}

int	convert_to_color(int nb_iterations, int max_iterations)
{
	double	coef;
	int		color;

	if (nb_iterations == -2)
		return (create_trgb(0, 0, 0, 0));
	coef = log((double)nb_iterations) / log((double)max_iterations);
	if (nb_iterations == max_iterations)
		return (create_trgb(0, 0, 0, 0));
	if (nb_iterations >= 0 && nb_iterations < 4)
		return (create_trgb(0, 0, 120, 140));
	else if (nb_iterations % 4 == 1)
		color = calculate_color(coef, 0.1);
	else if (nb_iterations % 4 == 2)
		color = calculate_color(coef, 0.3);
	else if (nb_iterations % 4 == 3)
		color = calculate_color(coef, 0.6);
	else
		color = calculate_color(coef, 0.9);
	return (color);
}
