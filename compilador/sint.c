
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "sint.h"
#include "sint_setup.h"
#include "lex.h"
#include "lex_setup.h"
#include "sem.h"
#include "symbol_table.h"


stack_cell *stack[STACK_SIZE];
int stack_pointer = 0;

Machine *current_machine;
int current_state = 0;
bool machine_popped = false;

void print_stack(void) {
  int i;
  if (stack_pointer > 0) {
    for (i = 0 ; i < stack_pointer ; i++) {
      printf("[maq: %d, est: %d]", stack[i]->machine, stack[i]->state);
    }
    printf("\n");

  } else {
    printf("Pilha Vazia\n");
  }

}

void change_machine(int machine, int state) {
  switch (machine) {
    case P_MACHINE:
      current_machine = p;
      break;

    case CMD_MACHINE:
      current_machine = cmd;
      break;

    case EXP_A_MACHINE:
      current_machine = exp_a;
      break;

    case EXP_B_MACHINE:
      current_machine = exp_b;
      break;
  }

  current_state = state;
}

void push_current_machine() {
  if (stack_pointer < STACK_SIZE) {
    stack[stack_pointer] = (stack_cell*)malloc(sizeof(stack_cell));

    stack[stack_pointer]->machine = current_machine->id;
    stack[stack_pointer]->state   = current_state;
    stack_pointer++;

    printf("TODO\n");

  } else {
    printf("\nError: Stack overflow\n");
  }
}

void pop_machine() {
  if (stack_pointer > 0) {
    change_machine(stack[stack_pointer-1]->machine, stack[stack_pointer-1]->state);
    stack_pointer--;

  } else {
    printf("\nError: Pilha Vazia\n");
  }
}

bool is_accepting_state(Machine *machine, int state) {

  int i = 0;

  switch (machine->id) {
    case P_MACHINE:
      while(p->accepting_states[i] > 0) {
        if (state == p->accepting_states[i]) {
          return true;
        }
        i++;
      }
      return false;

    case CMD_MACHINE:
      while(cmd->accepting_states[i] > 0){
        if (state == cmd->accepting_states[i]) {
          return true;
        }
        i++;
      }
      return false;

    case EXP_A_MACHINE:
      while(exp_a->accepting_states[i] > 0){
        if (state == exp_a->accepting_states[i]) {
          return true;
        }
        i++;
      }
      return false;

    case EXP_B_MACHINE:
      while(exp_b->accepting_states[i] > 0){
        if (state == exp_b->accepting_states[i]) {
          return true;
        }
        i++;
      }
      return false;
  }
}

void next_state_exp_a_machine(Token *token) {

  int next_state = get_next_state_exp_a_machine(token, current_state);

  if (next_state >= 0) {
    printf("SUBMAQ EXP_A: (%d, %s) -> %d\n", current_state, token->value, next_state);
    current_state = next_state;

    return;
  }

  if (next_state < 0 && exp_a->states_table[current_state][15] > 0) {
    printf("SUBMAQ EXP_A: (%d, EXP_A) -> %d\n", current_state, exp_a->states_table[current_state][15]);
    current_state = exp_a->states_table[current_state][15];
    push_current_machine();
    change_machine(EXP_A_MACHINE, 0);
    next_state_exp_a_machine(token);

    return;
  }

  if (is_accepting_state(current_machine, current_state) && stack_pointer > 0) {
    pop_machine();
    machine_popped = true;

    return;
  }

  printf("\n\n** Erro Sintatico **\n");
  printf("--------------------\n");
  printf("input.txt[%d:%d] ~> Token '%s' inesperado.\n\n", token->line, token->column, token->value);
  exit(0);
}

void next_state_exp_b_machine(Token *token) {

  int next_state = get_next_state_exp_b_machine(token, current_state);

  if (next_state >= 0) {
    printf("SUBMAQ EXP_B: (%d, %s) -> %d\n", current_state, token->value, next_state);
    current_state = next_state;

    return;
  }

  if (next_state < 0 && exp_b->states_table[current_state][13] > 0) {
    printf("SUBMAQ EXP_B: (%d, EXP_B) -> %d\n", current_state, exp_b->states_table[current_state][13]);
    current_state = exp_b->states_table[current_state][13];
    push_current_machine();
    change_machine(EXP_B_MACHINE, 0);
    next_state_exp_b_machine(token);

    return;
  }

  if (next_state < 0 && exp_b->states_table[current_state][14] > 0) {
    printf("SUBMAQ EXP_B: (%d, EXP_A) -> %d\n", current_state, exp_b->states_table[current_state][14]);
    current_state = exp_b->states_table[current_state][14];
    push_current_machine();
    change_machine(EXP_A_MACHINE, 0);
    next_state_exp_a_machine(token);

    return;
  }

  if (is_accepting_state(current_machine, current_state) && stack_pointer > 0) {
    pop_machine();
    machine_popped = true;

    return;
  }

  printf("\n\n** Erro Sintatico **\n");
  printf("--------------------\n");
  printf("input.txt[%d:%d] ~> Token '%s' inesperado.\n\n", token->line, token->column, token->value);
  exit(0);

}


