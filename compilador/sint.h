#define P_MACHINE 1
#define CMD_MACHINE 2
#define EXP_A_MACHINE 3
#define EXP_B_MACHINE 4
#define STACK_SIZE 100

typedef struct {
  int machine;
  int state;
} stack_cell;

extern stack_cell *stack[STACK_SIZE];

void syntactic_analysis(void);
