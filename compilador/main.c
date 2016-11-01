#include <stdio.h>
#include "lex.h"
#include "lex_setup.h"
#include "sint_setup.h"
#include "sint.h"

int main(void) {

  setup_lexical_analizer();
  setup_syntactic_analizer();
  
  syntactic_analysis();

  return 0;
}
