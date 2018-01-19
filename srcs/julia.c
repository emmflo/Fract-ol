#include "fractal.h"
#include <complex.h>

int	julia(t_rect_int win, t_point_int pt, t_frac_params *params)
{
	t_point	v;
	int	i;
	double	xtemp;

	i = 0;
	v.x = pt.x * params->zoom.x + params->offset.x;
	v.y = pt.y * params->zoom.y + params->offset.y;
	v.x = ((((double)(v.x - win.x) * 3.5) / (double)win.w) - 2.5);
	v.y = ((((double)(v.y - win.y) * 2.0) / (double)win.h) - 1.0);
	while (v.x*v.x + v.y*v.y < 4 && i < params->max)
	{
		xtemp = v.x*v.x - v.y*v.y;
		v.y = 2*v.x*v.y + params->c.y;
		v.x = xtemp + params->c.x;
		i++;
	}
	return (i);
}

t_point	complex_power(t_point nb, int power)
{
	t_point	result;
	t_point	tmp;
	double	tmp2;
	int	i;

	if (power < 0)
	{
		result = complex_power(nb, -power);
		tmp2 = (result.x*result.x - result.y * result.y);
		nb.x = result.x / tmp2;
		nb.y = -result.y / tmp2;
		return (nb);
	}
	i = 0;
	result.x = 1;
	result.y = 1;
	while (power >= 2)
	{
		result.x = nb.x*nb.x - nb.y*nb.y;
		result.y = 2*nb.x*nb.y;
		if (power % 2 == 0)
			nb = result;
		else
		{
			tmp.x = nb.x*result.x - nb.y*result.y;
			tmp.y = nb.x*result.y + nb.y*result.x;
			nb = tmp;
		}
		power /= 2;
	}
	return (nb);
}

int	mandelbroth(t_rect_int win, t_point_int pt, t_frac_params *params)
{
	t_point	v;
	t_point	v_copy;
	int	i;
	double	xtemp;

	i = 0;
	v.x = pt.x * params->zoom.x + params->offset.x;
	v.y = pt.y * params->zoom.y + params->offset.y;
	v.x = ((((double)(v.x - win.x) * 3.5) / (double)win.w) - 2.5);
	v.y = ((((double)(v.y - win.y) * 2.0) / (double)win.h) - 1.0);
	v_copy = v;
	while (v.x*v.x + v.y*v.y < 4 && i < params->max)
	{
		xtemp = v.x*v.x - v.y*v.y;
		v.y = 2*v.x*v.y + v_copy.y;
		v.x = xtemp + v_copy.x;
		i++;
	}
	return (i);
}

int	mandelbroth3(t_rect_int win, t_point_int pt, t_frac_params *params)
{
	t_point	v;
	t_point	v_copy;
	int	i;
	double	xtemp;

	i = 0;
	v.x = pt.x * params->zoom.x + params->offset.x;
	v.y = pt.y * params->zoom.y + params->offset.y;
	v.x = ((((double)(v.x - win.x) * 3.5) / (double)win.w) - 2.5);
	v.y = ((((double)(v.y - win.y) * 2.0) / (double)win.h) - 1.0);
	v_copy = v;
	while (v.x*v.x + v.y*v.y < 4 && i < params->max)
	{
		xtemp = v.x*v.x*v.x - 3*v.x*v.y*v.y + 3*params->c.x*v.x - 3*params->c.y*v.y + v_copy.x;
		v.y = 3*v.x*v.x*v.y - v.y*v.y*v.y + 3*params->c.y*v.x + 3*params->c.x*v.y + v_copy.y;
		v.x = xtemp;
		i++;
	}
	return (i);
}

int	mandelbroth_power(t_rect_int win, t_point_int pt, t_frac_params *params)
{
	t_point	v;
	t_point	v_copy;
	int	i;
	double	xtemp;

	i = 0;
	v.x = pt.x * params->zoom.x + params->offset.x;
	v.y = pt.y * params->zoom.y + params->offset.y;
	v.x = ((((double)(v.x - win.x) * 3.5) / (double)win.w) - 2.5);
	v.y = ((((double)(v.y - win.y) * 2.0) / (double)win.h) - 1.0);
	v_copy = v;
	while (v.x*v.x + v.y*v.y < 4 && i < params->max)
	{
		v = complex_power(v, params->power);
		v.x += v_copy.x;
		v.y += v_copy.y;
		i++;
	}
	return (i);
}

int	fract2(t_rect_int win, t_point_int pt, t_frac_params *params)
{
	t_point	v;
	t_point	tmp;
	int	i;

	i = 0;
	v.x = pt.x * params->zoom.x + params->offset.x;
	v.y = pt.y * params->zoom.y + params->offset.y;
	v.x = ((((double)(v.x - win.x) * 3.5) / (double)win.w) - 2.5);
	v.y = ((((double)(v.y - win.y) * 2.0) / (double)win.h) - 1.0);
	while (v.x*v.x + v.y*v.y < 4 && i < params->max)
	{
		tmp.x = v.x;
		tmp.y = v.y;
		v.x = (2*(-(tmp.x*tmp.x*tmp.x) + 3*tmp.x*tmp.y*tmp.y + 6))
			/(3*(-(tmp.x*tmp.x) + 2*tmp.x + tmp.y*tmp.y)*(-(tmp.x*tmp.x) + 2*tmp.x + tmp.y*tmp.y));
		v.y = (2*(-3*(tmp.x*tmp.x*tmp.y) + tmp.y*tmp.y*tmp.y))
			/(3*(-2*(tmp.x*tmp.y) + 2*tmp.y)*(-2*(tmp.x*tmp.y) + 2*tmp.y));
		v.x += params->c.x;
		v.y += params->c.y;
		i++;
	}
	return (i);
}

int	fract(t_rect_int win, t_point_int pt, t_frac_params *params)
{
	double complex	z;
	double complex	c;
	t_point	v;
	t_point	tmp;
	int	i;

	i = 0;
	v.x = pt.x * params->zoom.x + params->offset.x;
	v.y = pt.y * params->zoom.y + params->offset.y;
	v.x = ((((double)(v.x - win.x) * 3.5) / (double)win.w) - 2.5);
	v.y = ((((double)(v.y - win.y) * 2.0) / (double)win.h) - 1.0);
	z = v.x + v.y * I;
	c = params->c.x + params->c.y * I;
	while (cabs(z) < 2 && i < params->max)
	{
		z = ((1 - cpow(z, 3) / 6)/cpow((z - cpow(z, 2) / 2), 2)) + c;
		i++;
	}
	return (i);
}
