#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "token_classifier.h"
#include "symbols_table.h"


Scope * current_scope = NULL;
Tree  * scopes_tree;

void print_symbol_table(Symbol_table_row *row) {
  printf("%s | %d | %d\n", row->name, row->class, row->type);
  if(row->next_row){
    print_symbol_table(row->next_row);  
  }
}

void create_new_scope() {
  printf("\n>> Entering new scope!\n\n");
  Scope *new_scope = malloc(sizeof(Scope));

  new_scope->parent_scope = current_scope;
  new_scope->symbol_table_first_row = NULL;  

  current_scope = new_scope;
}

void leave_current_scope() {
  printf("\n>> Leaving scope!\n\n");
  
  current_scope = current_scope->parent_scope;
}

void setup_scopes(void) {
  scopes_tree   = malloc(sizeof(Tree));
  current_scope = malloc(sizeof(Scope));
  
  create_new_scope();
}

void create_new_row(Symbol_table_row * row, Token * token, int type) {
  if (strcmp(row->name, token->value) == 0) {
    printf("\n\n** Erro Semantico **\n");
    printf("--------------------\n");
    printf("input.txt[%d:%d] ~> Identificador '%s' declarado anteriormente.\n\n", token->line, token->column, token->value);
    exit(0);

  } else if(row->next_row == NULL){
    Symbol_table_row * new_row = malloc(sizeof(Symbol_table_row));

    new_row->next_row = NULL;
    strcpy(new_row->name, token->value);
    new_row->class = token->class;
    new_row->type = type;

    row->next_row = new_row;

    return;

  } else {
    create_new_row(row->next_row, token, type);
  }
}

void insert_symbol_table(Token *token, int type) {
  if (current_scope->symbol_table_first_row != NULL) {
    create_new_row(current_scope->symbol_table_first_row, token, type);
  
  } else {
    current_scope->symbol_table_first_row = malloc(sizeof(Symbol_table_row));

    current_scope->symbol_table_first_row->next_row = NULL;
    strcpy(current_scope->symbol_table_first_row->name, token->value);
    current_scope->symbol_table_first_row->class = token->class;
    current_scope->symbol_table_first_row->type = type;
  }
  
}

void lookup(Scope *scope, Token *token) {
  // int symbol_table_number_of_rows = current_scope->symbol_table->number_of_rows;
  // int i
  // for (i = 0 ; i < symbol_table_number_of_rows ; i++) {

  // }
}