void next_state_cmd_machine(Token *token) {

  int next_state = get_next_state_cmd_machine(token, current_state);

  if (next_state >= 0) {
    printf("SUBMAQ CMD: (%d, %s) -> %d\n", current_state, token->value, next_state);
    current_state = next_state;

    return;
  }

  if (next_state < 0 && cmd->states_table[current_state][26] > 0) {
    printf("SUBMAQ CMD: (%d, EXP_A) -> %d\n", current_state, cmd->states_table[current_state][26]);
    current_state = cmd->states_table[current_state][26];
    push_current_machine();
    change_machine(EXP_A_MACHINE, 0);
    next_state_exp_a_machine(token);

    return;
  }

  if (next_state < 0 && cmd->states_table[current_state][27] > 0) {
    printf("SUBMAQ CMD: (%d, CMD) -> %d\n", current_state, cmd->states_table[current_state][27]);
    current_state = cmd->states_table[current_state][27];
    push_current_machine();
    change_machine(CMD_MACHINE, 0);
    next_state_cmd_machine(token);

    return;
  }

  if (next_state < 0 && cmd->states_table[current_state][28] > 0) {
    printf("SUBMAQ CMD: (%d, EXP_B) -> %d\n", current_state, cmd->states_table[current_state][28]);
    current_state = cmd->states_table[current_state][28];
    push_current_machine();
    change_machine(EXP_B_MACHINE, 0);
    next_state_exp_b_machine(token);

    return;
  }

  if (is_accepting_state(current_machine, current_state) && stack_pointer > 0) {
    pop_machine();
    machine_popped = true;

    return;
  }

  printf("\n\n** Erro Sintatico **\n");
  printf("--------------------\n");
  printf("input.txt[%d:%d] ~> Token '%s' inesperado.\n\n", token->line, token->column, token->value);
  exit(0);
}


void next_state_p_machine(Token *token) {

  int next_state = get_next_state_p_machine(token, current_state);

  if (next_state >= 0) {
    printf("SUBMAQ P: (%d, %s) -> %d\n", current_state, token->value, next_state);
    current_state = next_state;

    return;
  }

  if (next_state < 0 && p->states_table[current_state][18] > 0) {
    printf("SUBMAQ P: (%d, CMD) -> %d\n", current_state, p->states_table[current_state][18]);

    current_state = p->states_table[current_state][18];
    push_current_machine();
    change_machine(CMD_MACHINE, 0);
    next_state_cmd_machine(token);

    return;
  }

  if (is_accepting_state(current_machine, current_state) && stack_pointer > 0) {
    pop_machine();
    machine_popped = true;

    return;
  }

  printf("\n\n** Erro Sintatico **\n");
  printf("--------------------\n");
  printf("input.txt[%d:%d] ~> Token '%s' inesperado.\n\n", token->line, token->column, token->value);
  exit(0);
}

void next_state(Token *token) {

  switch (current_machine->id) {
    case P_MACHINE:
      next_state_p_machine(token);
      break;

    case CMD_MACHINE:
      next_state_cmd_machine(token);
      break;

    case EXP_A_MACHINE:
      next_state_exp_a_machine(token);
      break;

    case EXP_B_MACHINE:
      next_state_exp_b_machine(token);
      break;
  }
}

void preserve_token_on_pop(Token *token){
  if (machine_popped){
    machine_popped = false;
    next_state(token);
    if(machine_popped) {
      preserve_token_on_pop(token);
    }
  }
}

void syntactic_analysis(void) {
  Token *token;
  change_machine(P_MACHINE, 0);

  while(token != NULL) {
    // if (is_accepting_state(current_machine, current_state) && stack_pointer == 0) {
    //   return;
    // }

    token = get_next_token();

    next_state(token);
    preserve_token_on_pop(token);

    semantic_action(token, current_machine->id, current_state);
  }
}
