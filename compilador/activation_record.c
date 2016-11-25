#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "token_classifier.h"
#include "symbol_table.h"

Scope * current_scope = NULL;

void push_scope(Scope *scope) {
  printf("\n>> Entering new scope (%d)!\n\n", type);
  
  current_scope = scope;
}

void create_scope(int type) {
  Scope *new_scope = malloc(sizeof(Scope));

  current_scope->next_scope = new_scope;
  
  new_scope->previous_scope = current_scope;
  new_scope_next_scope = NULL;
  new_scope->type = type;
  new_scope->symbol_table = create_symbol_table();

  push_scope(new_scope);
}

Scope * pop_scope() {
  printf("\n>> Leaving scope (%d)!\n\n", current_scope->type);
  
  previous_scope = malloc(sizeof(Scope));
  previous_scope = current_scope->previous_scope;

  current_scope = current_scope->previous_scope;

  return previous_scope;
}

void setup_scopes(void) {
  current_scope = malloc(sizeof(Scope));
  
  Scope *global_scope = malloc(sizeof(Scope));

  global_scope->previous_scope = current_scope;
  global_scope->first_row = NULL;
  global_scope->type = type;  

  push_scope(global_scope);
}