#!/bin/sh
echo "Compilando..."

gcc main.c sint_setup.c sint.c lex.c next_state.c token_classifier.c lex_setup.c symbol_table.c sem.c scope.c -o output -w &&

echo "Arquivo 'output' criado com sucesso" &&
echo "Executando o resultado da compilação...\n" &&
echo "-------------\n\n" &&

./output
