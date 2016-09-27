#!/bin/sh
echo "Compilando analisador lexico..."

gcc main.c lex.c next_state.c token_classifier.c lex_setup.c -o output -w

echo "Arquivo 'output' criado com sucesso"
echo "Executando o resultado da compilação...\n"
echo "-------------"

./output
