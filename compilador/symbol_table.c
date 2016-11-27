#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "token_classifier.h"
#include "symbol_table.h"
#include "scope.h"

void print_symbol_table(Symbol_table_row *row) {
  printf(">>>>>>>>>>>>> (%s | %d | %d| %d)\n", row->lexeme, row->class, row->type, row->relative_position);
  if(row->next_row){
    print_symbol_table(row->next_row);  
  }
}

Symbol_table* create_symbol_table() {
  Symbol_table* new_table = malloc(sizeof(Symbol_table));

  new_table->parent_symbol_table = current_scope->symbol_table;
  new_table->first_row = NULL; 

  return new_table;
}

void create_row(Symbol_table_row * row, char lexeme[MAX_TOKEN_VALUE_SIZE], int class, int type, int relative_position) {
  if (strcmp(row->lexeme, lexeme) == 0) {
    printf("\n\n** Erro Semantico **\n");
    printf("--------------------\n");
    printf("Identificador '%s' declarado anteriormente.\n\n");
    exit(0);

  } else if(row->next_row == NULL){
    Symbol_table_row* new_row = malloc(sizeof(Symbol_table_row));

    new_row->next_row = NULL;
    strcpy(new_row->lexeme, lexeme);
    new_row->class = class;
    new_row->type = type;
    new_row->relative_position = relative_position;

    row->next_row = new_row;

    return;

  } else {
    create_row(row->next_row, lexeme, class, type, relative_position);
  }
}

void insert_symbol(char lexeme[MAX_TOKEN_VALUE_SIZE], int class, int type, int relative_position) {

  printf("********Inserindo simbolo: %s\n", lexeme);
  if (current_scope->symbol_table->first_row != NULL) {

    create_row(current_scope->symbol_table->first_row, lexeme, class, type, relative_position);
  
  } else {
    
    current_scope->symbol_table->first_row = malloc(sizeof(Symbol_table_row));

    current_scope->symbol_table->first_row->next_row = NULL;
    strcpy(current_scope->symbol_table->first_row->lexeme, lexeme);
    current_scope->symbol_table->first_row->class = class;
    current_scope->symbol_table->first_row->type = type;
    current_scope->symbol_table->first_row->relative_position = relative_position;
  }
  print_symbol_table(current_scope->symbol_table->first_row);
}

Symbol_table_row* recursive_search_table(Symbol_table_row* row, char lexeme[MAX_TOKEN_VALUE_SIZE]) {

  // printf("###########teste (l:%s, lt:%s)\n", lexeme, row->lexeme);
  if (strcmp(row->lexeme, lexeme) == 0) {
    return row;
  
  } else if(row->next_row == NULL) {
    return NULL;
  
  } else {
    return recursive_search_table(row->next_row, lexeme);
  }
}

Symbol_table_row* recursive_search_scopes(Scope* scope, char lexeme[MAX_TOKEN_VALUE_SIZE]) {
  
  Symbol_table_row* aux_row = malloc(sizeof(Symbol_table_row));
  if (scope->symbol_table->first_row != NULL) {
    aux_row = recursive_search_table(scope->symbol_table->first_row, lexeme);  
  } else {
    return recursive_search_scopes(scope->previous_scope, lexeme);
  }
  
  // printf("########%s\n", aux_row);
  // printf("######## ps:%s\n", scope->previous_scope);
  if (aux_row != NULL) {
    return aux_row;
  
  } else if(scope->previous_scope == NULL) {
    return NULL;
  
  } else {
    return recursive_search_scopes(scope->previous_scope, lexeme);
  }
}

Symbol_table_row* lookup_symbol(char lexeme[MAX_TOKEN_VALUE_SIZE]) {

  return recursive_search_scopes(current_scope, lexeme);
}


