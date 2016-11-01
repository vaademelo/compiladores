#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "next_state.h"
#include "token_classifier.h"

FILE *input_file;
fpos_t cursor_current_position;
fpos_t cursor_previous_position;

int next_state_table[MAX_NEXT_STATE_TABLE_SIZE][MAX_NEXT_STATE_TABLE_SIZE];

bool is_layout_char(int character) {
  return (character == 32 || // space
          character == 9  || // tab
          character == 10 || // new line
          character == 13);  // carriage return
}

Token* get_next_token(void) {
  Token *token;
  int current_state = 0;
  int previous_state = -1;
  int ch, lookahead;

  char buffer[MAX_TOKEN_VALUE_SIZE];
  int buffer_size_counter = 0;

  token = (Token*)malloc(sizeof(Token));

  do {
    fgetpos(input_file, &cursor_previous_position);

    ch = getc(input_file);

    if (buffer_size_counter == 0 && is_layout_char(ch)){
      continue;
    }

    previous_state = current_state;
    current_state = get_next_state(ch, current_state);

    if (current_state != 0) {
      buffer[buffer_size_counter] = ch;
      buffer_size_counter++;
    } else {
      buffer[buffer_size_counter] = '\0';
      token->class = classify_token(previous_state, current_state, buffer);
      strcpy(token->value, buffer);
      fsetpos(input_file, &cursor_previous_position);
      if (token->class == 0) {
        return get_next_token();
      } else {
        return token;
      }

    }

    // if (current_state == 0 && previous_state != 0 && !is_layout_char(ch)) {
    //   lookahead = ch;
    //   // classify_token(buffer);
    // }

  } while ( ch != EOF);

  return NULL;
}
