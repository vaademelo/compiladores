#define OPERAND_VAR  0
#define OPERAND_FUNC 1
#define OPERAND_NUMB 2

typedef struct operand {
  
  operand* previous_operand;
  operand* next_operand;

  char* lexeme[MAX_TOKEN_VALUE_SIZE];
  int   type; // Tipo de operando
} Operand;

extern Operand* operand_stack;
extern FILE *output_file;

void semantic_action(Token *token, int machine, int state);

void setup_semantic_analyzer(void);