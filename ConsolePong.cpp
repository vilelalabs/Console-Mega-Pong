/***********************************************************************
*                                                                      *
*  Jogo Mega Pong                                     Data 21/01/2018  *
*  Desenvolvido por: Henrique Leal Vilela                              *
*                                                                      *
*  Objetivo:                                                           *
*    Relembrar algumas pr?ticas b?sicas de programa??o e algor?tmos    *
*                                                                      *
*                                                                      *
*                                                                      *
************************************************************************/

// inclus?o de bibliotecas
#include <conio.h>
#include <iomanip.h>

// defini??o de constantes
// dimens?es totais de tela ?til
#define MAX_WIDTH 80
#define MAX_HEIGHT 24
//dimens?es da tela de jogo
#define MIN_WIDTH  4
#define MIN_HEIGHT 5

//-------------------------- VARIAVEIS GLOBAIS ------------------------------------------

//marcadores
int vidas = 3; int pontos = 0;

//---- PONG ----------------------------------
// indica a posi??o vertical do pong na tela
int pos_pong     = (MAX_HEIGHT/2); // inicia no centro vertical, pong ter? 5 'pixels'
int pos_anterior = pos_pong; // posi??o para apagar posi??o anterior

int comando = 0; // controle do pong

//---- BOLA ------------------------------------
//posicao inicial da bola
int pos_bola_x    = (MAX_WIDTH/2);  // inicia no centro horizontal
int pos_bola_y    = (MAX_HEIGHT/2); // inicia no centro vertical

// posi??o da bola para apagar posi??o anterior
int pos_bola_x_ant    = pos_bola_x;  // inicia no centro horizontal
int pos_bola_y_ant    = pos_bola_y; // inicia no centro vertical

//dire??o para onde a bola est? indo (definidos em atualiza bola)
// 0 =>  cima-esquerda  // 1 =>  cima-direita
// 2 => baixo-esquerda  // 3 => baixo-esquerda
int direcao_bola = 0;

//-------------- PROT?TIPOS DE FUN??ES --------------------------------------

//---- GERAIS ----------------------------
void setup();                                           // prepara??o da tela
void loop();                                            // loopping de jogo
void debug();                                           // para debug de dados
void main_window();                                     // janela principal
void janela(int x, int y, int width, int height);       // janelas definidas
void apaga_janela(int x, int y, int width, int height); // apaga janelas definidas
void cabecalho();                                       // pontua??o e vidas
void reinicia();                                        //reinicia partida
void fim_de_jogo();                                     //game over

//---- PONG -------------------------------
void desenha_pong();
void controle();

//---- BOLA -------------------------------
void desenha_bola();
int atualiza_bola();

/////////////////////////   MAIN   //////////////////////////////////////////
int main() {
    // prepara tela
    setup();
    //loopping de jogo
    loop();

    return 0;
}
/////////////////////////  END MAIN   ///////////////////////////////////////

void setup() {

    _setcursortype(_NOCURSOR);  // elimina cursor vis?vel na tela
    randomize();                // para rodar melhor a fun??o rand()
    main_window();              // cria janela principal
    cabecalho();                // cria cabe?alho inicial
    desenha_pong();             // inicia o pong no centro vertical
    desenha_bola();             // inicia a bola no centro da tela
}
//----------------------------------------------------------------------------

void loop(){
    while(1) {                    // looping infinito de jogo
       while(!kbhit()) {
            if(vidas <= 0){       // finaliza o jogo se n?o houver mais vidas
                fim_de_jogo();
                getch() << 27;    //garante que sair? do jogo colocando o ESC no buffer
                return;
            }
            Sleep(30);            //tempo para ver a tela / controla a velocidade do jogo
            controle();           // recebe os controles do teclado para movimento do pong
            desenha_pong();       //desenha o pong na tela
            desenha_bola();       //desenha a bola na tela
            if(!atualiza_bola())  // atualiza posi??o da bola
                reinicia();       // reinicia a partida se a bola passou do pong



            //debug();             //para ver valores de vari?veis na tela

            if(comando == 27) return;  //se ESc foi pressionado sai do looping
       }
       if(getch()==27) break;   // sai se pressionar tecla ESC (ASCII=27)

    }
}
//----------------------------------------------------------------------------

