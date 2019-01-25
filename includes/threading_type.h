#ifndef THREADING_TYPE_H
# define THREADING_TYPE_H
# include "graphics.h"
# include "fractal_type.h"

typedef struct	s_args
{
	t_img		*img;
	struct s_env	*env;
	t_rect_int	rect;
	int		(*fractal)(t_rect_int, t_point_int, t_frac_params*);
	int		done;
	t_frac_params	*params;
}		t_args;

#endif
