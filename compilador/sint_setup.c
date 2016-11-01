#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "sint_setup.h"

Machine *p;
Machine *cmd;
Machine *exp_a;
Machine *exp_b;

void setup_machine(Machine *m, FILE *machine_file) {
  int i, j;
  int cols, rows;
  int number_of_accepting_states;

  fscanf(machine_file, "%d %d", &cols, &rows);
  fscanf(machine_file, "%d", &number_of_accepting_states);

  for(i = 0 ; i < number_of_accepting_states ; i++) {
    fscanf(machine_file, "%d", &m->accepting_states[i]);
  }

  //Marcando o final da lista
  m->accepting_states[i] = -1;

  for (i = 0 ; i < rows ; i++) {
    for (j = 0 ; j < cols ; j++) {
      fscanf(machine_file, "%d", &m->states_table[i][j]);
    }
  }
}

void setup_syntactic_analizer(void) {
  p     = (Machine*)malloc(sizeof(Machine));
  cmd   = (Machine*)malloc(sizeof(Machine));
  exp_a = (Machine*)malloc(sizeof(Machine));
  exp_b = (Machine*)malloc(sizeof(Machine));

  p->id     = P_MACHINE;
  cmd->id   = CMD_MACHINE;
  exp_a->id = EXP_A_MACHINE;
  exp_b->id = EXP_B_MACHINE;

  setup_machine(p, fopen("setup_files/submaq_p.txt", "r"));
  setup_machine(cmd, fopen("setup_files/submaq_cmd.txt", "r"));
  setup_machine(exp_a, fopen("setup_files/submaq_exp_a.txt", "r"));
  setup_machine(exp_b, fopen("setup_files/submaq_exp_b.txt", "r"));

}
