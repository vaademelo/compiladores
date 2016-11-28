#define OPERAND_STACK  0
#define OPERATOR_STACK 1

#define OPERAND_VAR  0
#define OPERAND_FUNC 1
#define OPERAND_NUMB 2

typedef struct stack_node {
  
  struct stack_node* previous_node;
  struct stack_node* next_node;

  char* lexeme[MAX_TOKEN_VALUE_SIZE];
  int   type; 
} Stack_node;

extern Stack_node* last_operand;
extern Stack_node* last_operator;
extern FILE* output_file;

void semantic_action(Token *token, int machine, int state);

void setup_semantic_analyzer(void);