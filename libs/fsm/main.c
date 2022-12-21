#include "libfsm.h"

bool	is_not_equal_character(void *ch, void *event_data);
void	print_message(void *data, void *event_data);
void	split_token(void *data, void *event_data, void *new_data);

t_state state_general, state_quote, state_dquote, state_end;

t_state state_end = {
	.transitions = NULL,
	.num_transitions = 0
};

t_state state_group = {
    .parent_state = NULL,
    .entry_state = &state_general,
    .transitions = (t_transition[]){
		{(void *)(intptr_t)'\0', is_equal_character, NULL, &state_end},
	},
    .num_transitions = 1,
    .data = "group",
    .entry_action = &print_message,
    .exit_action = &print_message,
};

t_state state_general = {
    .parent_state = &state_group,
    .entry_state = NULL,
    .transitions = (t_transition[]){
		{(void *)(intptr_t)' ', is_equal_character, &split_token, &state_general},
		{(void *)(intptr_t)'\'', is_equal_character, NULL, &state_quote},
		{(void *)(intptr_t)'"', is_equal_character, NULL, &state_dquote},
	},
    .num_transitions = 3,
    .data = "general",
    .entry_action = &print_message,
    .exit_action = &print_message,
};

t_state state_quote = {
    .parent_state = &state_group,
    .entry_state = NULL,
    .transitions = (t_transition[]){
		{(void *)(intptr_t)'\'', is_equal_character, NULL, &state_general},
	},
    .num_transitions = 1,
    .data = "quote",
    .entry_action = &print_message,
    .exit_action = &print_message,
};

t_state state_dquote = {
    .parent_state = &state_group,
    .entry_state = NULL,
    .transitions = (t_transition[]){
		{(void *)(intptr_t)'"', is_equal_character, NULL, &state_general},
	},
    .num_transitions = 1,
    .data = "dquote",
    .entry_action = &print_message,
    .exit_action = &print_message,
};

t_state state_error = {
	.entry_action = &print_message,
};

bool	is_equal_character(void *ch, void *data)
{
	return ((intptr_t)ch == (intptr_t)data);
};

bool	is_not_equal_character(void *ch, void *data)
{
	return ((intptr_t)ch != (intptr_t)data);
}

void print_message(void *state_data, void *event_data)
{
	exit(0);
	printf( "state_data: %s\n", (char *)state_data);
}

void split_token(void *state_data, void *event_data, void *new_data)
{
	new_data = state_data;
	printf("split: %c\n", *(char *)state_data);
}

int main (int argc, char  **argv)
{
	t_state_machine fsm;
	t_torkenizer	tk;
	char			*line;

	if (argc != 2)
		return (0);
	tk.str = argv[1];
	tk.pos = argv[1];
	fsm_init(&fsm, &state_general, &state_error);
	while (true)
	{
		int ret = fsm_handle_event(&fsm, &tk);
		if (ret == FSM_STATE_END_REACHED)
			break;
	}
	return (0);
}