#include <stdbool.h>
#include <string.h>
#include "token_classifier.h"
#include "lex_setup.h"

bool is_reserved_word(char buffer[MAX_TOKEN_VALUE_SIZE]) {
  int i;

  for (i = 0 ; i < reserved_words_list->length ; i++) {
    if (strcmp(buffer, reserved_words_list->items[i]) == 0) {
      return true;
    }
  }
}

bool is_type(char buffer[MAX_TOKEN_VALUE_SIZE]) {
  int i;

  for (i = 0 ; i < types_list->length ; i++) {
    if (strcmp(buffer, types_list->items[i]) == 0) {
      return true;
    }
  }
}

int classify_identifier(char buffer[MAX_TOKEN_VALUE_SIZE]) {
  if (is_reserved_word(buffer)) {
    return 2; // palavra reservada
  } else if (is_type(buffer)) {
    return 3; // tipo
  } else {
    return 4; // outros
  }
}

int classify_special_symbol(char buffer[MAX_TOKEN_VALUE_SIZE]) {
  return 1;
}

int classify_number(char buffer[MAX_TOKEN_VALUE_SIZE]) {
  return 0;
}

/**
* 0 - numero
* 1 - simbolos especiais
* 2 - palavra reservada
* 3 - tipo
* 4 - outros
* 5 - comentarios
**/
int classify_token(int previous_state, int current_state, char buffer[MAX_TOKEN_VALUE_SIZE]) {
   if (previous_state == 3 || previous_state == 4) {
    return classify_number(buffer); // numero

  } else if (previous_state == 1 ||
             previous_state == 5 ||
             previous_state == 6 ||
             previous_state == 7 ||
             previous_state == 8 ||
             previous_state == 9 ||
             previous_state == 10 ||
             previous_state == 11 ||
             previous_state == 12 ||
             previous_state == 13 ||
             previous_state == 14) {
    return classify_special_symbol(buffer); // simbolos especiais

  } else if (previous_state == 2) {
    return classify_identifier(buffer); // identifier

  } else
  return 5;
}
