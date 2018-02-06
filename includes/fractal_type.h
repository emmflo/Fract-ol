#ifndef FRACTAL_TYPE_H
# define FRACTAL_TYPE_H

typedef enum	e_coloring_type {PICO8, RAINBOW} t_coloring_type;

typedef struct		s_frac_params
{
	int		max;
	t_point		offset;
	t_point		c;
	int		power;
	t_point		zoom;
	t_rect_int	win_rect;
	t_coloring_type	coloring_type;
	double		color_angle;
	int		color_shift;
}			t_frac_params;

typedef struct		s_frac_return
{
	int	index;
	double	continuous_index;
}			t_frac_return;

#endif
