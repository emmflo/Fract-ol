#include "env.h"

void	zoom_centered(t_env *env, t_point pt, double zoom)
{
	t_point	old;
	t_point	new;

	old.x = pt.x * env->params->zoom.x + env->params->offset.x;
	old.y = pt.y * env->params->zoom.y + env->params->offset.y;
	env->params->zoom.x *= zoom;
	env->params->zoom.y *= zoom;
	new.x = pt.x * env->params->zoom.x + env->params->offset.x;
	new.y = pt.y * env->params->zoom.y + env->params->offset.y;
	env->params->offset.x += (old.x - new.x);
	env->params->offset.y += (old.y - new.y);
}
