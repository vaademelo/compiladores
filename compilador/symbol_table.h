typedef struct symbol_table_row{
  
  struct symbol_table_row * next_row;

  char lexeme[MAX_TOKEN_VALUE_SIZE];
  int  class;
  int  type;
  int  relative_position;

} Symbol_table_row;

typedef struct three_node{
  
  struct three_node* parent_symbol_table;
  Symbol_table_row* first_row;

} Symbol_table;

void insert_symbol(char lexeme[MAX_TOKEN_VALUE_SIZE], int class, int type, int relative_position);

Symbol_table_row* lookup_symbol(char lexeme[MAX_TOKEN_VALUE_SIZE]);

Symbol_table* create_symbol_table();