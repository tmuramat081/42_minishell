#include "lexer.h"

#define NUM_STATES 3

state_func_t* const state_table[NUM_STATES] = {
    do_state_initial, do_state_foo, do_state_bar
};

transition_func_t * const	transition_table[NUM_STATES][NUM_STATES] = {
    {NULL, change_single_quote_mode, change_single_quote_mode},
    {NULL, change_double_quote_mode, change_double_quote_mode},
    { do_bar_to_initial, do_bar_to_foo,     do_bar_to_bar }
};


void	change_single_quote(void *data)
{
	data->
}

void	change_double_quote(void *data);
{

}

t_state run_state(t_state cur_state, void *data)
{
	t_state			new_state;
	transition_func_t	*transition;

	new_state = state_table[cur_state](data);
	transition = transition_table[cur_state][new_state];

	if (transition)
	{
		transition(data);
	}
	return (new_state);
}