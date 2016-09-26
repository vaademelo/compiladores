#include <stdio.h>
#include "lex.h"
#include "next_state.h"

int get_character_group (int character) {
  if (character >= 97 && character <= 122) {
    return 0; // a...z
  } else if (character >= 65 && character <= 90) {
    return 1; // A...Z
  } else if (character >= 48 && character <= 57) {
    return 2; // 0...9
  } else if (character == 62) {
    return 3; // >
  } else if (character == 60) {
    return 4; // <
  } else if (character == 61) {
    return 5; // =
  } else if (character == 33) {
    return 6; // !
  } else if (character == 38) {
    return 7; // &
  } else if (character == 47) {
    return 8; // /
  } else if (character == 46) {
    return 9; // .
  } else if (character == 42) {
    return 10; // *
  } else if (character == 32) {
    return 13; // ' '
  } else if (character == 13 || character == 10) {
    return 14; // EOL
  } else {
    return 11;
  }
}

int get_next_state(int character, int current_state) {
  int character_received_group = get_character_group(character);
  return next_state_table[current_state][character_received_group];
}
