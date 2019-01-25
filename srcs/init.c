#include "env.h"
#include "imgui.h"
#include "fractal.h"
#include "graphics.h"
#include "keyboard.h"

t_env	*set_env()
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	if (!(env->params = (t_frac_params*)malloc(sizeof(t_frac_params))))
		return (NULL);
	env->params->c.x = -1.7;
	env->params->c.y = 0;
	env->params->offset.x = 0;
	env->params->offset.y = 0;
	env->params->zoom.x = 1;
	env->params->zoom.y = 1;
	env->params->max = 100;
	env->params->power = 2;
	env->params->coloring_type = PICO8;
	env->params->color_angle = 0;
	env->params->color_shift = 0;

	key_set_default(&(env->keys));
	env->menu = 0;
	env->c_update = 1;
	if (!(env->args = (t_args*)malloc(sizeof(t_args) * 24)))
		return (NULL);
	env->next_frame = 1;
	return (env);
}

int		init_win(t_env *env)
{
	void		*mlx_ptr;
	t_rect_int	win_rect;
	int		i;

	if (!(mlx_ptr = mlx_init()))
		return (0);
	if (!(env->win = g_new_window(mlx_ptr, 1000, 1000, "Fractol")))
		return (0);
	win_rect.x = 0;
	win_rect.y = 0;
	win_rect.w = 1000;
	win_rect.h = 1000;
	env->params->win_rect = win_rect;
	env->img = g_new_img(env->win->mlx_ptr, env->win->size_x, env->win->size_y);
	env->full_fract = g_new_img(env->win->mlx_ptr, env->win->size_x, env->win->size_y);
	i=0;
	while (i < 24)
	{
		env->args[i].img = env->img;
		i++;
	}
	return (1);
}
