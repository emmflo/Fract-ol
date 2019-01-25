#include "env.h"
#include <stdlib.h>
#include "fractal.h"
#include "ft_threading.h"

void		*exec_fractal(void *args)
{
	t_args	*a;

	a = (t_args*)args;
	calculate_fractal(a->img, a->params, a->rect, a->fractal);
	a->done = 1;
	return (NULL);
}

void		launch_threads(t_env *env)
{
	t_point_int	size;
	int	i;
	pthread_t	threads[24];

	size.x = env->win->size_x / 6;
	size.y = env->win->size_y / 4;
	i = 0;
	while (i < 24)
	{
		(env->args)[i].rect.x = i%6 * size.x;
		(env->args)[i].rect.y = i/6 * size.y;
		(env->args)[i].rect.w = size.x;
		(env->args)[i].rect.h = size.y;
		(env->args)[i].env = env;
		(env->args)[i].fractal = env->fractal;
		(env->args)[i].done = 0;
		if (!((env->args)[i].params = (t_frac_params*)malloc(sizeof(t_frac_params))))
			return ;
		ft_memcpy(env->args[i].params, env->params, sizeof(t_frac_params));
		pthread_create(&threads[i], NULL, &exec_fractal, &(env->args[i]));
		//calculate_fractal(env->win, rect, env->params, &julia);
		i++;
	}
}

int		is_fract_done(t_env *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 24)
	{
		j += (env->args)[i].done;
		i++;
	}
	return (j == 24);
}
