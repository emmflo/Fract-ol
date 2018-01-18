#include "fractal.h"
#include <graphics.h>

#include <stdio.h>

#include <pthread.h>
#include <errno.h>

colors[16] = {0x0,0x102B53,0x7E2553,0x008751, 0xAB5236, 0x5F574F, 0xC2C3C7, 0xFFF1E8,
	0xFF004D, 0xFFA300, 0xFFEC27, 0x00E436, 0x29ADFF, 0x83769C, 0xFF77A8, 0xFFCCAA};

void	calculate_fractal(t_env *env, t_rect_int rect,
		int fractal(t_rect_int, t_point_int, t_frac_params*))
{
	int		tmp;
	int		color;
	t_point_int	pt;
	t_rect_int	win_rect;

	pt.x = rect.x;
	win_rect.x = 0;
	win_rect.y = 0;
	win_rect.w = env->win->size_x;
	win_rect.h = env->win->size_y;
	while (pt.x < rect.w + rect.x)
	{
		pt.y = rect.y;
		while (pt.y < rect.h + rect.y)
		{
			tmp = fractal(win_rect, pt, env->params);
			color = colors[tmp % 16];
			//pthread_mutex_lock(&(env->mutex_pixel));
			g_put_pixel(env->win->img_next, pt, color);
			//pthread_mutex_unlock(&(env->mutex_pixel));
			pt.y++;
		}
		pt.x++;
	}
}
