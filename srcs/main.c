#include <libft.h>
#include <imgui.h>
#include <mlx.h>
#include "env.h"
#include "mouse.h"
#include "keyboard.h"
#include "fractal.h"
#include "zoom.h"
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void		update_keys(t_env *env)
{
	t_point	center;

	if (env->keys.act[quit])
		exit(0);
	if (env->keys.act[up])
		env->params->offset.y -= env->params->zoom.x * 10;
	else if (env->keys.act[down])
		env->params->offset.y += env->params->zoom.y * 10;
	if (env->keys.act[left])
		env->params->offset.x -= env->params->zoom.x * 10;
	else if (env->keys.act[right])
		env->params->offset.x += env->params->zoom.y * 10;
	if (env->keys.act[zoom])
	{
		center.x = env->win->size_x/2;
		center.y = env->win->size_y/2;
		zoom_centered(env, center, 0.98);
		printf("zoom %f %f\n", env->params->zoom.x, env->params->zoom.y);
	}
	else if (env->keys.act[dezoom])
	{
		center.x = env->win->size_x/2;
		center.y = env->win->size_y/2;
		zoom_centered(env, center, 1.02);
		printf("zoom %f %f\n", env->params->zoom.x, env->params->zoom.y);
	}
	if (!env->keys.last_act[menu] && env->keys.act[menu])
		env->menu = !env->menu;
	if (!env->keys.last_act[c_update] && env->keys.act[c_update])
		env->c_update = !env->c_update;
	key_last_act_update(env);
}

typedef struct	s_args
{
	t_env		*env;
	t_rect_int	rect;
	int		(*fractal)(t_rect_int, t_point_int, t_frac_params*);
}		t_args;

void		*exec_fractal(void *args)
{
	t_args	*a;

	a = (t_args*)args;
	calculate_fractal(a->env, a->rect, a->fractal);
	return (NULL);
}

void	update_menu(t_env *env)
{
	static int	tmp = 6;
	char		str[16];

	if (env->menu)
	{
		g_rect_fill(env->win->img_next, make_rect(0, 0, 240, env->win->size_y), 0x333333);
		if(button(env->win, env->ui, 1, make_rect(20, 20, 64, 32), "Quit"))
			exit(0);
		if(button(env->win, env->ui, 2, make_rect(20, 150, 64, 32), "Julia"))
			env->fractal = &julia;
		if(button(env->win, env->ui, 3, make_rect(100, 150, 64, 32), "Mandelbroth"))
			env->fractal = &mandelbroth;
		if(button(env->win, env->ui, 4, make_rect(20, 200, 64, 32), "Mandelbroth3"))
			env->fractal = &mandelbroth3;
		if(button(env->win, env->ui, 5, make_rect(100, 200, 64, 32), "MandelbrothP"))
			env->fractal = &mandelbroth_power;
		if(button(env->win, env->ui, 8, make_rect(20, 250, 64, 32), "ResetZoom"))
		{
			env->params->zoom.x = 1;
			env->params->zoom.y = 1;
		}
		if(button(env->win, env->ui, 9, make_rect(100, 250, 64, 32), "ResetPos"))
		{
			env->params->offset.x = 0;
			env->params->offset.y = 0;
		}
		if (slider(env->win, env->ui, 7, make_rect(20, 100, 200, 32), 1000, &(env->params->max)))
			printf("NB4 %d\n", env->params->max);
		if (slider(env->win, env->ui, 6, make_rect(20, 300, 200, 32), 12, &(tmp)))
			env->params->power = tmp - 4;
		snprintf(str, sizeof(str), "%d", env->params->power);
		g_add_to_text_buffer(env->win, g_make_text(20, 400, 0xFFFFFF, str));
	}
}

int		update(t_env *env)
{
	int		i;
	t_point_int	size;
	pthread_t	threads[24];
	t_args		*args;

	if (!(args = (t_args*)malloc(sizeof(t_args) * 24)))
		return (1);
	size.x = env->win->size_x / 6;
	size.y = env->win->size_y / 4;
	update_keys(env);
	if (env->drag && env->ui->mousedown)
	{
		env->params->offset.x = env->offset_start.x + (env->drag_start.x - env->ui->mousex) * env->params->zoom.x;
		env->params->offset.y = env->offset_start.y + (env->drag_start.y - env->ui->mousey) * env->params->zoom.y;
	}
	i = 0;
	while (i < 24)
	{
		args[i].rect.x = i%6 * size.x;
		args[i].rect.y = i/6 * size.y;
		args[i].rect.w = size.x;
		args[i].rect.h = size.y;
		args[i].env = env;
		args[i].fractal = env->fractal;
		pthread_create(&threads[i], NULL, &exec_fractal, &args[i]);
		//calculate_fractal(env->win, rect, env->params, &julia);
		i++;
	}
	i = 0;
	while (i < 24)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	update_menu(env);
	g_update(env->win);
	g_render_delete_text_buffer(env->win);
	return (0);
}

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
	key_set_default(&(env->keys));
	env->menu = 0;
	env->c_update = 1;
	pthread_mutex_init(&(env->mutex_pixel), NULL);
	env->fractal = &julia;
	return (env);
}

int		init_win(t_env *env)
{
	void		*mlx_ptr;

	if (!(mlx_ptr = mlx_init()))
		return (0);
	if (!(env->win = g_new_window(mlx_ptr, 1000, 1000, "Fractol")))
		return (0);
	return (1);
}

int		main(int argc, char *argv[])
{
	t_env		*env;

	if (!(env = set_env()))
		return (1);
	if (!init_win(env))
		return (2);
	if (!(env->ui = make_ui()))
		return (4);
	mlx_hook(env->win->win_ptr, MotionNotify, PointerMotionMask, &(mouse_move), env);
	mlx_hook(env->win->win_ptr, ButtonPress, ButtonPressMask, &(mouse_press_button), env);
	mlx_hook(env->win->win_ptr, ButtonRelease, ButtonReleaseMask, &(mouse_release_button), env);
	mlx_hook(env->win->win_ptr, KeyPress, KeyPressMask, &(key_press), env);
	mlx_hook(env->win->win_ptr, KeyRelease, KeyReleaseMask, &(key_release),	env);
	//mlx_hook(env->win->win_ptr, DestroyNotify, StructureNotifyMask, &(destroy), env);
	mlx_loop_hook(env->win->mlx_ptr, &update, env);
	mlx_loop(env->win->mlx_ptr);
	return (0);
}
