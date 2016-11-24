#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#include "lex.h"
#include "lex_setup.h"
#include "sint.h"
#include "symbols_table.h"
#include "sem.h"

FILE * output_file;
int memory_address = 512;
int while_counter = 0;


void new_scope(void) {
  create_new_scope();
}

void leave_scope(void) {
  leave_current_scope();
}

void start_code(void) {
  fprintf(output_file, "MAIN JP /0000\n");
  fflush(output_file);
  
  memory_address += 2;
}

void end_code(void) {
  fprintf(output_file, "HM /00\n");
  fprintf(output_file, "#  P\n");
  fflush(output_file);

  memory_address += 4;
}

void function_declaration(Token *token) {
  fprintf(output_file, "\n; ** Subrotina %s\n", token->value);
  fprintf(output_file, "%s JP /0000 ; Guarda o endereco de retorno para a rotina anterior\n", token->value);
  fflush(output_file);
 
  new_scope();
}

void while_initialize() {
  fprintf(output_file, "\nLACO%02d LD /0000\n", while_counter);
  fflush(output_file);

  while_counter++;
}

bool is_new_scope(Token *token, int machine, int state) {

  return (
    (machine == P_MACHINE && state == 6 && strcmp(token->value, "{") == 0)
    || (machine == CMD_MACHINE && state == 31 && strcmp(token->value, "{") == 0)
    || (machine == CMD_MACHINE && state == 37 && strcmp(token->value, "{") == 0)
  );
}

bool is_end_of_scope(Token *token, int machine, int state) {
  printf("(t: %s, m: %d, s: %d)\n", token->value, machine, state);
  return (
       (machine == P_MACHINE && state == 3)
    || (machine == P_MACHINE && state == 20)
    || (machine == P_MACHINE && state == 14 && strcmp(token->value, "}") == 0)
    || (machine == CMD_MACHINE && state == 20 && strcmp(token->value, "}") == 0)
    || (machine == CMD_MACHINE && state == 37 && strcmp(token->value, "}") == 0)
    || (machine == CMD_MACHINE && state == 38 && strcmp(token->value, "}") == 0)
  );
}

void setup_semantic_analyzer(void) {
  output_file = fopen("output.asm", "w+");
  start_code();
  end_code();
}

void semantic_action(Token * token, int machine, int state) {
  if (machine == CMD_MACHINE && state == 7) { // Declaracao de variavel
    insert_symbol_table(token, VAR); 
  } 

  if (machine == P_MACHINE && state == 5) { // Declaracao de funcao
    insert_symbol_table(token, FUNC);
    function_declaration(token);
  } 

  if (machine == P_MACHINE && state == 14 && strcmp(token->value, "enquanto") == 0) {
    while_initialize();
  }

  if (is_new_scope(token, machine, state)) {
    new_scope();
  }

  if (is_end_of_scope(token, machine, state)) {
    leave_scope();
  } 
}
