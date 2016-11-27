
; ** Subrotina imprimeAutor
imprimeAutor JP /0000 ; Guarda o endereco de retorno para a rotina anterior

; Inserindo valor da variavel (olivaras) no quadro
<CALCULA EXP_A>
MM VAR_VALOR
LV =3
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

; Lendo valor da variavel (i) do quadro
LV =0
MM VAR_DESLOCAMENTO
SC LER_VAR_DO_QUADRO
<calcula EXP_B>
JN FIM_ENQUANTO00
JZ FIM_ENQUANTO00

ENQUANTO01 LD /0000

; Lendo valor da variavel (i) do quadro
LV =0
MM VAR_DESLOCAMENTO
SC LER_VAR_DO_QUADRO
<calcula EXP_B>
JN FIM_ENQUANTO01
JZ FIM_ENQUANTO01

JP ENQUANTO01
FIM_ENQUANTO01

SE00 LD /0000

; Lendo valor da variavel (i) do quadro
LV =0
MM VAR_DESLOCAMENTO
SC LER_VAR_DO_QUADRO
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

SE01 LD /0000

; Lendo valor da variavel (i) do quadro
LV =0
MM VAR_DESLOCAMENTO
SC LER_VAR_DO_QUADRO
<calcula EXP_B>
JN FIM_SE01
JZ FIM_SE01

; Inserindo valor da variavel (i) no quadro
<CALCULA EXP_A>
MM VAR_VALOR
LV =0
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO
FIM_SE01

SE02 LD /0000

; Lendo valor da variavel (i) do quadro
LV =0
MM VAR_DESLOCAMENTO
SC LER_VAR_DO_QUADRO
<calcula EXP_B>
JN FIM_SE02
JZ FIM_SE02
JP FIM_SENAO02
FIM_SE02
FIM_SENAO02
FIM_SE01

SE03 LD /0000

; Lendo valor da variavel (i) do quadro
LV =0
MM VAR_DESLOCAMENTO
SC LER_VAR_DO_QUADRO
<calcula EXP_B>
JN FIM_SE03
JZ FIM_SE03
JP FIM_SENAO03
FIM_SE03
FIM_SENAO03

; Inserindo valor da variavel (i) no quadro
<CALCULA EXP_A>
MM VAR_VALOR
LV =0
MM VAR_DESLOCAMENTO
SC INSERIR_VAR_NO_QUADRO
FIM_SE02
FIM_SE01

JP ENQUANTO00
FIM_ENQUANTO00
