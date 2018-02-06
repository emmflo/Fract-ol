#include "fractal.h"
#include <graphics.h>

#include <stdio.h>

#include <pthread.h>
#include <errno.h>
#include <math.h>

int 	colors[16] = {0x0,0x102B53,0x7E2553,0x008751, 0xAB5236, 0x5F574F, 0xC2C3C7, 0xFFF1E8,
	0xFF004D, 0xFFA300, 0xFFEC27, 0x00E436, 0x29ADFF, 0x83769C, 0xFF77A8, 0xFFCCAA};

void	*fracts[NB_FRACT] = 
{
	&julia,
	&mandelbroth,
	&mandelbroth3,
	&multibroth,
	&multijulia,
	&newton,
	&burning_ship
};

char	fract_names[NB_FRACT][16] =
{
	"julia",
	"mandelbroth",
	"mandelbroth3",
	"multibroth",
	"multijulia",
	"newton",
	"burning_ship"
};

int	rainbow_color(double freq, double angle)
{
	int	color;

	color = g_rgb_to_color(
			sin(angle + freq) * 230 + 25, 
			sin(angle + freq + 2*M_PI/3) * 230 + 25, 
			sin(angle + freq + 4*M_PI/3) * 230 + 25);
	return (color);
}

void	calculate_fractal(t_img *img, t_frac_params *params, t_rect_int rect,
		t_frac_return fractal(t_rect_int, t_point_int, t_frac_params*))
{
	int		tmp;
	int		color;
	t_point_int	pt;
	t_rect_int	win_rect;
	t_frac_return	ret;

	pt.x = rect.x;
	while (pt.x < rect.w + rect.x)
	{
		pt.y = rect.y;
		while (pt.y < rect.h + rect.y)
		{
			ret = fractal(params->win_rect, pt, params);
			if (params->coloring_type == PICO8)
			{
				color = colors[(ret.index + params->color_shift) % 16];
			}
			if (params->coloring_type == RAINBOW)
				color = rainbow_color(ret.continuous_index, params->color_angle);
			//pthread_mutex_lock(&(env->mutex_pixel));
			//g_put_pixel(env->win->img_next, pt, color);
			g_put_pixel(img, pt, color);
			//pthread_mutex_unlock(&(env->mutex_pixel));
			pt.y++;
		}
		pt.x++;
	}
}
