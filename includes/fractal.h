#ifndef FRACTAL_H
# define FRACTAL_H
# include "graphics.h"
# include "fractal_type.h"
# include "env.h"
# define NB_FRACT 7

void	calculate_fractal(t_img *img, t_frac_params *params, t_rect_int rect,
		t_frac_return fractal(t_rect_int, t_point_int, t_frac_params*));
t_frac_return	julia(t_rect_int win, t_point_int pt, t_frac_params *params);
t_frac_return	mandelbroth(t_rect_int win, t_point_int pt, t_frac_params *params);
t_frac_return	mandelbroth3(t_rect_int win, t_point_int pt, t_frac_params *params);
t_frac_return	multibroth(t_rect_int win, t_point_int pt, t_frac_params *params);
t_frac_return	multijulia(t_rect_int win, t_point_int pt, t_frac_params *params);
t_frac_return	newton(t_rect_int win, t_point_int pt, t_frac_params *params);
t_frac_return	burning_ship(t_rect_int win, t_point_int pt, t_frac_params *params);
extern void	*fracts[NB_FRACT]; 
extern char	fract_names[NB_FRACT][16];

#endif
