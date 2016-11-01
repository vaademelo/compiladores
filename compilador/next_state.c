#include <stdio.h>
#include "lex.h"
#include "next_state.h"
#include "sint_setup.h"

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
  } else if (character == 34) {
    return 15; // '"'
  } else if (character == 58) {
    return 16; // ':'
  } else if (character == 124) {
    return 17; // '|'
  } else {
    return 11;
  }
}

int get_next_state(int character, int current_state) {
  int character_received_group = get_character_group(character);
  return next_state_table[current_state][character_received_group];
}

int get_next_state_exp_a_machine(Token *token, int current_state){
  int next_state = -1;

  if (token->class == 6){
    next_state = exp_a->states_table[current_state][0];

  } else if (token->class == 1 || token->class == 2){
    next_state = exp_a->states_table[current_state][1];

  } else if (strcmp(token->value, "(") == 0){
    next_state = exp_a->states_table[current_state][2];

  } else if (strcmp(token->value, ")") == 0){
    next_state = exp_a->states_table[current_state][3];

  } else if (strcmp(token->value, "[") == 0){
    next_state = exp_a->states_table[current_state][4];

  } else if (strcmp(token->value, "]") == 0){
    next_state = exp_a->states_table[current_state][5];

  } else if (strcmp(token->value, ".") == 0){
    next_state = exp_a->states_table[current_state][6];

  } else if (strcmp(token->value, "^") == 0){
    next_state = exp_a->states_table[current_state][7];

  } else if (strcmp(token->value, "-") == 0){
    next_state = exp_a->states_table[current_state][8];

  } else if (strcmp(token->value, "*") == 0){
    next_state = exp_a->states_table[current_state][9];

  } else if (strcmp(token->value, "/") == 0){
    next_state = exp_a->states_table[current_state][10];

  } else if (strcmp(token->value, "\%") == 0){
    next_state = exp_a->states_table[current_state][11];

  } else if (strcmp(token->value, "+") == 0){
    next_state = exp_a->states_table[current_state][12];

  } else if (token->class == 1){
    next_state = exp_a->states_table[current_state][13];

  } else if (strcmp(token->value, ",") == 0){
    next_state = exp_a->states_table[current_state][14];

  }

  return next_state;
}

int get_next_state_exp_b_machine(Token *token, int current_state){

  int next_state = -1;

  if (strcmp(token->value, "!") == 0) {
    next_state = exp_b->states_table[current_state][0];

  } else if (strcmp(token->value, "VERDADEIRO") == 0) {
    next_state = exp_b->states_table[current_state][1];

  } else if (strcmp(token->value, "FALSO") == 0){
    next_state = exp_b->states_table[current_state][2];

  }  else if (strcmp(token->value, "(") == 0){
    next_state = exp_b->states_table[current_state][3];

  } else if (strcmp(token->value, ")") == 0){
    next_state = exp_b->states_table[current_state][4];

  } else if (strcmp(token->value, ">") == 0){
    next_state = exp_b->states_table[current_state][5];

  } else if (strcmp(token->value, ">=") == 0){
    next_state = exp_b->states_table[current_state][6];

  } else if (strcmp(token->value, "<") == 0){
    next_state = exp_b->states_table[current_state][7];

  } else if (strcmp(token->value, "<=") == 0){
    next_state = exp_b->states_table[current_state][8];

  } else if (strcmp(token->value, "==") == 0){
    next_state = exp_b->states_table[current_state][9];

  } else if (strcmp(token->value, "!=") == 0){
    next_state = exp_b->states_table[current_state][10];

  } else if (strcmp(token->value, "||") == 0){
    next_state = exp_b->states_table[current_state][11];

  } else if (strcmp(token->value, "&&") == 0){
    next_state = exp_b->states_table[current_state][12];

  }

  return next_state;
}

