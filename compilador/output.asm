
; ** Subrotina imprimeAutor
imprimeAutor JP /0000 ; Guarda o endereco de retorno para a rotina anterior

; Inserindo valor da variavel (olivaras) no quadro
<CALCULA EXP_A>
MM VAR_VALOR
LV =3
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO

; Inserindo argumento 4 no quadro.
LV <livro>
MM VAR_VALOR
LV 4
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO

; Inserindo argumento 5 no quadro.
LV <livro>
MM VAR_VALOR
LV 5
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO

; ** Subrotina principal
principal JP /0000 ; Guarda o endereco de retorno para a rotina anterior

; Inserindo valor da variavel (fundacao) no quadro
<CALCULA EXP_A>
MM VAR_VALOR
LV =2
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO

; Inserindo valor da variavel (fundacao) no quadro
<CALCULA EXP_A>
MM VAR_VALOR
LV =2
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO

; Inserindo valor da variavel (fundacao) no quadro
<CALCULA EXP_A>
MM VAR_VALOR
LV =2
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO

; Inserindo valor da variavel (hhgttg) no quadro
<CALCULA EXP_A>
MM VAR_VALOR
LV =1
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO

; Inserindo valor da variavel (hhgttg) no quadro
<CALCULA EXP_A>
MM VAR_VALOR
LV =1
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO

; Inserindo valor da variavel (hhgttg) no quadro
<CALCULA EXP_A>
MM VAR_VALOR
LV =1
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO

; Inserindo valor da variavel (i) no quadro
<CALCULA EXP_A>
MM VAR_VALOR
LV =0
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO

ENQUANTO00 LD /0000

; Inserindo argumento 3 no quadro.
LV <iguana>
MM VAR_VALOR
LV 3
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO

; Inserindo argumento 4 no quadro.
LV <iguana>
MM VAR_VALOR
LV 4
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO
SC 
<calcula EXP_B>
JN FIM_ENQUANTO00
JZ FIM_ENQUANTO00

ENQUANTO01 LD /0000

; Inserindo argumento 5 no quadro.
LV <i>
MM VAR_VALOR
LV 5
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO
<calcula EXP_B>
JN FIM_ENQUANTO01
JZ FIM_ENQUANTO01

; Inserindo argumento 6 no quadro.
LV <teste>
MM VAR_VALOR
LV 6
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO
SC _NULL

JP ENQUANTO01
FIM_ENQUANTO01

; Inserindo argumento 7 no quadro.
LV <i>
MM VAR_VALOR
LV 7
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO
<calcula EXP_B>
JN FIM_SE00
JZ FIM_SE00
; Criando novo quadro para a chamada da subrotina.
SC CRIAR_QUADRO

; Inserindo argumento 0 no quadro.
LV <tap>
MM VAR_VALOR
LV 0
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO

; Inserindo argumento 1 no quadro.
LV <flap>
MM VAR_VALOR
LV 1
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO

; Inserindo argumento 2 no quadro.
LV <larry>
MM VAR_VALOR
LV 2
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO
SC imprimeAutor

; Inserindo valor da variavel (i) no quadro
<CALCULA EXP_A>
MM VAR_VALOR
LV =0
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO
<calcula EXP_B>
JN FIM_SE00
JZ FIM_SE00

; Inserindo valor da variavel (i) no quadro
<CALCULA EXP_A>
MM VAR_VALOR
LV =0
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO
FIM_SE00

; Inserindo argumento 3 no quadro.
LV <i>
MM VAR_VALOR
LV 3
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO
<calcula EXP_B>
JN FIM_SE-1
JZ FIM_SE-1

; Inserindo argumento 4 no quadro.
LV <abobrinha>
MM VAR_VALOR
LV 4
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO
SC _NULL
JP FIM_SENAO-1
FIM_SE-1

; Inserindo argumento 5 no quadro.
LV <morango>
MM VAR_VALOR
LV 5
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO
SC _NULL
FIM_SENAO-1
FIM_SE-2

; Inserindo argumento 6 no quadro.
LV <i>
MM VAR_VALOR
LV 6
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO
<calcula EXP_B>
JN FIM_SE-3
JZ FIM_SE-3

; Inserindo argumento 7 no quadro.
LV <hhgttg>
MM VAR_VALOR
LV 7
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO
SC _NULL
JP FIM_SENAO-3
FIM_SE-3

; Inserindo argumento 8 no quadro.
LV <hhgttg>
MM VAR_VALOR
LV 8
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO
SC _NULL
FIM_SENAO-3

; Inserindo valor da variavel (i) no quadro
<CALCULA EXP_A>
MM VAR_VALOR
LV =0
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO

JP ENQUANTO00
FIM_ENQUANTO00
