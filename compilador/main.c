#include <stdio.h>
#include "lex.h"
#include "lex_setup.h"
#include "sint_setup.h"
#include "sint.h"
#include "symbol_table.h"
#include "sem.h"

int main(void) {

  setup_lexical_analyser();
  setup_syntactic_analyser();
  setup_semantic_analyzer();
  setup_scopes();
  
  syntactic_analysis();

  return 0;
}
