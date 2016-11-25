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
int file_current_line = 1;
int file_current_column = 1;

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
  int ch;

  char buffer[MAX_TOKEN_VALUE_SIZE];
  int buffer_size_counter = 0;

  token = (Token*)malloc(sizeof(Token));
  token->line = file_current_line;

  do {
    fgetpos(input_file, &cursor_previous_position);

    ch = getc(input_file);
    file_current_column++;

    if (buffer_size_counter == 0 && (ch == 13 || ch == 10)) {
      file_current_line++;
      file_current_column = 1;
      token->line = file_current_line;
    }

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
      file_current_column--;
      token->column = file_current_column - buffer_size_counter;
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

Token* lookahead(int k) {
  Token *token;
  int i;
  int saved_file_current_line = file_current_line;
  int saved_file_current_column = file_current_column;  
  fpos_t saved_cursor_previous_position;

  // We start by getting the position of file reading cursor so we can return to the same
  // point at the end of this function.
  fgetpos(input_file, &saved_cursor_previous_position);

  // Then we perform a loop k times, once we are looking for the token k positions
  // ahead.
  for (i = 0 ; i < k ; i++) {
    // At this point the program asks for a token
    token = get_next_token();
  }

  // Finally we restore the position of the file reading cursor.
  fsetpos(input_file, &saved_cursor_previous_position);
  file_current_line = saved_file_current_line;
  file_current_column = saved_file_current_column;

  return token;
}
