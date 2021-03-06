//tipo de fun��o a ser usada no acionamento do botao
//o par�metro int devolver� � fun��o o identificador do bot�o
//o par�metro void* devolver� � fun��o um par�etro personalizado passado ao m�todo DefineAcao();
typedef int (*AcaoBotao)(int,void*);

class CPigBotao: public CPigComponente{

private:

    int tecla;
    int largFrame;
    AcaoBotao acao;
    void *param;
    Timer timer;
    bool botaoRepeticao;
    double tempoRepeticao;

    int TrataMouse(PIG_Evento evento){
        SDL_Point p;
        CMouse::PegaXY(p.x,p.y);
        MouseSobre(p.x,p.y);

        if(agoraOn){
            if (evento.mouse.acao==MOUSE_PRESSIONADO)
                return OnMouseClick();
        }

        return 0;
    }

    int TrataTeclado(PIG_Evento evento){
        if (evento.teclado.acao==TECLA_PRESSIONADA&&evento.teclado.tecla==tecla)
            if (timer->GetTempoDecorrido()>tempoRepeticao)
                return OnMouseClick();

        return 0;
    }

    void TrataTimer(){
        //if (timer->GetTempoDecorrido()<tempoRepeticao){
            //if(estado!=COMPONENTE_DESABILITADO)
            //    DefineEstado(COMPONENTE_ACIONADO);
        if (timer->GetTempoDecorrido()>=tempoRepeticao){
            if (estado==COMPONENTE_ACIONADO){
                if (agoraOn){
                    if (botaoRepeticao&&CMouse::GetEstadoBotaoEsquerdo()==MOUSE_PRESSIONADO){
                        OnMouseClick();
                    }else DefineEstado(COMPONENTE_MOUSEOVER);
                }else DefineEstado(COMPONENTE_NORMAL);
            }
        }
    }

    int OnMouseClick(){
        DefineEstado(COMPONENTE_ACIONADO);
        timer->Reinicia(false);
        if (acao) acao(id,param);//rever se NULL � necess�rio
        if (audioComponente>=0) CGerenciadorAudios::Play(audioComponente);
        return 1;
    }

    int OnMouseOn(){
        if (estado==COMPONENTE_DESABILITADO) return 0;
        DefineEstado(COMPONENTE_MOUSEOVER);
        return 1;
    }

    int OnMouseOff(){
        if (estado==COMPONENTE_DESABILITADO) return 0;
        DefineEstado(COMPONENTE_NORMAL);
        return 1;
    }

    CPigBotao LeArquivoParametros(std::string nomeArqParam){

        std::ifstream arquivo;
        int idComponente,px,py,altura,largura,retiraFundo = 0,janela = 0;

        std::string nomeArq = "",variavel,valor,palavra;

        arquivo.open(nomeArqParam);
        //if(!arquivo.is_open()) printf("falha ler arquivo\n");
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> palavra;
            if(palavra == "idComponente") arquivo >> idComponente;
            if(palavra == "px") arquivo >> px;
            if(palavra == "py") arquivo >> py;
            if(palavra == "altura") arquivo >> altura;
            if(palavra == "largura") arquivo >> largura;
            if(palavra == "nomeArq") arquivo >> nomeArq;
            if(palavra == "retiraFundo") arquivo >> retiraFundo;
            if(palavra == "janela") arquivo >> janela;
        }
        arquivo.close();

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;

        return CPigBotao(idComponente,px,py,altura,largura,nomeArq,retiraFundo,janela);
    }

public:

    CPigBotao(int idComponente,int px, int py, int alt,int larg,std::string nomeArq, int retiraFundo=1,int janela=0):
        CPigComponente(idComponente,px,py,alt,larg,nomeArq,retiraFundo,janela){
            tecla = -1;//sem tecla de atalho
            acao = NULL;//n�o tem a��o registrada
            param = NULL;//n�o tem par�metro associado � a��o
            largFrame = largOriginal/4;
            DefineEstado(COMPONENTE_NORMAL);
            tempoRepeticao = 0.2;
            botaoRepeticao = false;
            SetPosicaoPadraoLabel(PIG_COMPONENTE_CENTRO_CENTRO);
            timer = new CTimer(false);
        }

    CPigBotao(std::string nomeArqParam):CPigBotao(LeArquivoParametros(nomeArqParam)){
    }

    ~CPigBotao(){
        delete timer;
    }

    void DefineAcao(AcaoBotao funcao,void *parametro){
        acao = funcao;
        param = parametro;
    }

    void DefineAtalho(int teclaAtalho){
        tecla = teclaAtalho;
    }

    void DefineCursor(PIG_EstadoComponente estado, int indiceMouse){
        //mouse[estado]=indiceMouse;
    }

    void DefineTempoRepeticao(double segundos){
        tempoRepeticao = segundos;
    }

    void DefineBotaoRepeticao(bool repeticao){
        botaoRepeticao = repeticao;
    }

    void DefineEstado(PIG_EstadoComponente estadoComponente){
        SDL_Rect r={0,0,largFrame,altOriginal};
        estado = estadoComponente;
        switch(estado){
        case COMPONENTE_NORMAL:
            break;
        case COMPONENTE_MOUSEOVER:
            r.x += largFrame;
            break;
        case COMPONENTE_ACIONADO:
            r.x += 2*largFrame;
            break;
        case COMPONENTE_DESABILITADO:
            r.x += 3*largFrame;
            break;
        }
        DefineFrame(r);
    }

    int TrataEvento(PIG_Evento evento){
        if (estado == COMPONENTE_DESABILITADO || estado == COMPONENTE_INVISIVEL) return -1;
        if (evento.tipoEvento == EVENTO_MOUSE) return TrataMouse(evento);
        if (evento.tipoEvento == EVENTO_TECLADO) return TrataTeclado(evento);
        return 0;
    }

    int Desenha(){

        if (estado==COMPONENTE_INVISIVEL) return 0;

        TrataTimer();

        SDL_RenderCopyEx(renderer, text, &frame,&dest,-angulo,&pivoRelativo,flip);

        DesenhaLabel();
        EscreveHint();

        return 1;
    }

};

typedef CPigBotao *PigBotao;
