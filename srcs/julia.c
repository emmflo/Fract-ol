#include "fractal.h"
#include <complex.h>

t_frac_return	julia(t_rect_int win, t_point_int pt, t_frac_params *params)
{
	t_frac_return	ret;
	t_point	v;
	int	i;
	double	xtemp;

	i = 0;
	v.x = pt.x * params->zoom.x + params->offset.x;
	v.y = pt.y * params->zoom.y + params->offset.y;
	v.x = ((((double)(v.x - win.x) * 3.5) / (double)win.w) - 1.75);
	v.y = ((((double)(v.y - win.y) * 2.0) / (double)win.h) - 1.0);
	while (v.x*v.x + v.y*v.y < 4 && i < params->max)
	{
		xtemp = v.x*v.x - v.y*v.y;
		v.y = 2*v.x*v.y + params->c.y;
		v.x = xtemp + params->c.x;
		i++;
	}
	ret.index = i;
	ret.continuous_index = i + 1 - ((log(2) / (sqrt(v.x*v.x + v.y*v.y))) / log(2));
	return (ret);
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
		tmp2 = (result.x*result.x + result.y*result.y);
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

t_frac_return	mandelbroth(t_rect_int win, t_point_int pt, t_frac_params *params)
{
	t_frac_return	ret;
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
	ret.index = i;
	ret.continuous_index = i + 1 - ((log(2) / (sqrt(v.x*v.x + v.y*v.y))) / log(2));
	return (ret);
}

t_frac_return	mandelbroth3(t_rect_int win, t_point_int pt, t_frac_params *params)
{
	t_frac_return	ret;
	t_point	v;
	t_point	v_copy;
	int	i;
	double	xtemp;

	i = 0;
	v.x = pt.x * params->zoom.x + params->offset.x;
	v.y = pt.y * params->zoom.y + params->offset.y;
	v.x = ((((double)(v.x - win.x) * 3.5) / (double)win.w) - 1.75);
	v.y = ((((double)(v.y - win.y) * 2.0) / (double)win.h) - 1.0);
	v_copy = v;
	while (v.x*v.x + v.y*v.y < 4 && i < params->max)
	{
		xtemp = v.x*v.x*v.x - 3*v.x*v.y*v.y + 3*params->c.x*v.x - 3*params->c.y*v.y + v_copy.x;
		v.y = 3*v.x*v.x*v.y - v.y*v.y*v.y + 3*params->c.y*v.x + 3*params->c.x*v.y + v_copy.y;
		v.x = xtemp;
		i++;
	}
	ret.index = i;
	ret.continuous_index = i + 1 - ((log(2) / (sqrt(v.x*v.x + v.y*v.y))) / log(2));
	return (ret);
}

t_frac_return	multibroth(t_rect_int win, t_point_int pt, t_frac_params *params)
{
	t_frac_return	ret;
	t_point	v;
	t_point	v_copy;
	int	i;
	double	xtemp;

	i = 0;
	v.x = pt.x * params->zoom.x + params->offset.x;
	v.y = pt.y * params->zoom.y + params->offset.y;
	v.x = ((((double)(v.x - win.x) * 3.5) / (double)win.w) - 1.75);
	v.y = ((((double)(v.y - win.y) * 2.0) / (double)win.h) - 1.0);
	v_copy = v;
	while (v.x*v.x + v.y*v.y < 4 && i < params->max)
	{
		v = complex_power(v, params->power);
		v.x += v_copy.x;
		v.y += v_copy.y;
		i++;
	}
	ret.index = i;
	ret.continuous_index = i + 1 - ((log(2) / (sqrt(v.x*v.x + v.y*v.y))) / log(2));
	return (ret);
}

t_frac_return	multijulia(t_rect_int win, t_point_int pt, t_frac_params *params)
{
	t_frac_return	ret;
	t_point	v;
	t_point	v_copy;
	int	i;
	double	xtemp;

	i = 0;
	v.x = pt.x * params->zoom.x + params->offset.x;
	v.y = pt.y * params->zoom.y + params->offset.y;
	v.x = ((((double)(v.x - win.x) * 3.5) / (double)win.w) - 1.75);
	v.y = ((((double)(v.y - win.y) * 2.0) / (double)win.h) - 1.0);
	v_copy = v;
	while (v.x*v.x + v.y*v.y < 4 && i < params->max)
	{
		v = complex_power(v, params->power);
		v.x += params->c.x;
		v.y += params->c.y;
		i++;
	}
	ret.index = i;
	ret.continuous_index = i + 1 - ((log(2) / (sqrt(v.x*v.x + v.y*v.y))) / log(2));
	return (ret);
}

int	newton_old(t_rect_int win, t_point_int pt, t_frac_params *params)
{
	t_point	v;
	t_point z_squared;
	t_point	num;
	t_point dem;
	double	tmp;
	int	i;

	i = 0;
	v.x = pt.x * params->zoom.x + params->offset.x;
	v.y = pt.y * params->zoom.y + params->offset.y;
	v.x = ((((double)(v.x - win.x) * 3.5) / (double)win.w) - 1.75);
	v.y = ((((double)(v.y - win.y) * 2.0) / (double)win.h) - 1.0);
	while (v.x*v.x + v.y*v.y > 0.000001 && i < params->max)
	{
		z_squared.x = v.x*v.x - v.y*v.y;
		z_squared.y = 2*v.x*v.y;
		num.x = v.x * z_squared.x - v.y * z_squared.y - 1;
		num.y = v.x * z_squared.y + v.y * z_squared.x;
		dem.x = 3 * z_squared.x * z_squared.x - 3 * z_squared.y * z_squared.y;
		dem.y = 6 * z_squared.x * z_squared.y;
		tmp = (dem.x * dem.x + dem.y * dem.y);
		v.x -= (num.x * dem.x) / tmp + (num.y * dem.y) / tmp;
		v.y -= (num.y * dem.x) / tmp - (num.x * dem.y) / tmp;
		i++;
	}
	return (i);
}

t_frac_return	newton(t_rect_int win, t_point_int pt, t_frac_params *params)
{
	t_frac_return	ret;
	int	i;
	t_point v;
	t_point	old;
	double	tmp;

	i = 0;
	tmp = 1.0;
	v.x = pt.x * params->zoom.x + params->offset.x;
	v.y = pt.y * params->zoom.y + params->offset.y;
	v.x = ((((double)(v.x - win.x) * 3.5) / (double)win.w) - 1.75);
	v.y = ((((double)(v.y - win.y) * 2.0) / (double)win.h) - 1.0);
	while (tmp > 0.000001 && i < params->max)
	{
		old.x = v.x;
		old.y = v.y;
		tmp = (v.x * v.x + v.y * v.y) * (v.x * v.x + v.y * v.y);
		v.x = (2 * v.x * tmp + v.x * v.x - v.y * v.y) / (3.0 * tmp);
		v.y = (2 * v.y * (tmp - old.x)) / (3.0 * tmp);
		tmp = (v.x - old.x) * (v.x - old.x) + (v.y - old.y) * (v.y - old.y);
		i++;
	}
	ret.index = i;
	ret.continuous_index = i + 1 - ((log(2) / (sqrt(v.x*v.x + v.y*v.y))) / log(2));
	return (ret);
}

t_frac_return	burning_ship(t_rect_int win, t_point_int pt, t_frac_params *params)
{
	t_frac_return	ret;
	int	i;
	t_point v;
	t_point	old;
	double	tmp;

	i = 0;
	v.x = pt.x * params->zoom.x + params->offset.x;
	v.y = pt.y * params->zoom.y + params->offset.y;
	v.x = ((((double)(v.x - win.x) * 3.5) / (double)win.w) - 1.75);
	v.y = ((((double)(v.y - win.y) * 2.0) / (double)win.h) - 1.0);
	while (v.x*v.x + v.y*v.y < 4 && i < params->max)
	{
		tmp = v.y;
		v.y = fabs((double) (v.x * v.y + v.x * v.y + params->c.y));
		v.x = fabs((double) (v.x * v.x - tmp * tmp + params->c.x));
		i++;
	}
	ret.index = i;
	ret.continuous_index = i + 1 - ((log(2) / (sqrt(v.x*v.x + v.y*v.y))) / log(2));
	return (ret);
}
