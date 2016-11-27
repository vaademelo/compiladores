#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "token_classifier.h"
#include "symbol_table.h"
#include "scope.h"

Scope* current_scope = NULL;

void push_scope(Scope *scope) {
  current_scope = scope;
}

Scope * pop_scope() {
  printf("\n>> Leaving scope (%d)!\n\n", current_scope->type);
  
  Scope* previous_scope = malloc(sizeof(Scope));

  previous_scope = current_scope->previous_scope;
  current_scope  = current_scope->previous_scope;

  return previous_scope;
}

void create_scope(int type) {
  printf("\n>> Entering new scope (%d)!\n\n", type);
  
  Scope* new_scope = malloc(sizeof(Scope));

  current_scope->next_scope = new_scope;

  new_scope->previous_scope = current_scope;
  new_scope->next_scope = NULL;
  new_scope->type = type;
  new_scope->symbol_table = create_symbol_table();

  push_scope(new_scope);
}

void setup_scopes(void) {
  current_scope = malloc(sizeof(Scope));
  
  printf("\n>> Creating global scope!\n\n");
  
  Scope* global_scope = malloc(sizeof(Scope));

  global_scope->previous_scope = NULL;
  global_scope->next_scope = NULL;
  global_scope->type = GLOBAL_SCOPE;
  global_scope->symbol_table = create_symbol_table();

  push_scope(global_scope);
}