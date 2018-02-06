#ifndef KEYBOARD_TYPE_H
# define KEYBOARD_TYPE_H
# define NB_ACT 11 

typedef struct	s_keys
{
	int	act[NB_ACT];
	int	last_act[NB_ACT];
	int	act_key[NB_ACT];
}		t_keys;

#endif
