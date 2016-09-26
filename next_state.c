#include <stdio.h>
#include "lex.h"

void print_matrix (int matrix[MAX_NEXT_STATE_TABLE][MAX_NEXT_STATE_TABLE], int cols, int rows) {
  int i, j;

  for (j = 0 ; j < cols ; j++) {
    for (i = 0 ; i < rows ; i++) {
      printf("[%d] ", matrix[i][j]);
    }
    printf("\n");
  }
}

void setup_next_state_table (int next_state_table[MAX_NEXT_STATE_TABLE][MAX_NEXT_STATE_TABLE]) {
  int i, j;
  int cols, rows;

  FILE *next_state_table_file;
  next_state_table_file = fopen("next_state.txt", "r");

  fscanf(next_state_table_file, "%d %d", &cols, &rows);
  printf("\n\n%d %d\n\n", cols, rows);

  for (i = 0 ; i < rows ; i++) {
    for (j = 0 ; j < cols ; j++) {
      fscanf(next_state_table_file, "%d", &next_state_table[i][j]);
    }
  }
}

int get_character_group (int character) {
  if (character >= 97 && character <= 122) {
    return 0; // a...z
  } else if (character >= 65 && character <= 90) {
    return 1; // A...Z
  } else if (character >= 48 && character <= 57) {
    return 2; // 0...9
  } else if (character == 62) {
    return 3; // >
  } else if (character == 60) {
    return 4; // <
  } else if (character == 61) {
    return 5; // =
  } else if (character == 33) {
    return 6; // !
  } else if (character == 38) {
    return 7; // &
  } else if (character == 47) {
    return 8; // /
  } else if (character == 46) {
    return 9; // .
  } else if (character == 42) {
    return 10; // *
  } else if (character == 32) {
    return 13; // ' '
  } else if (character == 13 || character == 10) {
    return 14; // EOL
  } else {
    return 11;
  }
}

int get_next_state(int character, int current_state, int next_state_table[MAX_NEXT_STATE_TABLE][MAX_NEXT_STATE_TABLE]) {
  int character_received_group = get_character_group(character);

  return next_state_table[current_state][character_received_group];
}
