
#include "libfsm.h"

static void	_goto_error_state(t_state_machine *fsm, void *const event)
{
	fsm->previous_state = fsm->current_state;
	fsm->current_state = fsm->error_state;
	if (fsm->current_state && fsm->current_state->entry_action)
		fsm->current_state->entry_action(fsm->current_state->data, event);
}

static t_transition	*_get_transition(t_state_machine *fsm, t_state *state,
	void *const event_data)
{
	t_transition	*t;
	size_t			i;

	(void)fsm;
	i = 0;
	while (i < state->num_transitions)
	{
		t = &state->transitions[i];
		if (!t->guard)
			return (t);
		else if (t->guard(t->condition, event_data))
			return (t);
		i++;
	}
	return (NULL);
}

static int _judge_status(t_state_machine *fsm)
{
	if (fsm->current_state == fsm->previous_state)
		return (FSM_STATE_LOOP);
	if (fsm->current_state == fsm->error_state)
		return (FSM_ERR_STATE_REACHED);
	if (!fsm->current_state->num_transitions)
		return (FSM_STATE_END_REACHED);
	return (FSM_STATE_CHANGED);
}
int	fsm_handle_event(t_state_machine *fsm, void *event_data)
{
	t_state			*next_state;
	t_transition	*transition;

	if (!fsm|| !event_data)
		return (FSM_ERR_ARGS);
	if (!fsm->current_state)
	{
		_goto_error_state(fsm, event_data);
		return (FSM_ERR_STATE_REACHED);
	}
	if (!fsm->current_state->num_transitions)
		return (FSM_STATE_NOT_CHANGED);
	next_state = fsm->current_state;
	while (true)
	{
		transition = _get_transition(fsm, next_state, event_data);
		if (!transition)
		{
			next_state = next_state->parent_state;
			if (!next_state)
				break ;
			continue ;
		}
		if (!transition->next_state)
		{
			_goto_error_state(fsm, event_data);
			return (FSM_ERR_STATE_REACHED);
		}
		next_state = transition->next_state;
		while (next_state->entry_state)
			next_state = next_state->entry_state;
		if (next_state != fsm->current_state && fsm->current_state->exit_action)
			fsm->current_state->exit_action(fsm->current_state->data, event_data);
		if (transition->action)
			transition->action(fsm->current_state->data, event_data, next_state->data);
		if (next_state != fsm->current_state && next_state->entry_action)
		fsm->previous_state = fsm->current_state;
		fsm->current_state = next_state;
		return (_judge_status(fsm));
	}
	return (FSM_STATE_NOT_CHANGED);
}