void janela(int x, int y, int width, int height) {

   // linha superior
   gotoxy(x,y);
   cprintf("%c",201);
   for(int i=1;i<width-1;i++) {
        gotoxy(x+i,y);
        cprintf("%c",205);
   }
   cprintf("%c",187);

   //linha inferior
   gotoxy(x,y+height);
   cprintf("%c",200);
   for(int i=1;i<width-1;i++){
        gotoxy(x+i,y+height);
        cprintf("%c",205);
   }
   cprintf("%c",188);

   // linhas laterais
   for(int i=1;i<height;i++) {
        gotoxy(x,y+i); cprintf("%c",186);
        gotoxy(x+width-1,y+i); cprintf("%c",186);
   }

   //reposiciona cursor
   gotoxy(x,y);
   gotoxy(x+1,y+1);
}
//----------------------------------------------------------------------------

void apaga_janela(int x, int y, int width, int height) {

   // apaga toda a janela e seu conte?do
   for(int i=x;i<=x+width;i++)
        for(int j=y;j<=y+height;j++) {
             gotoxy(i,j);
             cprintf(" ");
        }
}
//----------------------------------------------------------------------------

void main_window() {
    textcolor(WHITE);                   // define cor padr?o
    janela(1,1,MAX_WIDTH,MAX_HEIGHT);   //desenha janela em torno da tela
}
//----------------------------------------------------------------------------

void cabecalho() {
    janela(1,1,MAX_WIDTH,3);
    gotoxy(1,4);
    cprintf("%c",204);
    gotoxy(MAX_WIDTH,4);
    cprintf("%c",185);

    gotoxy(2,2);
    cprintf("VIDAS: %d",vidas);

    gotoxy((MAX_WIDTH/2)-4,2);
    cprintf("MEGA PONG");

    gotoxy(MAX_WIDTH-14,2);
    cprintf("PONTOS:    %d",pontos);

}
//-----------------------------------------------------------------------------

void desenha_pong() {

    //apaga parte do pong da posi??o anterior
    for(int i=0;i<MIN_HEIGHT; i++) { // pong com 5 pixels de tamanho vertical
        gotoxy(3,pos_anterior+i); //
        cprintf(" ");
    }

    //desenha nova posi??o do pong
    textcolor(YELLOW+BLINK);
    for(int i=0;i<MIN_HEIGHT; i++) { // pong com 5 pixels de tamanho vertical
        gotoxy(3,pos_pong+i); //
        cprintf("%c", 219);
    }
}
//----------------------------------------------------------------------

void controle() {
    Sleep(10);
    if(kbhit()) {

        pos_anterior = pos_pong; // pega posi??o anterior para apag?-lo na fun??o desenha
        comando = getch();

        //conserta CapsLock
        if(comando=='W') comando = 'w';
        else if(comando=='S') comando = 's';

        //executa troca de posi??o do pong
        switch(comando){
            case ('w'):
                if(pos_pong >MIN_HEIGHT)
                    pos_pong -=1;

                break;
            case ('s'):
                if(pos_pong <20)
                    pos_pong +=1;
                break;
        }
    }
}
//---------------------------------------------------------------------

void desenha_bola() {
    //apaga posi??o anterior da bola
    textcolor(GREEN);
    gotoxy(pos_bola_x_ant,pos_bola_y_ant);
    cprintf("%c", ' ');

    // desenha posi??o atual da bola
    textcolor(GREEN);
    gotoxy(pos_bola_x,pos_bola_y);
    cprintf("%c", '*');
}
//-------------------------------------------------------------------------

