#include "PIG.h"
#include "CPigForm.h"
#include "CPigComponente.h"
#include "CPigBotao.h"
#include "CPigCaixaTexto.h"
#include "CPigCheckBox.h"

PIG_Evento evento;          //evento ser tratadoi a cada pssada do loop principal
PIG_Teclado meuTeclado;     //vari�vel como mapeamento do teclado

int main( int argc, char* args[] ){

    //criando o jogo (aplica��o)
    CriaJogo("Meu Jogo");

    //associando o teclado (basta uma �nica vez) com a vari�vel meuTeclado
    meuTeclado = GetTeclado();

    //loop principal do jogo
    while(JogoRodando()){

        //pega um evento que tenha ocorrido desde a �ltima passada do loop
        evento = GetEvento();

        //aqui o evento deve ser tratado e as coisas devem ser atualizadas

        //ser� feita aprepa��o do frame que ser� exibido na tela
        IniciaDesenho();

        //todas as chamadas de desenho devem ser feitas aqui na ordem desejada

        //o frame totalmente pronto ser� mostrado na tela
        EncerraDesenho();
    }

    //o jogo ser� encerrado
    FinalizaJogo();

    return 0;
}

