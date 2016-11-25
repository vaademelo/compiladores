#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "token_classifier.h"
#include "activation_record.h"
#include "symbol_table.h"

void print_symbol_table(Symbol_table_row *row) {
  printf("%s | %d | %d\n", row->lexeme, row->class, row->type);
  if(row->next_row){
    print_symbol_table(row->next_row);  
  }
}

Symbol_table * create_symbol_table() {
  Symbol_table *new_table = malloc(sizeof(Symbol_table));

  new_table->parent_symbol_table = current_scope->symbol_table;
  new_table->first_row = NULL; 

  return new_table;
}

void create_row(Symbol_table_row * row, char lexeme[MAX_TOKEN_VALUE_SIZE], int class, int type) {
  if (strcmp(row->lexeme, lexeme) == 0) {
    printf("\n\n** Erro Semantico **\n");
    printf("--------------------\n");
    printf("input.txt[%d:%d] ~> Identificador '%s' declarado anteriormente.\n\n", token->line, token->column, token->value);
    exit(0);

  } else if(row->next_row == NULL){
    Symbol_table_row * new_row = malloc(sizeof(Symbol_table_row));

    new_row->next_row = NULL;
    strcpy(new_row->lexeme, lexeme);
    new_row->class = class;
    new_row->type = type;

    row->next_row = new_row;

    return;

  } else {
    create_row(row->next_row, lexeme, class, type);
  }
}

void insert_symbol(char lexeme[MAX_TOKEN_VALUE_SIZE], int class, int type) {
  
  if (current_scope->symbol_table->first_row != NULL) {
    create_row(current_scope->symbol_table->first_row, token, type);
  
  } else {
    current_scope->symbol_table->first_row = malloc(sizeof(Symbol_table_row));

    current_scope->symbol_table->first_row->next_row = NULL;
    strcpy(current_scope->symbol_table->first_row->lexeme, lexeme);
    current_scope->symbol_table->first_row->class = class;
    current_scope->symbol_table->first_row->type = type;
  }
  
}

bool lookup_symbol(Symbol_table *table, char lexeme[MAX_TOKEN_VALUE_SIZE]) {
  // int symbol_table_number_of_rows = current_scope->symbol_table->symbol_table->number_of_rows;
  // int i
  // for (i = 0 ; i < symbol_table_number_of_rows ; i++) {

  // }
}


