typedef struct symbol_table_row{
  
  struct symbol_table_row * next_row;

  char name[MAX_TOKEN_VALUE_SIZE];
  int class;
  int type;

} Symbol_table_row;

typedef struct three_node{
  
  struct three_node * parent_scope;
  Symbol_table_row * symbol_table_first_row;

} Scope;

typedef struct tree {

  Scope * head; 

} Tree;

Tree * scopes_tree;
Scope * current_scope;

void setup_scopes(void);
void insert_symbol_table(Token *token, int type);
