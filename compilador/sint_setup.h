#define MAX_MACHINE_TABLE_SIZE 60

#define P_MACHINE 1
#define CMD_MACHINE 2
#define EXP_A_MACHINE 3
#define EXP_B_MACHINE 4

typedef struct {
  int id;
  int accepting_states[20];
  int states_table[MAX_MACHINE_TABLE_SIZE][MAX_MACHINE_TABLE_SIZE];
} Machine;

extern Machine *p;

extern Machine *cmd;

extern Machine *exp_a;

extern Machine *exp_b;

void setup_syntactic_analyser(void);