int atualiza_bola() {

    pos_bola_x_ant= pos_bola_x;
    pos_bola_y_ant= pos_bola_y;

    //batendo nas bordas superior e inferior indo para a esquerda
    if(pos_bola_y <= MIN_HEIGHT && direcao_bola==0) direcao_bola = 2;
    else if(pos_bola_y >= MAX_HEIGHT && direcao_bola==2) direcao_bola = 0;
    //batendo nas bordas superior e inferior indo para a direita
    else if(pos_bola_y <= MIN_HEIGHT && direcao_bola==1) direcao_bola = 3;
    else if(pos_bola_y >= MAX_HEIGHT && direcao_bola==3) direcao_bola = 1;

    //////////COLISAO COM PONG ////////
    if(pos_bola_x <= MIN_WIDTH && direcao_bola==0)
        if(pos_bola_y >= pos_pong && pos_bola_y <= pos_pong+5)
        {
            direcao_bola = 1;
            pontos += 10;
            gotoxy(73,2);             //atualiza pontos na tela
            cout<< setw(5)<< pontos;
        }
     else if(pos_bola_x <= MIN_WIDTH && direcao_bola==2) {
        if(pos_bola_y >= pos_pong && pos_bola_y <= pos_pong+5)
        {
            direcao_bola = 3;
            pontos += 10;
            gotoxy(10,2);             //atualiza pontos na tela
            cout<< setw(5)<< pontos;
        }
     }
     else
        return 0;

    //batendo, a principio (alterar esta parte para detectar colisao com pong) parede direita
    //manter, para partidas de 1 jogador
    if(pos_bola_x >= MAX_WIDTH-1 && direcao_bola==1) direcao_bola = 0;
    else if(pos_bola_x >= MAX_WIDTH-1 && direcao_bola==3) direcao_bola = 2;

    int mov = direcao_bola; // valor recebido
    switch(mov) {
        case 0:
            pos_bola_x-=1;pos_bola_y-=1;
            break;
        case 1:
            pos_bola_x+=1;pos_bola_y-=1;
            break;
        case 2:
            pos_bola_x-=1;pos_bola_y+=1;
            break;
        case 3:
            pos_bola_x+=1;pos_bola_y+=1;
            break;
    }
    return 1;
}
//----------------------------------------------------------------------

void reinicia() {
    // tira uma vida
    vidas -= 1;

    //mostra quantas vidas ainda tem
    Sleep(1000);
    janela((MAX_WIDTH/2)-5,(MAX_HEIGHT/2)-5,10,2);
    cout<< "VIDAS: " << vidas;
    Sleep(1500);

    //apaga janela de jogo
    apaga_janela(2,5,MAX_WIDTH-4,MAX_HEIGHT-5);
    Sleep(100);

    //reinicia posi??o da bola
    pos_bola_x    = (MAX_WIDTH/2) +rand()%15;  // inicia no centro horizontal
    pos_bola_y    = (MAX_HEIGHT/2)+rand()%10; // inicia no centro vertical

    direcao_bola = (rand()%4);

    // indica a posi??o vertical do pong na tela
    pos_pong      = (MAX_HEIGHT/2); // inicia no centro vertical, pong ter? 5 'pixels'

    //atualiza vidas no cabe?alho
    gotoxy(9,2);
    cout << vidas;
}
//----------------------------------------------------------------------

void fim_de_jogo() {
    //apaga janela de jogo
    apaga_janela(2,5,MAX_WIDTH-4,MAX_HEIGHT-5);
    Sleep(100);

    //mostra mensagem de fim de jogo
    janela((MAX_WIDTH/2)-10,(MAX_HEIGHT/2)-5,20,3);
    cout<< "FIM DE JOGO\n";
    gotoxy((MAX_WIDTH/2)-9,(MAX_HEIGHT/2)-3);
    cout<< "PONTOS: " << setw(5) <<pontos;

    Sleep(1500);
}
//----------------------------------------------------------------------

void debug() {
    textcolor(RED);
    //posi??o vertical do pong
    gotoxy(MAX_WIDTH-13, 5);
    cout<< "posicao: " <<setw(2) <<  pos_pong;
    //posi??o da bola
    gotoxy(MAX_WIDTH-20, 6);
    cout<<  "bola: x= "<< setw(2) << pos_bola_x << ", y= " << setw(2) << pos_bola_y;

    //valor registrado em "comando"
    gotoxy(MAX_WIDTH-12, 7);
    cout <<"comando: " << (char)comando;

    //direcao da bola
    gotoxy(MAX_WIDTH-18, 8);
    cout << "dir. bola: " <<direcao_bola;
}
//----------------------------------------------------------------------

