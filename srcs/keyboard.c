#include <stdlib.h>
#include "keyboard.h"
#include "graphics.h"
#include "env.h"

int		key_press(int keycode, t_env *env)
{
	int	i;

	i = 0;
	while (i < NB_ACT)
	{
		if (keycode == env->keys.act_key[i])
			env->keys.act[i] = 1;
		i++;
	}
}

int		key_release(int keycode, t_env *env)
{
	int	i;

	i = 0;
	while (i < NB_ACT)
	{
		if (keycode == env->keys.act_key[i])
			env->keys.act[i] = 0;
		i++;
	}
}

void	key_set_default(t_keys *keys)
{
	int	i;

	i = 0;
	while (i < NB_ACT)
	{
		keys->act_key[i] = -1;
		keys->act[i] = 0;
		keys->last_act[i] = 0;
		i++;
	}
	keys->act_key[menu] = XK_Tab;
	keys->act_key[quit] = XK_Escape;
	keys->act_key[up] = XK_w;
	keys->act_key[left] = XK_a;
	keys->act_key[down] = XK_s;
	keys->act_key[right] = XK_d;
	keys->act_key[zoom] = XK_q;
	keys->act_key[dezoom] = XK_e;
	keys->act_key[c_update] = XK_r;
	keys->act_key[angle_up] = XK_Up;
	keys->act_key[angle_down] = XK_Down;
}

void	key_last_act_update(t_env *env)
{
	int	i;

	i = 0;
	while (i < NB_ACT)
	{
		env->keys.last_act[i] = env->keys.act[i];
		i++;
	}
}
