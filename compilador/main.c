#include <stdio.h>
#include <stdbool.h>
#include "lex.h"
#include "lex_setup.h"
#include "sint_setup.h"
#include "sint.h"
#include "symbol_table.h"
#include "scope.h"
#include "sem.h"

int main(void) {

  setup_lexical_analyser();
  setup_syntactic_analyser();
  setup_scopes();
  setup_semantic_analyzer();
  
  syntactic_analysis();

  return 0;
}
