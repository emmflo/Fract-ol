#ifndef FRACTAL_H
# define FRACTAL_H
# include "graphics.h"
# include "fractal_type.h"
# include "env.h"

void	calculate_fractal(t_img *img, t_frac_params *params, t_rect_int rect,
		int fractal(t_rect_int, t_point_int, t_frac_params*));
int	julia(t_rect_int win, t_point_int pt, t_frac_params *params);
int	mandelbroth(t_rect_int win, t_point_int pt, t_frac_params *params);
int	mandelbroth3(t_rect_int win, t_point_int pt, t_frac_params *params);
int	mandelbroth_power(t_rect_int win, t_point_int pt, t_frac_params *params);
int	fract(t_rect_int win, t_point_int pt, t_frac_params *params);

#endif
