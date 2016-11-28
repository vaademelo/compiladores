#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "lex.h"
#include "lex_setup.h"
#include "sint.h"
#include "symbol_table.h"
#include "scope.h"
#include "sem.h"

FILE * output_file;
Stack_node* last_operand  = NULL;
Stack_node* last_operator = NULL;

int memory_address     = 512;
int while_counter      = 0;
int while_end_counter  = 0;
int if_counter         = 0;
int else_counter       = 0;

int symbol_counter     = 0;
int temporary_var_conter = 0;

char current_subroutine_call_lexeme[MAX_TOKEN_VALUE_SIZE]; 
char current_variable_lexeme[MAX_TOKEN_VALUE_SIZE]; 
int  current_variable_relative_position; 


// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// -  F U N C O E S   A U X I L I A R E S  -
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


// =-=-=-=-=-=-=-=-= G E R E N C I A M E N T O  D E  " P I L H A "

Stack_node* pop(Stack_node* node, int stack) {

  if (node == NULL) {
    printf("=-=-=-=-=-=-=-=- Erro: Pilha vazia\n");
    return NULL;
  }

  if (node->next_node == NULL && stack == OPERAND_STACK)  last_operand = node->previous_node;
  if (node->next_node == NULL && stack == OPERATOR_STACK) last_operator = node->previous_node;


  if (node->previous_node == NULL && node->next_node == NULL && stack == OPERATOR_STACK) {
    last_operator = NULL;
  
  } else if (node->previous_node == NULL && node->next_node == NULL && stack == OPERATOR_STACK) {
    last_operator = NULL;
  
  } else if (node->previous_node == NULL) {
    node->next_node->previous_node = NULL;  
  
  } else if (node->next_node == NULL) {
    node->previous_node->next_node = NULL;
  
  } else {
    node->previous_node->next_node = node->next_node;
    node->next_node->previous_node = node->previous_node;  
  }
  
  return node; 
}

void push_operand(char* lexeme[MAX_TOKEN_VALUE_SIZE], int type) {
  Stack_node* new_operand = malloc(sizeof(Stack_node));

  new_operand->previous_node = last_operand;
  new_operand->next_node = NULL;
  new_operand->type = type;
  strcpy(new_operand->lexeme, lexeme);

  last_operand = new_operand;
}

void push_operator(char* lexeme[MAX_TOKEN_VALUE_SIZE]) {
  Stack_node* new_operator = malloc(sizeof(Stack_node));

  new_operator->previous_node = last_operator;
  new_operator->next_node = NULL;
  strcpy(new_operator->lexeme, lexeme);

  last_operator = new_operator;
}

bool is_operator_stack_empty() {
  return (last_operator == NULL);
}

// =-=-=-=-=-=-=-=-= P R E C E D E N C I A   D E   O P E R A D O R E S

bool is_higher_precedence(char* operator1[MAX_TOKEN_VALUE_SIZE], char* operator2[MAX_TOKEN_VALUE_SIZE]) {
  if ((strcmp(operator1, "*") == 0 || strcmp(operator1, "/") == 0) 
   && (strcmp(operator2, "+") == 0 || strcmp(operator2, "+") == 0)) {
    return true;
  
  } 

  if (strcmp(operator1, "||") == 0 || strcmp(operator1, "&&") == 0) {
    return true;
  }

  return false;

}

bool is_logic_operator(char* operator[MAX_TOKEN_VALUE_SIZE]){
  if(strcmp(operator, "==") == 0) return true;
  if(strcmp(operator, "!=") == 0) return true;
  if(strcmp(operator, ">")  == 0) return true;
  if(strcmp(operator, ">=") == 0) return true;
  if(strcmp(operator, "<")  == 0) return true;
  if(strcmp(operator, "<=") == 0) return true;

  return false;
}

// =-=-=-=-=-=-=-=-= G E R E N C I A M E N T O   D E   E S C O P O

// TIPOS: Definidos em 'scope.h'

void new_scope(int type) {
  create_scope(type);
}

void leave_scope(void) {
  pop_scope();
}

bool is_new_scope(Token *token, int machine, int state) {

  return (
    (machine == P_MACHINE && state == 4 && strcmp(token->value, "{") == 0)
    || (machine == CMD_MACHINE && state == 30 && strcmp(token->value, "{") == 0)
    || (machine == CMD_MACHINE && state == 36 && strcmp(token->value, "{") == 0)
  );
}

