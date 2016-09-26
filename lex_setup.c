#include <stdio.h>
#include "lex_setup.h"
#include "lex.h"

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
  FILE *reserved_words_file;

  reserved_words_file = fopen("setup_files/reserved_words.txt", "r");
  //
  // fscanf(next_state_table_file, "%d %d", &cols, &rows);
  // printf("\n\n%d %d\n\n", cols, rows);
  //
  // for (i = 0 ; i < rows ; i++) {
  //   for (j = 0 ; j < cols ; j++) {
  //     fscanf(next_state_table_file, "%d", &next_state_table[i][j]);
  //   }
  // }
}

void open_input_file(void) {
  input_file = fopen("input.txt", "r");
}

void setup_lexical_analizer(void) {
  open_input_file();
  setup_next_state_table();
}
