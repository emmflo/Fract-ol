#ifndef FRACTAL_TYPE_H
# define FRACTAL_TYPE_H

typedef struct		s_frac_params
{
	int	max;
	t_point	offset;
	t_point	c;
	int	power;
	t_point	zoom;
	t_rect_int	win_rect;
}			t_frac_params;

#endif
