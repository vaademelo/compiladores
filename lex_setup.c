#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lex_setup.h"
#include "lex.h"

List *reserved_words_list;
List *types_list;

void setup_next_state_table(void) {
  int i, j;
  int cols, rows;
  FILE *next_state_table_file;

  next_state_table_file = fopen("setup_files/next_state.txt", "r");

  fscanf(next_state_table_file, "%d %d", &cols, &rows);
  printf("\n\n%d %d\n\n", cols, rows);

  for (i = 0 ; i < rows ; i++) {
    for (j = 0 ; j < cols ; j++) {
      fscanf(next_state_table_file, "%d", &next_state_table[i][j]);
    }
  }
}

void setup_reserved_words_list(void) {
  int i;
  int number_of_reserved_words;
  FILE *reserved_words_file;

  reserved_words_list = (List*)malloc(sizeof(List));

  reserved_words_file = fopen("setup_files/reserved_words.txt", "r");

  fscanf(reserved_words_file, "%d", &number_of_reserved_words);
  reserved_words_list->length = number_of_reserved_words;

  for (i = 0 ; i < number_of_reserved_words ; i++) {
    fscanf(reserved_words_file, "%s", reserved_words_list->items[i]);
  }
}

void setup_types_list(void) {
  int i;
  int number_of_types;
  FILE *types_file;

  types_list = (List*)malloc(sizeof(List));

  types_file = fopen("setup_files/types.txt", "r");

  fscanf(types_file, "%d", &number_of_types);
  types_list->length = number_of_types;

  for (i = 0 ; i < number_of_types ; i++) {
    fscanf(types_file, "%s", types_list->items[i]);
  }
}

void open_input_file(void) {
  input_file = fopen("input.txt", "r");
}

void setup_lexical_analizer(void) {
  open_input_file();
  setup_next_state_table();
  setup_reserved_words_list();
  setup_types_list();
}
