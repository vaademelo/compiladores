#define MAX_RESERVED_WORDS_LIST_SIZE 50
#define MAX_RESERVED_WORD_SIZE 50

typedef struct {
  int length;
  char items[MAX_RESERVED_WORDS_LIST_SIZE][MAX_RESERVED_WORD_SIZE];
} List;

extern List *reserved_words_list;

extern List *types_list;

void setup_lexical_analizer(void);
