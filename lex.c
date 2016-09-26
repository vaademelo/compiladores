#include <stdio.h>
#include "lex.h"
#include "next_state.h"
#include "classifier.h"

void initialize_buffer(int buffer[MAX_BUFFER_SIZE]) {
  int i;

  for (i = 0 ; i < MAX_BUFFER_SIZE ; i++) {
    buffer[i] = -1;
  }
}

void get_next_token(void) {

  int current_state = 0;
  int previous_state = -1;

  int ch;
  int buffer[MAX_BUFFER_SIZE];

  int next_state_table[MAX_NEXT_STATE_TABLE][MAX_NEXT_STATE_TABLE];
  setup_next_state_table(next_state_table);

  printf("\n\n[%d]\n\n", next_state_table[9][5]);

  // ch = getchar();
  // printf("Codigo ASCII: %d\n", ch);
  // printf("Caracter: %c\n", ch);
  // printf("Estado atual: %d\n", current_state);
  // printf("Proximo estado: %d\n", get_next_state(ch, current_state, next_state_table));


  FILE *input_file;
  input_file = fopen("input.txt", "r");

  while ((ch = getc(input_file)) != EOF) {

    previous_state = current_state;
    current_state = get_next_state(ch, current_state, next_state_table);

    if (current_state == 0 && previous_state != 0) {
      classify_token(buffer);
    }

  }

  fclose(input_file);

}
