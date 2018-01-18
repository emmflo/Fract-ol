#include "fractal.h"
#include <graphics.h>

#include <stdio.h>

#include <pthread.h>
#include <errno.h>

colors[16] = {0x0,0x102B53,0x7E2553,0x008751, 0xAB5236, 0x5F574F, 0xC2C3C7, 0xFFF1E8,
	0xFF004D, 0xFFA300, 0xFFEC27, 0x00E436, 0x29ADFF, 0x83769C, 0xFF77A8, 0xFFCCAA};

void	calculate_fractal(t_img *img, t_frac_params *params, t_rect_int rect,
		int fractal(t_rect_int, t_point_int, t_frac_params*))
{
	int		tmp;
	int		color;
	t_point_int	pt;
	t_rect_int	win_rect;

	pt.x = rect.x;
	while (pt.x < rect.w + rect.x)
	{
		pt.y = rect.y;
		while (pt.y < rect.h + rect.y)
		{
			tmp = fractal(params->win_rect, pt, params);
			color = colors[tmp % 16];
			//pthread_mutex_lock(&(env->mutex_pixel));
			//g_put_pixel(env->win->img_next, pt, color);
			g_put_pixel(img, pt, color);
			//pthread_mutex_unlock(&(env->mutex_pixel));
			pt.y++;
		}
		pt.x++;
	}
}
