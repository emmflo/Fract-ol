#include <imgui.h>
#include "zoom.h"
#include "env.h"

int		mouse_move(int x, int y, t_env *env)
{
	update_ui_coord(env->ui, x, y);
	if (env->c_update && !env->drag)
	{
		env->params->c.x = (((double)x * 3.5) / (double)env->win->size_x) - 2.5;
		env->params->c.y = (((double)y * 2.0) / (double)env->win->size_y) - 1.0;
	}
	return (0);
}

int		mouse_press_button(int button, int x, int y, t_env *env)
{
	t_point	mouse;

	update_ui_coord(env->ui, x, y);
	if (button == 1)
	{
		update_ui_mouse_button(env->ui, 1);
		if (env->ui->hotitem == 0)
		{
			env->drag_start.x = x;
			env->drag_start.y = y;
			env->offset_start.x = env->params->offset.x;
			env->offset_start.y = env->params->offset.y;
			env->drag = 1;
		}
	}
	if (button == 2)
	{
	}
	if (button == 3)
		env->menu = !env->menu;
	if (button == 4)
	{
		mouse.x = x;
		mouse.y = y;
		zoom_centered(env, mouse, 0.98);
	}
	if (button == 5)
	{
		mouse.x = x;
		mouse.y = y;
		zoom_centered(env, mouse, 1.02);
	}
	return (0);
}

int		mouse_release_button(int button, int x, int y, t_env *env)
{
	update_ui_coord(env->ui, x, y);
	if (button == 1)
	{
		update_ui_mouse_button(env->ui, 0);
		if (env->drag_start.x == x && env->drag_start.y == y)
			env->c_update = !env->c_update;
		env->drag = 0;
	}
	return (0);
}

