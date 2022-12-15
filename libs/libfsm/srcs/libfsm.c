
#include "libfsm.h"

void 	fsm_start	(efsm *machine, fsm_event const *event)
{
	machine->m_status = 1;
	machine->m_actions.start();
	machine->m_state = (fsm_state)(fsm_state_0);
	machine->m_state(machine, event);
}

void 	fsm_error (efsm *machine, fsm_event const *event)
{
	machine->m_status = 3;

	switch(event->m_signal)
	{
		case 3:
			machine->m_state = (fsm_state)(fsm_state_0);
			machine->m_state(machine, event);
		default:
			machine->m_actions.error();
	}
}


void	fsm_state_0 (efsm *machine, fsm_event const *event)
{
	machine->m_status = 2;
	switch (event->m_signal)
	{
		case 1:
			machine->m_state = (fsm_state)(fsm_start);
			machine->m_state = (machine, event);
			break ;
		case 2:
			machine->m_state = (fsm_state)(fsm_error);
			machine->m_state = (machine, event);
			break ;
		default:
			machine->m_actions.state_actions[0]();
	}
}

void fst_create(efsm *machine, fsm_actions *actions)
{
	size_t	i;

	machine->m_state = (fsm_state)(fsm_start);
	machine->m_status = 0;
	machine->m_actions.background = actions->background;

	i = 0;
	while (i < FSM_STATE_NUM)
	{
		machine->m_actions.state_actions[i] = actions->state_actions[i];
		i++;
	}
}

void	fsm_reset(efsm *machine)
{
	machine->m_state = 0;
	machine->m_status = 0;
}

void	fsm_run_machine(efsm *machine, fsm_event const *event, fsm_status *status)
{
	machine->m_state(machine, event);
	machine->m_actions.background();
	status = machine->m_status;
}

void fsm_generate_event (fsm_event *event, fsm_input *input)
{
	event->m_signal = (fsm_event_signal)(* input);
}