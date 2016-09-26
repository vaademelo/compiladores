#define MAX_NEXT_STATE_TABLE 20
#define MAX_BUFFER_SIZE 50

typedef struct {
  int class;
  char repr[MAX_BUFFER_SIZE];
} Token_type;

void get_next_token(void);
