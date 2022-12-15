#ifndef LIBFSM_H
# define LIBFSM_H

#include <stdint.h>
#include <stdio.h>

typedef void (* fsm_state)(efsm *, fsm_event const *);
typedef void (* state_action)(void);
typedef uint32_t fsm_event_signal;
typedef uint32_t fsm_status;
typedef uint32_t fsm_input;

#define FSM_STATE_NUM 1
typedef struct fsm_actions
{
	state_action background;
	state_action start;
	state_action state_actions[FSM_STATE_NUM];
	state_action error;
}	fsm_actions;

typedef struct fsm_event
{
	fsm_event_signal m_signal;
	int m_source;
	int m_error_code;
}	fsm_event;

typedef struct efsm {
	fsm_state	m_state;
	fsm_status	m_status;
	fsm_actions m_actions;
}	efsm;

typedef

void fsm_create(efsm *machine, fsm_actions actions);
void fsm_reset(efsm *machine);
void fsm_run_machine (efsm *machine, fsm_event const *event, fsm_status *status);
void fsm_generate_event (fsm_event *event, fsm_input *input);

#endif


