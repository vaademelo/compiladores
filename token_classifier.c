#include "token_classifier.h"

int classify_token(int previous_state, int current_state) {
  if (previous_state == 2) {
    return 0; // identifier
  } else if (previous_state == 3 || previous_state == 4) {
    return 1; // numero
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
    return 2; // simbolos especiais
  }
  return 0;
}
