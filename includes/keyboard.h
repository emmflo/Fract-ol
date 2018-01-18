#ifndef KEYBOARD_H
# define KEYBOARD_H
# ifdef __APPLE__
#  include "key_defs.h"
# else
#  include <X11/keysym.h>
# endif

enum {menu, quit, up, down, left, right, zoom, dezoom, c_update};

# include "env.h"

int	key(int keycode, void *params);
int	key_press(int keycode, t_env *env);
int	key_release(int keycode, t_env *env);
void	key_set_default(t_keys *keys);
void	key_last_act_update(t_env *env);

# include "keyboard_type.h"

#endif
