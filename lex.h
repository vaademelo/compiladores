#define MAX_NEXT_STATE_TABLE_SIZE 20
#define MAX_TOKEN_VALUE_SIZE 50

extern int next_state_table[MAX_NEXT_STATE_TABLE_SIZE][MAX_NEXT_STATE_TABLE_SIZE];
extern FILE *input_file;;

typedef struct {
  int class;
  char value[MAX_TOKEN_VALUE_SIZE];
} Token;

Token* get_next_token(void);
