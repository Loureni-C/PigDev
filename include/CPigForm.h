#ifndef _PIGFORM_
#define _PIGFORM_

#include "CPigComponente.h"
#include "CPigBotao.h"
#include "CPigScrollBar.h"
#include "CPigCaixaTexto.h"
#include "CPigCampoTextoESenha.h"
#include "CPigAreaDeTexto.h"
#include "CPigItemCheck.h"
#include "CPigBox.h"
#include "CPigRadioBox.h"
#include "CPigCheckBox.h"
#include "CPigItemLista.h"
#include "CPigLista.h"
#include "CPigDropDown.h"
#include "CPigGauge.h"
#include "CPigGaugeCircular.h"

class CPigForm{

private:

int id;
int x,y,alt,larg;


public:

CPigForm(int idForm, int xForm, int yForm, int altForm, int largForm){
    id = idForm;
    x = xForm;
    y = yForm;
    alt = altForm;
    larg = largForm;
}

~CPigForm(){
}

int TrataEvento(PIG_Evento evento){

}

int Desenha(){

}

};


typedef CPigForm *PigForm;
#endif // _PIGFORM_
