#include <stdio.h>
#include "lex.h"
#include "lex_setup.h"

int main(void) {
  Token *token;

  setup_lexical_analyser();
  while(1) {
    token = get_next_token();
    printf("[Classe: %d, Valor: %s]\n", token->class, token->value);
  }
  return 0;
}
