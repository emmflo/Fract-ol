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
	t_img		*img;
	t_env		*env;
	t_rect_int	rect;
	int		(*fractal)(t_rect_int, t_point_int, t_frac_params*);
	int		done;
	t_frac_params	*params;
}		t_args;

void		*exec_fractal(void *args)
{
	t_args	*a;

	a = (t_args*)args;
	calculate_fractal(a->img, a->params, a->rect, a->fractal);
	a->done = 1;
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

void		img_copy(t_img *dest, t_img *src)
{
	int	i;

	if (dest == NULL && src == NULL)
		return ;
	i = 0;
	//printf("dest->width %d, src->width %d\n", dest->width, src->width);
	//printf("dest->height %d, src->height %d\n", dest->height, src->height);
	//printf("dest->bits_per_pixel %d, src->bits_per_pixel %d\n", *dest->bits_per_pixel, src->bits_per_pixel);
	while (i < dest->width * dest->height * (*dest->bits_per_pixel / 8) &&
		i < src->width * src->height * (*src->bits_per_pixel / 8))
	{
		dest->data[i] = src->data[i];
		i++;
	}
}

int		update(t_env *env)
{
	int		i;
	int		j;
	t_point_int	size;
	pthread_t	threads[24];
	static t_args	*args = NULL;
	static int	next_frame = 1;
	static t_img	*img;
	static t_img	*full_fract;

	if (args == NULL)
	{
		if (!(args = (t_args*)malloc(sizeof(t_args) * 24)))
			return (1);
		i=0;
		img = g_new_img(env->win->mlx_ptr, env->win->size_x, env->win->size_y);
		full_fract = g_new_img(env->win->mlx_ptr, env->win->size_x, env->win->size_y);
		while (i < 24)
		{
			args[i].img = img;
			i++;
		}
	}
	size.x = env->win->size_x / 6;
	size.y = env->win->size_y / 4;
	update_keys(env);
	if (env->drag && env->ui->mousedown)
	{
		env->params->offset.x = env->offset_start.x + (env->drag_start.x - env->ui->mousex) * env->params->zoom.x;
		env->params->offset.y = env->offset_start.y + (env->drag_start.y - env->ui->mousey) * env->params->zoom.y;
	}
	if (next_frame) {
		printf("THREADING\n");
	i = 0;
	while (i < 24)
	{
		args[i].rect.x = i%6 * size.x;
		args[i].rect.y = i/6 * size.y;
		args[i].rect.w = size.x;
		args[i].rect.h = size.y;
		args[i].env = env;
		args[i].fractal = env->fractal;
		args[i].done = 0;
		if (!(args[i].params = (t_frac_params*)malloc(sizeof(t_frac_params))))
			return (NULL);
		ft_memcpy(args[i].params, env->params, sizeof(t_frac_params));
		pthread_create(&threads[i], NULL, &exec_fractal, &args[i]);
		//calculate_fractal(env->win, rect, env->params, &julia);
		i++;
	}
	next_frame = 0;
	}
	i = 0;
	j = 0;
	while (i < 24)
	{
		j += args[i].done;
		//printf("i%d j%d\n", i, j);
		//pthread_join(threads[i], NULL);
		i++;
	}
	if (j == 24)
	{
		printf("DONE\n");
		next_frame = 1;
		img_copy(full_fract, img);
	}
	img_copy(env->win->img_next, full_fract);
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
	t_rect_int	win_rect;

	if (!(mlx_ptr = mlx_init()))
		return (0);
	if (!(env->win = g_new_window(mlx_ptr, 1000, 1000, "Fractol")))
		return (0);
	win_rect.x = 0;
	win_rect.y = 0;
	win_rect.w = 1000;
	win_rect.h = 1000;
	env->params->win_rect = win_rect;
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
