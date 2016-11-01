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

int classify_integer(char buffer[MAX_TOKEN_VALUE_SIZE]) {
  return 1;
}

int classify_float(char buffer[MAX_TOKEN_VALUE_SIZE]) {
  return 2;
}

int classify_string(char buffer[MAX_TOKEN_VALUE_SIZE]) {
  return 3;
}

int classify_special_symbol(char buffer[MAX_TOKEN_VALUE_SIZE]) {
  return 4;
}

int classify_identifier(char buffer[MAX_TOKEN_VALUE_SIZE]) {
  if (is_reserved_word(buffer)) {
    return 5; // palavra reservada
  } else if (is_type(buffer)) {
    return 7; // tipo
  } else {
    return 6; // identificador
  }
}

/**
* 0 - comentarios
* 1 - inteiro
* 2 - flutuante
* 3 - string
* 4 - simbolos especiais
* 5 - palavra reservada
* 6 - identificador
* 7 - tipo
**/
int classify_token(int previous_state, int current_state, char buffer[MAX_TOKEN_VALUE_SIZE]) {
   if (previous_state == 3) {
    return classify_integer(buffer); // numero inteiro

  } else if (previous_state == 4) {
    return classify_float(buffer); // numero flutuante

  } else if (previous_state == 25) {
    return classify_string(buffer); // string

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
             previous_state == 14 ||
             previous_state == 20 ||
             previous_state == 21 ||
             previous_state == 22 ||
             previous_state == 23) {
    return classify_special_symbol(buffer); // simbolos especiais

  } else if (previous_state == 2) {
    return classify_identifier(buffer); // identificador

  } else
    return 0;
}