bool is_end_of_scope(Token *token, int machine, int state) {
  return (
       (machine == P_MACHINE && state == 6  && strcmp(token->value, "}") == 0)
    || (machine == P_MACHINE && state == 14 && strcmp(token->value, "}") == 0)
    || (machine == CMD_MACHINE && state == 13 && strcmp(token->value, "}") == 0)
    || (machine == CMD_MACHINE && state == 31 && strcmp(token->value, "}") == 0)
    || (machine == CMD_MACHINE && state == 37 && strcmp(token->value, "}") == 0)
  );
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// -  G E R A C A O   D E   C O D I G O  -
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


// =-=-=-=-=-=-=-=-= C A B E C A L H O   D O   C O D I G O   G E R A D O

void start_code(void) {
  fprintf(output_file, "MAIN JP /0000\n");
  fflush(output_file);
  
  memory_address += 2;
}

// =-=-=-=-=-=-=-=-= R O D A P E   D O   C O D I G O   G E R A D O

// Imprime o final fisico do codigo
void end_code(void) {
  fprintf(output_file, "HM /00\n");
  fprintf(output_file, "#  P\n");
  fflush(output_file);

  memory_address += 4;
}

// =-=-=-=-=-=-=-=-= D E C L A R A C A O   D E   F U N C A O 

void function_declaration(Token *token) {
  fprintf(output_file, "\n; ** Subrotina %s\n", token->value);
  fprintf(output_file, "%s JP /0000 ; Guarda o endereco de retorno para a rotina anterior\n", token->value);
  fflush(output_file);
 
  new_scope(FUNC_SCOPE);
}

// =-=-=-=-=-=-=-=-= L A C O   ' E N Q U A  N T O '

void while_initialize() {
  fprintf(output_file, "\nENQUANTO%02d LD /0000\n", while_counter);
  fflush(output_file);

  while_end_counter = while_counter;
  while_counter++;
}

void while_escape() {
  fprintf(output_file, "<calcula EXP_B>\n");
  fprintf(output_file, "JN FIM_ENQUANTO%02d\n", while_end_counter);
  fprintf(output_file, "JZ FIM_ENQUANTO%02d\n", while_end_counter);
  fflush(output_file);  
}

void while_finalize() {
  fprintf(output_file, "\nJP ENQUANTO%02d\n", while_end_counter);
  fprintf(output_file, "FIM_ENQUANTO%02d\n", while_end_counter);
  fflush(output_file);
  
}

// =-=-=-=-=-=-=-=-= C O N D I C O N A L  ' S E '

void if_initialize() {
  fprintf(output_file, "\nSE%02d LD /0000\n", if_counter);
  fflush(output_file);

  else_counter = if_counter;
  if_counter++;
}

void if_escape() {
  fprintf(output_file, "<calcula EXP_B>\n");
  fprintf(output_file, "JN FIM_SE%02d\n", else_counter);
  fprintf(output_file, "JZ FIM_SE%02d\n", else_counter);
  fflush(output_file);  
}

void if_finalize() {
  fprintf(output_file, "FIM_SE%02d\n", else_counter);
  fflush(output_file);
}

// =-=-=-=-=-=-=-=-= C O N D I C O N A L  ' E L S E  '

void else_initialize() {
  fprintf(output_file, "JP FIM_SENAO%02d\n", else_counter);
  fprintf(output_file, "FIM_SE%02d\n", else_counter);
  fflush(output_file);
}

void else_finalize() {
  fprintf(output_file, "FIM_SENAO%02d\n", else_counter);
  fflush(output_file);
}

// =-=-=-=-=-=-=-=-= G E R E N C I A M E N T O  D O  R E G I S T R O  D E  A T I V A C A O

void frame_initialize() {
  fprintf(output_file, "; Criando novo quadro para a chamada da subrotina.\n");
  fprintf(output_file, "SC CRIAR_QUADRO\n");
  fflush(output_file); 
}

void insert_parameter_into_frame(Token* token) {
  fprintf(output_file, "\n; Inserindo argumento %d no quadro.\n", symbol_counter);
  fprintf(output_file, "LV <%s>\n", token->value);
  fprintf(output_file, "MM VAR_VALOR\n");
  fprintf(output_file, "LV %d\n", symbol_counter);
  fprintf(output_file, "MM VAR_DESLOCAMENTO\n");
  fprintf(output_file, "SC INSERIR_VAR_NO_QUADRO\n");
  fflush(output_file); 
}

void frame_finalize(char lexeme[MAX_TOKEN_VALUE_SIZE]) {
  fprintf(output_file, "SC %s\n", lexeme);
  fflush(output_file); 
}

void value_attribution() {
  fprintf(output_file, "\n; Inserindo valor da variavel (%s) no quadro\n", current_variable_lexeme);
  fprintf(output_file, "<CALCULA EXP_A>\n");
  fprintf(output_file, "MM VAR_VALOR\n");
  fprintf(output_file, "LV =%d\n", current_variable_relative_position);
  fprintf(output_file, "MM VAR_DESLOCAMENTO\n");
  fprintf(output_file, "SC INSERIR_VAR_NO_QUADRO\n");
  fflush(output_file);  
}

void load_value_from_frame(char lexeme[MAX_TOKEN_VALUE_SIZE]) {
  fprintf(output_file, "\n; Lendo valor da variavel (%s) do quadro\n", lexeme);
  fprintf(output_file, "LV =%d\n", lookup_symbol(lexeme)->relative_position);
  fprintf(output_file, "MM VAR_DESLOCAMENTO\n");
  fprintf(output_file, "SC LER_VAR_DO_QUADRO\n");
  fflush(output_file);  
}

// =-=-=-=-=-=-=-=-=  E X P R E S S O E S

void expression_term(Stack_node* operand1, Stack_node* operand2, Stack_node* operator) {
  
  Symbol_table_row* aux_row = malloc(sizeof(Symbol_table_row));
  aux_row = lookup_symbol(operand2->lexeme);

  if (operand2->type == OPERAND_VAR && aux_row != NULL) {
    load_value_from_frame(operand2->lexeme);
  
  } if (operand2->type == OPERAND_VAR && aux_row == NULL) {
    fprintf(output_file, "LD %s\n", operand2->lexeme);
  
  } else {
    fprintf(output_file, "LV =%s\n", operand2->lexeme);  
  }
  
  fprintf(output_file, "MM T%d\n", temporary_var_conter);

  aux_row = lookup_symbol(operand1->lexeme);

  if (operand1->type == OPERAND_VAR && aux_row != NULL) {
    load_value_from_frame(operand1->lexeme);
  
  } if (operand1->type == OPERAND_VAR && aux_row == NULL) {
    fprintf(output_file, "LD %s\n", operand1->lexeme);
  
  } else {
    fprintf(output_file, "LV =%s\n", operand1->lexeme);  
  }

  fprintf(output_file, "%s  T%d\n", operator->lexeme, temporary_var_conter);
  fprintf(output_file, "MM T%d\n", temporary_var_conter);
  fflush(output_file);  
}

void recursive_expression_writer(Stack_node* operator, Stack_node* operand) {
  
  while (strcmp(last_operator->lexeme, "(") == 0) {
    last_operator = last_operator->previous_node;
  }

  if (operator->previous_node == NULL 
   || is_logic_operator(operator->previous_node->lexeme) 
   || strcmp(operator->previous_node->lexeme, "(")){
    expression_term(pop(operand->previous_node, OPERAND_STACK), pop(operand, OPERAND_STACK), pop(operator, OPERATOR_STACK));
    
    Stack_node* new_operand = malloc(sizeof(Stack_node));
    
    new_operand->previous_node = operand->next_node->previous_node;
    new_operand->next_node = operand->next_node;
    sprintf(new_operand->lexeme, "T%d", temporary_var_conter);
    temporary_var_conter++;
    
    operand->next_node->previous_node = new_operand;

    recursive_expression_writer(last_operator, last_operand);
  }

  if (is_higher_precedence(operator->previous_node->lexeme, operator->lexeme)) {
    expression_term(pop(operand->previous_node->previous_node, OPERAND_STACK), pop(operand->previous_node, OPERAND_STACK), pop(operator->previous_node, OPERATOR_STACK));

    Stack_node* new_operand = malloc(sizeof(Stack_node));
    
    new_operand->previous_node = operand->previous_node;
    new_operand->next_node = operand;
    sprintf(new_operand->lexeme, "T%d", temporary_var_conter);
    temporary_var_conter++;
    
    operand->previous_node = new_operand;

    recursive_expression_writer(last_operator, last_operand);
  }

  if(!is_operator_stack_empty()) {
    recursive_expression_writer(operator->previous_node, operand->previous_node);
  }
}

void generate_expression_code() {
  recursive_expression_writer(last_operator, last_operand);
}

// void greater_than() {
//   Operand* operand1 = pop_operand();
//   Operand* operand2 = pop_operand();

//   fprintf(output_file, "; %s > %s\n", operand1->lexeme, operand2->lexeme);

//   if (operand1->type == OPERAND_VAR) {
//     load_value_from_frame(operand1->lexeme);
  
//   } else {
//     fprintf(output_file, "LV =%s\n", operand1->lexeme);
//     fflush(output_file);
//   }

//   if (operand2->type == OPERAND_VAR) {
//     load_value_from_frame(operand2->lexeme);
  
//   } else {
//     fprintf(output_file, "-  =%s\n", operand2->lexeme);
//     fflush(output_file);
//   }
// }

void setup_semantic_analyzer(void) {
  output_file = fopen("output.asm", "w+");
  last_operator = malloc(sizeof(Stack_node));  
  last_operand  = malloc(sizeof(Stack_node));

  last_operator->previous_node = NULL;
  last_operator->next_node = NULL;
  last_operator->type = NULL;
  // last_operator->lexeme = NULL;

  last_operand->previous_node = NULL;
  last_operand->next_node = NULL;
  last_operand->type = NULL;
  // last_operand->lexeme = NULL;
}


// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// -  S E L E C A O   D E  A C O E S  S E M A N T I C A S   -
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void semantic_action(Token * token, int machine, int state) {
  
  bool is_leaving_scope = is_end_of_scope(token, machine, state);

  printf("(t: %s, tc: %d, m: %d, s: %d)\n", token->value, token->class, machine, state);

  if (machine == CMD_MACHINE && state == 1) { // Declaracao de variavel
    insert_symbol(token->value, 0, VAR, symbol_counter); 
    symbol_counter++;
  } 

  // *********************************
  // *  A T R I B U I C A O   D E   V A L O R 
  // ********************************

  if (machine == CMD_MACHINE && state == 2) {

    Symbol_table_row* aux_row = malloc(sizeof(Symbol_table_row));

    aux_row = lookup_symbol(token->value);

    if (aux_row == NULL) {
      printf("\n\n** Erro Semantico **\n");
      printf("--------------------\n");
      printf("input.txt[%d:%d] ~> A variavel '%s' deve ser declarada antes de receber um valor.\n\n", token->line, token->column, token->value);
      exit(0);
    } else {

      strcpy(current_variable_lexeme, token->value);
      current_variable_relative_position = aux_row->relative_position;

    }
  }

  // Inserindo variavel no quadro
  if ((machine == EXP_A_MACHINE && state == 2 && strcmp(current_variable_lexeme, "_NULL") != 0)
   || (machine == CMD_MACHINE && state == 11 && strcmp(current_variable_lexeme, "_NULL") != 0)) {
    // getchar();
    value_attribution();
    strcpy(current_variable_lexeme, "_NULL");
  }  


  // *********************************
  // *  D E C L A R A C A O   D E   S U B R O T I N A 
  // ********************************

  // Inserir o lexema da funcao na tabela de simbolos
  if (machine == P_MACHINE && state == 2) {
    insert_symbol(token->value, 0, FUNC, NULL);
    function_declaration(token);
    symbol_counter = 0;
  }


  if ((machine == P_MACHINE && state == 7 && strcmp(token->value, ")") != 0)
   || (machine == P_MACHINE && state == 24)) {
    insert_symbol(token->value, 0, VAR, symbol_counter); 
    symbol_counter++;
  } 

  // *********************************
  // *  I F   -   T H E N
  // *********************************

  // Inicializando o 'if'
  if ((machine == CMD_MACHINE && state == 13 && strcmp(token->value, "se") == 0)
   || (machine == CMD_MACHINE && state == 31 && strcmp(token->value, "se") == 0) 
   || (machine == CMD_MACHINE && state == 37 && strcmp(token->value, "se") == 0) 
   || (machine == CMD_MACHINE && state == 38 && strcmp(token->value, "se") == 0)) {
    if_initialize();
    new_scope(IF_SCOPE);
  }

  // Gerar o código responsável por escapar do 'then' caso a expressão seja falso
  if (current_scope->type == IF_SCOPE
   && machine == EXP_A_MACHINE 
   && state == 2 && strcmp(token->value, ")") == 0) {
    if_escape();
  }

  // Se estiver saindo de um contexto de 'if' entao decrementa else_counter
  if (is_leaving_scope 
   && current_scope->type == IF_SCOPE 
   && (lookahead(1) == NULL || strcmp(lookahead(1)->value, "senao") != 0)) {

    if_finalize();
    else_counter--;

    leave_scope();
  }

  // *********************************
  // *  E L S E
  // *********************************

  // Finalizando o 'if' e inicializa o 'else'
  if (machine == CMD_MACHINE && state == 38 && strcmp(token->value, "senao") == 0) {
    else_initialize();
    new_scope(ELSE_SCOPE);
  }

  // Se estiver saindo de um contexto de 'else' entao decrementa else_counter
  if (is_leaving_scope && current_scope->type == ELSE_SCOPE) {
    else_finalize();
    else_counter--;

    leave_scope();
  }

  // *********************************
  // *  W H I L E 
  // *********************************

  // Inicializando o 'while'
  if ((machine == CMD_MACHINE && state == 13 && strcmp(token->value, "enquanto") == 0)
   || (machine == CMD_MACHINE && state == 31 && strcmp(token->value, "enquanto") == 0)) {
    while_initialize();
    new_scope(WHILE_SCOPE);
  }

  // Gerar o código responsável por escapar do 'while' caso a expressão seja falsa
  if (current_scope->type == WHILE_SCOPE
   && machine == EXP_A_MACHINE 
   && state == 2 && strcmp(token->value, ")") == 0) {
    while_escape();
  }

  // Se estiver saindo de um contexto de 'while' entao decrementa while
  if (is_leaving_scope && current_scope->type == WHILE_SCOPE) {
    while_finalize();
    while_end_counter--;

    leave_scope();
  }

  // *********************************
  // *  C H A M A D A   S U B F U N C A O
  // *********************************
  
  // Inicializando Frame
  if (machine == CMD_MACHINE && state == 24 && token->class == 6 && strcmp(lookahead(1)->value, "(") == 0) {
    frame_initialize();
    strcpy(current_subroutine_call_lexeme, token->value);
    symbol_counter = 0;
  }  

  // Inserindo valor dos parametros no quadro
  if ((machine == EXP_A_MACHINE && state == 6)
   || (machine == EXP_A_MACHINE && state == 25)) {
    
    insert_parameter_into_frame(token);
    symbol_counter++;

    // Finalizando criacao do frame apos o ultimo argumento
    if(strcmp(lookahead(1)->value, ")") == 0) {
      frame_finalize(current_subroutine_call_lexeme);
      strcpy(current_subroutine_call_lexeme, "_NULL");
    }
  }

  // *********************************
  // *  E X P R E S S O E S  A R I T M E T I C A S
  // *********************************  

  // if (machine == CMD_MACHINE 
  //  && (state == 27  || state == 34)
  //  && token->class == 6
  //  && strcmp(lookahead(1)->value, "(") != 0
  //  && strcmp(lookahead(1)->value, "[") != 0
  //  && strcmp(lookahead(1)->value, ".") != 0) {
  //   push_operand(token->value, OPERAND_VAR);
  //   getchar();
  // }

  if ((machine == CMD_MACHINE && state == 27 && (token->class == 1 || token->class == 6))
   || (machine == CMD_MACHINE && state == 34 && (token->class == 1 || token->class == 6))
   || (machine == EXP_A_MACHINE && state == 0 && (token->class == 1 || token->class == 6))
   || (machine == EXP_A_MACHINE && state == 3 && (token->class == 1 || token->class == 6))
   || (machine == EXP_A_MACHINE && state == 8 && (token->class == 1 || token->class == 6))
   || (machine == EXP_A_MACHINE && state == 15 && (token->class == 1 || token->class == 6))
   || (machine == EXP_B_MACHINE && state == 0 && (token->class == 1 || token->class == 6))
   || (machine == EXP_B_MACHINE && state == 3 && (token->class == 1 || token->class == 6))) {
    push_operand(token->value, OPERAND_VAR);
  getchar();
  }

  // if (machine == EXP_A_MACHINE 
  // && (state == 1 || state == 2 || state == 10 || state == 11 || state == 17 || state == 18 || state == 20 || state == 22 || state == 31 || state == 33 || state == 39 || state == 41)) {
    
  //   if (strcmp(token->value, "%") == 0 || strcmp(token->value, "^") == 0) {
  //     printf("\n\n** Erro na Geracao de Codigo **\n");
  //     printf("--------------------\n");
  //     printf("input.txt[%d:%d] ~> Infelizmente a operacao '%s' nao foi implementada. Por favor aguarde as proximas versoes. :P\n\n", token->line, token->column, token->value);
  //     exit(0);
  //   } else {
  // }
}
