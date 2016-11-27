#define GLOBAL_SCOPE 0
#define WHILE_SCOPE  1
#define IF_SCOPE     2
#define ELSEIF_SCOPE 3
#define ELSE_SCOPE   4
#define FUNC_SCOPE   5

typedef struct stack{
  
  struct stack* previous_scope;
  struct stack* next_scope;

  int type;
  Symbol_table* symbol_table;

} Scope;

extern Scope* current_scope;

void push_scope(Scope *scope);

Scope* pop_scope();

void create_scope(int type);

void setup_scopes(void);