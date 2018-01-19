#ifndef ENV_H
# define ENV_H
# include "keyboard_type.h"
# include "imgui.h"
# include <pthread.h>
# include "threading_type.h"
# include "fractal_type.h"

typedef struct	s_env
{
	t_window	*win;
	t_keys		keys;
	t_ui_state	*ui;
	int		menu;
	int		c_update;
	t_frac_params	*params;
	pthread_mutex_t	mutex_pixel;
	int		(*fractal)(t_rect_int, t_point_int, t_frac_params*);
	t_point_int	drag_start;
	t_point		offset_start;
	int		drag;
	t_img		*img;
	t_img		*full_fract;
	struct s_args	*args;
	int		next_frame;
}				t_env;

#endif
