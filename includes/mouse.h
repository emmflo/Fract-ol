#ifndef MOUSE_H
# define MOUSE_H

int		mouse_move(int x, int y, t_env *env);
int		mouse_press_button(int button, int x, int y, t_env *env);
int		mouse_release_button(int button, int x, int y, t_env *env);

#endif
