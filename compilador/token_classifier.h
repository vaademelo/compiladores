#define MAX_TOKEN_VALUE_SIZE 50

#define COMENTARIO 0
#define INTEIRO 1
#define FLUTUANTE 2
#define STRING 3
#define SIMBOLO_ESPECIAL 4
#define PALAVRA_RESERVADA 5
#define IDENTIFICADOR 6
#define TIPO 7

int classify_token(int previous_state, int current_state, char buffer[MAX_TOKEN_VALUE_SIZE]);