int get_next_state_p_machine(Token *token, int current_state){
  int next_state = -1;

  if (strcmp(token->value, "deftipo") == 0){
    next_state = p->states_table[current_state][0];

  } else if (strcmp(token->value, "func") == 0){
    next_state = p->states_table[current_state][1];

  } else if (token->class == 6){
    next_state = p->states_table[current_state][2];

  } else if (strcmp(token->value, "(") == 0){
    next_state = p->states_table[current_state][3];

  } else if (strcmp(token->value, ")") == 0){
    next_state = p->states_table[current_state][4];

  } else if (strcmp(token->value, ":") == 0){
    next_state = p->states_table[current_state][5];

  } else if (strcmp(token->value, "inteiro") == 0){
    next_state = p->states_table[current_state][6];

  } else if (strcmp(token->value, "flutuante") == 0){
    next_state = p->states_table[current_state][7];

  } else if (strcmp(token->value, "caracter") == 0){
    next_state = p->states_table[current_state][8];

  } else if (strcmp(token->value, "vazio") == 0){
    next_state = p->states_table[current_state][9];

  } else if (strcmp(token->value, "[") == 0){
    next_state = p->states_table[current_state][10];

  } else if (strcmp(token->value, "]") == 0){
    next_state = p->states_table[current_state][11];

  } else if (strcmp(token->value, ",") == 0){
    next_state = p->states_table[current_state][12];

  } else if (token->class == 1){
    next_state = p->states_table[current_state][13];

  } else if (strcmp(token->value, "{") == 0){
    next_state = p->states_table[current_state][14];

  } else if (strcmp(token->value, "}") == 0){
    next_state = p->states_table[current_state][15];

  } else if (strcmp(token->value, "registro") == 0){
    next_state = p->states_table[current_state][16];

  } else if (strcmp(token->value, ";") == 0){
    next_state = p->states_table[current_state][17];

  }

  return next_state;
}

int get_next_state_cmd_machine(Token *token, int current_state){
  int next_state = -1;

  if (strcmp(token->value, "seja") == 0){
    next_state = cmd->states_table[current_state][0];

  } else if (token->class == 6){
    next_state = cmd->states_table[current_state][1];

  } else if (strcmp(token->value, "se") == 0){
    next_state = cmd->states_table[current_state][2];

  } else if (strcmp(token->value, "enquanto") == 0){
    next_state = cmd->states_table[current_state][3];

  } else if (strcmp(token->value, "ler") == 0){
    next_state = cmd->states_table[current_state][4];

  } else if (strcmp(token->value, "imprimir") == 0){
    next_state = cmd->states_table[current_state][5];

  } else if (strcmp(token->value, "[") == 0){
    next_state = cmd->states_table[current_state][6];

  } else if (strcmp(token->value, "]") == 0){
    next_state = cmd->states_table[current_state][7];

  } else if (strcmp(token->value, ".") == 0){
    next_state = cmd->states_table[current_state][8];

  } else if (strcmp(token->value, ":=") == 0){
    next_state = cmd->states_table[current_state][9];

  } else if (strcmp(token->value, "(") == 0){
    next_state = cmd->states_table[current_state][10];

  } else if (strcmp(token->value, ")") == 0){
    next_state = cmd->states_table[current_state][11];

  } else if (strcmp(token->value, "um") == 0){
    next_state = cmd->states_table[current_state][12];

  } else if (strcmp(token->value, "\"") == 0){
    next_state = cmd->states_table[current_state][13];

  } else if (strcmp(token->value, "inteiro") == 0){
    next_state = cmd->states_table[current_state][14];

  } else if (strcmp(token->value, "flutuante") == 0){
    next_state = cmd->states_table[current_state][15];

  } else if (strcmp(token->value, "caracter") == 0){
    next_state = cmd->states_table[current_state][16];

  } else if (strcmp(token->value, "vazio") == 0){
    next_state = cmd->states_table[current_state][17];

  } else if (token->class == 3){
    next_state = cmd->states_table[current_state][18];

  } else if (strcmp(token->value, ";") == 0){
    next_state = cmd->states_table[current_state][19];

  } else if (token->class == 1){
    next_state = cmd->states_table[current_state][20];

  } else if (strcmp(token->value, "{") == 0){
    next_state = cmd->states_table[current_state][21];

  } else if (strcmp(token->value, "}") == 0){
    next_state = cmd->states_table[current_state][22];

  } else if (strcmp(token->value, "senao") == 0){
    next_state = cmd->states_table[current_state][23];

  } else if (strcmp(token->value, "senaose") == 0){
    next_state = cmd->states_table[current_state][24];

  } else if (strcmp(token->value, "torne") == 0){
    next_state = cmd->states_table[current_state][25];

  }

  return next_state;
}
