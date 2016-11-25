#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#include "lex.h"
#include "lex_setup.h"
#include "sint.h"
#include "symbol_table.h"
#include "activation_record.h"
#include "sem.h"

FILE * output_file;

int memory_address    = 512;
int while_counter     = 0;
int while_end_counter = 0;
int if_counter        = 0;
int else_counter      = 0;

void new_scope(int type) {
  create_scope();
}

void leave_scope(void) {
  pop_scope();
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
 
  new_scope(FUNC_SCOPE);
}

void while_initialize() {
  fprintf(output_file, "\nENQUANTO%02d LD /0000\n", while_counter);
  fflush(output_file);

  while_end_counter = while_counter;
  while_counter++;
}

void while_escape() {
  fprintf(output_file, "<calcula EXP_B>\n");
  fprintf(output_file, "JN FIM_ENQUANTO%02d\n", while_end_counter);
  fprintf(output_file, "JZ FIM_ENQUANTO%02d\n", while_end_counter);
  fflush(output_file);  
}

void while_finalize() {
  fprintf(output_file, "\nJP ENQUANTO%02d\n", while_end_counter);
  fprintf(output_file, "FIM_ENQUANTO%02d\n", while_end_counter);
  fflush(output_file);
  
}

void if_initialize() {
  fprintf(output_file, "\nSE%02d LD /0000\n", if_counter);
  fflush(output_file);

  else_counter = if_counter;
  if_counter++;
}

void if_escape() {
  fprintf(output_file, "<calcula EXP_B>\n");
  fprintf(output_file, "JN FIM_SE%02d\n", else_counter);
  fprintf(output_file, "JZ FIM_SE%02d\n", else_counter);
  fflush(output_file);  
}

void if_finalize() {
  fprintf(output_file, "FIM_SE%02d\n", else_counter);
  fflush(output_file);
}

void else_initialize() {
  fprintf(output_file, "JP FIM_SENAO%02d\n", else_counter);
  fprintf(output_file, "FIM_SE%02d\n", else_counter);
  fflush(output_file);
}

void else_finalize() {
  fprintf(output_file, "FIM_SENAO%02d\n", else_counter);
  fflush(output_file);
}

bool is_new_scope(Token *token, int machine, int state) {

  return (
    (machine == P_MACHINE && state == 4 && strcmp(token->value, "{") == 0)
    || (machine == CMD_MACHINE && state == 30 && strcmp(token->value, "{") == 0)
    || (machine == CMD_MACHINE && state == 36 && strcmp(token->value, "{") == 0)
  );
}

bool is_end_of_scope(Token *token, int machine, int state) {
  printf("(t: %s, m: %d, s: %d)\n", token->value, machine, state);
  return (
       (machine == P_MACHINE && state == 6  && strcmp(token->value, "}") == 0)
    || (machine == P_MACHINE && state == 14 && strcmp(token->value, "}") == 0)
    || (machine == CMD_MACHINE && state == 13 && strcmp(token->value, "}") == 0)
    || (machine == CMD_MACHINE && state == 31 && strcmp(token->value, "}") == 0)
    || (machine == CMD_MACHINE && state == 37 && strcmp(token->value, "}") == 0)
  );
}

void setup_semantic_analyzer(void) {
  output_file = fopen("output.asm", "w+");
}

void semantic_action(Token * token, int machine, int state) {
  
  bool is_leaving_scope = is_end_of_scope(token, machine, state);

  if (machine == CMD_MACHINE && state == 1) { // Declaracao de variavel
    insert_symbol(token, VAR); 
  } 

  if (machine == P_MACHINE && state == 2) { // Declaracao de funcao
    insert_symbol(token, FUNC);
    function_declaration(token);
  } 

  // *********************************
  // *  I F   -   T H E N
  // *********************************

  // Inicializando o 'if'
  if ((machine == CMD_MACHINE && state == 13 && strcmp(token->value, "se") == 0)
   || (machine == CMD_MACHINE && state == 31 && strcmp(token->value, "se") == 0) 
   || (machine == CMD_MACHINE && state == 37 && strcmp(token->value, "se") == 0) 
   || (machine == CMD_MACHINE && state == 38 && strcmp(token->value, "se") == 0)) {
    if_initialize();
    new_scope(IF_SCOPE);
  }

  // Gerar o código responsável por escapar do 'then' caso a expressão seja falso
  if (current_scope->type == IF_SCOPE
   && machine == EXP_A_MACHINE 
   && state == 2 && strcmp(token->value, ")") == 0) {
    if_escape();
  }

  // Se estiver saindo de um contexto de 'if' entao decrementa else_counter
  if (is_leaving_scope 
   && current_scope->type == IF_SCOPE 
   && (lookahead(1) == NULL || strcmp(lookahead(1)->value, "senao") != 0)) {

    if_finalize();
    else_counter--;

    leave_scope();
  }

  // *********************************
  // *  E L S E
  // *********************************

  // Finalizando o 'if' e inicializa o 'else'
  if (machine == CMD_MACHINE && state == 38 && strcmp(token->value, "senao") == 0) {
    else_initialize();
    new_scope(ELSE_SCOPE);
  }

  // Se estiver saindo de um contexto de 'else' entao decrementa else_counter
  if (is_leaving_scope && current_scope->type == ELSE_SCOPE) {
    else_finalize();
    else_counter--;

    leave_scope();
  }

    // *********************************
  // *  W H I L E 
  // *********************************

  // Inicializando o 'while'
  if ((machine == CMD_MACHINE && state == 13 && strcmp(token->value, "enquanto") == 0)
   || (machine == CMD_MACHINE && state == 31 && strcmp(token->value, "enquanto") == 0)) {
    while_initialize();
    new_scope(WHILE_SCOPE);
  }

  // Gerar o código responsável por escapar do 'while' caso a expressão seja falsa
  if (current_scope->type == WHILE_SCOPE
   && machine == EXP_A_MACHINE 
   && state == 2 && strcmp(token->value, ")") == 0) {
    while_escape();
  }

  // Se estiver saindo de um contexto de 'while' entao decrementa while
  if (is_leaving_scope && current_scope->type == WHILE_SCOPE) {
    while_finalize();
    while_end_counter--;

    leave_scope();
  }

}
