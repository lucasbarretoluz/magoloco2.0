/*O QUE ESTÁ SEM O 'OK' ESTÁ COM ALGUM DEFEITO*/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define NOMEARQSALVAMENTO "jogosalvo.txt"
#define L 23
#define C 60
#define false 0
#define true 1
#define NUM_MAX_MONSTROS 20

//---------------

struct cordenada
{
   int x;
   int y;
};

struct Mago
{
   struct cordenada posicao;
   int valor_x;
   int valor_y;
   int lives;
   int pontos;
   int nivel;
   boolean aura; //controle da arma secreta
};
struct Especiais
{
   int pressionada;
};
struct Especiais tab =
    {
        .pressionada = 0,
};
struct Especiais sair =
    {
        .pressionada = 0,
};
struct Tesouro
{
   struct cordenada posicao;
   int colisao;
};
struct Tesouro tesouro1 =
    {
        {
            .x = 0,
            .y = 0,
        },
};
struct Mago meuMago =
    {
        {
            .x = 0,
            .y = 0,
        },
        .valor_x = 0,
        .valor_y = 0,
        .lives = 3,
        .pontos = 0,
        .nivel = 1,
        .aura = false,

};
struct Monstro
{
   struct cordenada posicao[NUM_MAX_MONSTROS];
   int tipo[NUM_MAX_MONSTROS];
   int vida[NUM_MAX_MONSTROS];
   int passos[NUM_MAX_MONSTROS];
   struct cordenada deslocamento[NUM_MAX_MONSTROS];
   int numeroMonstros;
};
struct Monstro ogros =
    {};
struct Cronometro
{
   float segundos;
};
struct Cronometro poder =
    {
        .segundos = 0,
};
struct Cronometro contagem =
    {
        .segundos = 0,
};
//------------------

char mapa[L][C];
void entrada_teclado();  //OK
void movimenta();        //pensei em zerar as vidas dos monstros aq, quando ativar a aura.
void imprimir_mapa();    //OK
void cursor();           //OK
void hidecursor();       //OK
int salvaJogo();         //OK
void movimentaMonstro(); //OK
int lerMapa();
//int lerJogosalvo ();

//-------------MAIN
int main()
{
   char opcaoMenu;
   int teste = 0, testeSalvar = 0, i;
   time_t tempoInicial, tempoFinal;
   tesouro1.colisao = 0;
   srand(time(NULL));
   do //numero aleatório de monstros(OK)
   {
      ogros.numeroMonstros = rand() % NUM_MAX_MONSTROS;
   } while (ogros.numeroMonstros < ((NUM_MAX_MONSTROS / 4) + meuMago.nivel));
   for (i = 0; i < ogros.numeroMonstros; i++) // não deixa ser menor que um valor e aumenta a quantidade a cada nivel.(OK)
   {
      do
      {
         ogros.posicao[i].x = rand() % C;
         ogros.posicao[i].y = rand() % L;
         if ((mapa[ogros.posicao[i].y][ogros.posicao[i].x] == 'G') || (mapa[ogros.posicao[i].y][ogros.posicao[i].x] == '#') || (mapa[ogros.posicao[i].y][ogros.posicao[i].x] == 'Z') || (mapa[ogros.posicao[i].y][ogros.posicao[i].x] == 'X') || (mapa[ogros.posicao[i].y][ogros.posicao[i].x] == 'J') || (mapa[ogros.posicao[i].y][ogros.posicao[i].x] == 'T')) //impede do monstro nascer em cima de algum outro objeto do mapa.
         {
            teste = 0;
         }
         else
         {
            do //atribui o ogros.tipo do monstro 1 para zumbi e 2 para trol.
            {
               ogros.tipo[i] = rand() % 3;
            } while (ogros.tipo[i] == 0);
            if (ogros.tipo[i] == 1) //se for zumbi.
            {
               ogros.vida[i] = 1;
               mapa[ogros.posicao[i].y][ogros.posicao[i].x] = 'Z';
            }
            if (ogros.tipo[i] == 2) //se for trol.
            {
               ogros.vida[i] = 2;
               mapa[ogros.posicao[i].y][ogros.posicao[i].x] = 'T';
            }
            teste = 1;
         }
      } while (teste == 0);
      ogros.deslocamento[i].x = 1;
      ogros.deslocamento[i].y = 1;
   }
   do //atribui as posições iniciais aleatória do tesouro(OK)
   {
      tesouro1.posicao.x = rand() % C;
      tesouro1.posicao.y = rand() % L;
      if ((mapa[tesouro1.posicao.y][tesouro1.posicao.x] == '#') || (mapa[tesouro1.posicao.y][tesouro1.posicao.x] == 'Z') || (mapa[tesouro1.posicao.y][tesouro1.posicao.x] == 'X') || (mapa[tesouro1.posicao.y][tesouro1.posicao.x] == 'J') || (mapa[tesouro1.posicao.y][tesouro1.posicao.x] == 'T')) //impede do jogador nascer em cima de algum outro objeto do mapa.
      {
         teste = 0;
      }
      else
      {
         teste = 1;
      }
   } while (teste == 0);
   do //atribui a posição aleatória do mago.(OK)
   {
      meuMago.posicao.x = rand() % C;                                                                                                                                                                                                                                                      //atribui posição inicial x aleatória.
      meuMago.posicao.y = rand() % L;                                                                                                                                                                                                                                                      //atribui posição inicial y aleatória.
      if ((mapa[meuMago.posicao.y][meuMago.posicao.x] == '#') || (mapa[meuMago.posicao.y][meuMago.posicao.x] == 'Z') || (mapa[meuMago.posicao.y][meuMago.posicao.x] == 'X') || (mapa[meuMago.posicao.y][meuMago.posicao.x] == 'G') || (mapa[meuMago.posicao.y][meuMago.posicao.x] == 'T')) //impede do jogador nascer em cima de algum outro objeto do mapa.
      {
         teste = 0;
      }
      else
      {
         teste = 1;
      }
   } while (teste == 0);
   hidecursor();
   while (sair.pressionada == 0)
   {
      tempoInicial = time(NULL); //atribui o tempo inicial.
      entrada_teclado();         //OK
      if (tab.pressionada == 1)  //abre o menu.(OK)
      {
         system("cls");
         printf("\nPara sair do jogo pressione 'Q'");
         printf("\nPara iniciar um novo jogo pressione 'N'");
         printf("\nPara Carregar um jogo pressionen 'C'");
         printf("\nPara salvar o jogo pressione 'S'");
         printf("\nPara voltar pressione 'V'");
         scanf("%c", &opcaoMenu);
         switch (opcaoMenu)
         {
         case 113: //q
         case 81:  //Q
            sair.pressionada += 1;
            tab.pressionada = 0;
            break;
         case 110:                                             //n
         case 78:                                              //N
            mapa[meuMago.posicao.y][meuMago.posicao.x] = 32;   //apaga o jogador de antes.
            mapa[tesouro1.posicao.y][tesouro1.posicao.x] = 32; //apaga o tesouro de antes.
            for (i = 0; i < ogros.numeroMonstros; i++)
            {
               mapa[ogros.posicao[i].y][ogros.posicao[i].x] = 32;
            }
            poder.segundos = 0;
            contagem.segundos = 0;
            ogros.deslocamento->x = 0;
            ogros.deslocamento->y = 0;
            meuMago.pontos = 0; //zera os pontos
            meuMago.lives = 3;  //reseta as vidas.
            do                  //numero aleatório de monstros
            {
               ogros.numeroMonstros = rand() % NUM_MAX_MONSTROS;
            } while (ogros.numeroMonstros < ((NUM_MAX_MONSTROS / 4) + meuMago.nivel));
            for (i = 0; i < ogros.numeroMonstros; i++) // não deixa ser menor que um valor e aumenta a quantidade a cada nivel.
            {
               do
               {
                  ogros.posicao[i].x = rand() % C;
                  ogros.posicao[i].y = rand() % L;
                  if ((mapa[ogros.posicao[i].y][ogros.posicao[i].x] == 'G') || (mapa[ogros.posicao[i].y][ogros.posicao[i].x] == '#') || (mapa[ogros.posicao[i].y][ogros.posicao[i].x] == 'Z') || (mapa[ogros.posicao[i].y][ogros.posicao[i].x] == 'X') || (mapa[ogros.posicao[i].y][ogros.posicao[i].x] == 'J') || (mapa[ogros.posicao[i].y][ogros.posicao[i].x] == 'T')) //impede do monstro nascer em cima de algum outro objeto do mapa.
                  {
                     teste = 0;
                  }
                  else
                  {
                     do //atribui o ogros.tipo do monstro 1 para zumbi e 2 para trol.
                     {
                        ogros.tipo[i] = rand() % 3;
                     } while (ogros.tipo[i] == 0);
                     if (ogros.tipo[i] == 1) //se for zumbi.
                     {
                        ogros.vida[i] = 1;
                        mapa[ogros.posicao[i].y][ogros.posicao[i].x] = 'Z';
                     }
                     if (ogros.tipo[i] == 2) //se for trol.
                     {
                        ogros.vida[i] = 2;
                        mapa[ogros.posicao[i].y][ogros.posicao[i].x] = 'T';
                     }
                     teste = 1;
                  }
               } while (teste == 0);
               ogros.deslocamento[i].x = 1;
               ogros.deslocamento[i].y = 1;
            }
            teste = 0;
            do //atribui nova posição do mago.
            {
               meuMago.posicao.x = rand() % C;                                                                                                                                                                                                                                                      //atribui posição inicial x aleatória.
               meuMago.posicao.y = rand() % L;                                                                                                                                                                                                                                                      //atribui posição inicial y aleatória.
               if ((mapa[meuMago.posicao.y][meuMago.posicao.x] == '#') || (mapa[meuMago.posicao.y][meuMago.posicao.x] == 'Z') || (mapa[meuMago.posicao.y][meuMago.posicao.x] == 'X') || (mapa[meuMago.posicao.y][meuMago.posicao.x] == 'G') || (mapa[meuMago.posicao.y][meuMago.posicao.x] == 'T')) //impede do jogador nascer em cima de algum outro objeto do mapa.
               {
                  teste = 0;
               }
               else
               {
                  teste = 1;
               }
            } while (teste == 0);
            teste = 0;
            do //atribui nova posição do tesouro.
            {
               tesouro1.posicao.x = rand() % C;
               tesouro1.posicao.y = rand() % L;
               if ((mapa[tesouro1.posicao.y][tesouro1.posicao.x] == '#') || (mapa[tesouro1.posicao.y][tesouro1.posicao.x] == 'Z') || (mapa[tesouro1.posicao.y][tesouro1.posicao.x] == 'X') || (mapa[tesouro1.posicao.y][tesouro1.posicao.x] == 'J') || (mapa[tesouro1.posicao.y][tesouro1.posicao.x] == 'T')) //impede do jogador nascer em cima de algum outro objeto do mapa.
               {
                  teste = 0;
               }
               else
               {
                  teste = 1;
               }
            } while (teste == 0);
            tab.pressionada = 0;
            system("cls");
            break;
         case 118: //v
         case 86:  //V
            tab.pressionada = 0;
            system("cls");
            break;
         case 115:                     //s
         case 83:                      //S
            testeSalvar = salvaJogo(); //chama a função para salvar o jogo.
            if (testeSalvar == 1)
            {
               printf("\nSalvo com sucesso.");
            }
            else
            {
               printf("\nErro");
            }
            tab.pressionada = 0;
            getchar();
            system("cls");
            break;
         case 99: //c
         case 67: //C
            meuMago.nivel = lerMapa();
            tab.pressionada = 0;
            if (meuMago.nivel == 0)
            {
               printf("\nERRO AO CARREGAR ARQUIVO, OU ARQUIVO INEXISTENTE");
            }
            getchar();
            system("cls");
            break;
         }
      }
      movimenta();
      if (contagem.segundos >= 3) //OK.
      {
         movimentaMonstro(); //OK
         contagem.segundos = 0;
      }
      imprimir_mapa(); //OK
      Sleep(1000 / 30);
      cursor(0, 0);
      if (meuMago.lives == 0) //OK
      {
         printf("\n TURURU\nVOCE PERDEU");
         sair.pressionada = 1;
      }
      tempoFinal = time(NULL);                                 //atribui o tempo final
      contagem.segundos += difftime(tempoFinal, tempoInicial); //soma a diferença entre os tempos de duração do while.
      poder.segundos += difftime(tempoFinal, tempoInicial);    //soma a diferença entre os tempos de duração do while.
   }
   getchar();
}

//---------------------
char mapa[L][C] = //ALTERAR PARA SER O LUGAR ONDE O ARQUIVO DE MAPAS ABRIRA.
    {{"############################################################"},
     {"#                                                          #"},
     {"#                                                          #"},
     {"#                                                          #"},
     {"#    XXXXXXXXXXXXXXXXXXXX    X              X              #"},
     {"#                  X         X              X              #"},
     {"#                            X              X              #"},
     {"#                            X              X    XXXXXXX   #"},
     {"#           X      X         X              X              #"},
     {"#           X      X         X              X              #"},
     {"#           X      X         X              X              #"},
     {"#           X      X         X              X              #"},
     {"#                                                          #"},
     {"#                                                          #"},
     {"#                                                          #"},
     {"#                                                          #"},
     {"#                                                          #"},
     {"#           X      X                                       #"},
     {"#           X      X                                       #"},
     {"#           X      X                                       #"},
     {"#           X      XXXXXXXXX                               #"},
     {"#                                                          #"},
     {"############################################################"}};

//------------------Entrada do teclado
void entrada_teclado() //OK
{
   char ch1, ch2;
   if (_kbhit())
   {
      ch1 = _getch();

      switch (ch1) //falta adicionar valores para W S A D
      {

      case 72:                 //seta cima
         meuMago.valor_y = -1; //cima
         meuMago.valor_x = 0;
         meuMago.aura = false;
         break;
      case 80:                 //seta baixo
         meuMago.valor_y = +1; //baixo
         meuMago.valor_x = 0;
         meuMago.aura = false;
         break;
      case 75:                 //seta esquerda
         meuMago.valor_x = -1; //esquerda
         meuMago.valor_y = 0;
         meuMago.aura = false;
         break;
      case 77:                 //seta direita
         meuMago.valor_x = +1; //direita
         meuMago.valor_y = 0;
         meuMago.aura = false;
         break;
      case 87:
      case 119:                //comando 'w'
         meuMago.valor_y = -1; //cima
         meuMago.valor_x = 0;
         meuMago.aura = false;
         break;
      case 83:
      case 115:                //comando 's'
         meuMago.valor_y = +1; //baixo
         meuMago.valor_x = 0;
         meuMago.aura = false;
         break;
      case 65:
      case 97:                 //comando 'a'
         meuMago.valor_x = -1; //esquerda
         meuMago.valor_y = 0;
         meuMago.aura = false;
         break;
      case 68:
      case 100:                //comando 'd'
         meuMago.valor_x = +1; //direita
         meuMago.valor_y = 0;
         meuMago.aura = false;
         break;
      case 70:
      case 102: //comando 'f' = poder.
         //meuMago.aura = true;
         if (poder.segundos >= 5)
         {
            meuMago.aura = true;
            poder.segundos = 0;
         }
         break;
      case 9: //comando 'tab' = menu.
         tab.pressionada += 1;
         meuMago.aura = false;
         //default
      }
   }
}

//---------------------
void movimenta() //OK, por enquanto.
{
   int i, x, z = 0, teste = 0;
   mapa[meuMago.posicao.y][meuMago.posicao.x] = ' ';
   if (tesouro1.colisao != 1) //analisa se o jogador pegou o tesouro.
   {
      mapa[tesouro1.posicao.y][tesouro1.posicao.x] = 'G';
   }

   int nx = meuMago.valor_x + meuMago.posicao.x;
   int ny = meuMago.valor_y + meuMago.posicao.y;

   if (mapa[ny][nx] == '#')
   {

      meuMago.valor_x = 0;
      meuMago.valor_y = 0;
   }
   if ((mapa[ny][nx] == 'X') || (mapa[ny][nx] == 'T') || (mapa[ny][nx] == 'Z'))
   {
      meuMago.lives -= 1;
      meuMago.valor_x = 0;
      meuMago.valor_y = 0;
   }
   if (mapa[ny][nx] == 'G')
   {
      meuMago.pontos += 100; //atribui a pontuação.
      tesouro1.colisao = 1;  //atribui a colisao.
   }
   if (meuMago.aura == false)
   {
      for (i = 0; i <= L; i++)
      {
         for (x = 0; x <= C; x++)
         {
            if (mapa[i][x] == 'O')
            {
               mapa[i][x] = ' ';
            }
         }
      }
   }
   if (meuMago.aura == true) //arrumar
   {

      for (i = -2; i <= 2; i++)
      {
         for (x = -2; x <= 2; x++)
         {
            if (mapa[ny + i][nx + x] == ' ')
            {
               mapa[meuMago.posicao.y + i][meuMago.posicao.x + x] = 'O';
            }
            if ((mapa[ny + i][nx + x] == 'Z') || (mapa[ny + i][nx + x] == 'T'))
            {
               while (teste == 0)
               {
                  if ((ogros.posicao[z].x == (nx + x) && (ogros.posicao[z].y == (ny + i))))
                  {
                     ogros.vida[z]--;
                     teste = 1;
                  }
                  z++;
               }
            }
         }
      }
   }
   meuMago.posicao.x += meuMago.valor_x;
   meuMago.posicao.y += meuMago.valor_y;
   mapa[meuMago.posicao.y][meuMago.posicao.x] = 'J';

   //---------para deixar um clic por movimento a
   meuMago.valor_x = 0;
   meuMago.valor_y = 0;
}

//----------------------
void imprimir_mapa() //OK
{
   int i, j;
   for (i = 0; i < L; i++)
   {
      for (j = 0; j < C; j++)
      {
         printf("%c", mapa[i][j]);
      }
      printf("\n");
   }
   printf("\nVIDAS = %d          NIVEL = %d           PONTOS = %d", meuMago.lives, meuMago.nivel, meuMago.pontos);
}

//----------------------
void cursor(int x, int y) //OK
{

   COORD coord = {x, y};

   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//---------------------
void hidecursor() //OK
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

//---------------------
void movimentaMonstro() //OK
{
   int sinal, i, x = 0; //variavel para decidir se o deslocamento fica positivo ou negativo.
   for (i = 0; i < ogros.numeroMonstros; i++)
   {
      if (ogros.vida[i] > 0)
      {
         if ((ogros.passos[i] == 5) || (mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] == '#') || (mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] == 'Z') || (mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] == 'T') || (mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] == 'X')) //cuida, conforme especificação, se ja deu 5 passo, ou se vai bater em algo.
         {
            if (ogros.tipo[i] == 1) //zumbi
            {
               if (mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] != 'X') //não muda o deslocamento se for obstaculo, pois os zumbis o atravessam.
               {
                  do //looping para mudar os deslocamentos.
                  {
                     ogros.deslocamento[i].x = rand() % 2;
                     ogros.deslocamento[i].y = rand() % 2;
                     sinal = rand() % 2;
                     if (sinal == 0)
                     {
                        ogros.deslocamento[i].x = -ogros.deslocamento[i].x;
                     }
                     if (sinal == 1)
                     {
                        ogros.deslocamento[i].y = -ogros.deslocamento[i].y;
                     }
                  } while ((mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] == '#') || (mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] == 'Z') || (mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] == 'T')); //dura até que a posição futura não colida em nada.
                  mapa[ogros.posicao[i].y][ogros.posicao[i].x] = ' ';
                  mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] = 'Z';
               }
               if (mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] == 'X') //se a posição futura for um obstaculo, ele fica invisivel enquanto esta no obstaculo.
               {
                  mapa[ogros.posicao[i].y][ogros.posicao[i].x] = ' ';
               }
               if (mapa[ogros.posicao[i].y][ogros.posicao[i].x] == 'X') //se a posição atual é um obstaculo ele não apaga o obstaculo apos sair.
               {
                  mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] = 'Z';
               }
            }
            if (ogros.tipo[i] == 2) //trol.
            {
               do //looping para alterar o deslocamento do trol.
               {
                  ogros.deslocamento[i].x = rand() % 2;
                  ogros.deslocamento[i].y = rand() % 2;
                  sinal = rand() % 2;
                  if (sinal == 0)
                  {
                     ogros.deslocamento[i].x = -ogros.deslocamento[i].x;
                  }
                  if (sinal == 1)
                  {
                     ogros.deslocamento[i].y = -ogros.deslocamento[i].y;
                  }
               } while ((mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] == '#') || (mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] == 'Z') || (mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] == 'T') || (mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] == 'X')); //continua ate que a posição futura não seja um obstaculo.
               mapa[ogros.posicao[i].y][ogros.posicao[i].x] = ' ';
               mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] = 'T';
               ogros.passos[i] = 0;
            }
         }
         if ((mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] == ' ') || (mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] == 'O')) //se for uma posição vazia ele se move normalmente.
         {
            mapa[ogros.posicao[i].y][ogros.posicao[i].x] = ' ';
            if (ogros.tipo[i] == 1) //zumbi.
            {
               mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] = 'Z';
            }
            if (ogros.tipo[i] == 2) //trol.
            {
               mapa[ogros.posicao[i].y + ogros.deslocamento[i].y][ogros.posicao[i].x + ogros.deslocamento[i].x] = 'T';
            }
         }
         ogros.posicao[i].x += ogros.deslocamento[i].x;
         ogros.posicao[i].y += ogros.deslocamento[i].y;
      }
      else
      {
         mapa[ogros.posicao[i].y][ogros.posicao[i].x] = ' ';
         x++;
      }
   }
   if (x == ogros.numeroMonstros)
   {
      meuMago.nivel += 1;
   }
}

//---------------------
int salvaJogo() //OK
{
   FILE *salvarjogo;
   int l, c, teste;
   if (!(salvarjogo = fopen(NOMEARQSALVAMENTO, "w+"))) //abre o arquivo
   {
      teste = 0;
   }
   else
   {
      printf("\n\nMapa:\n");
      for (l = 0; l < L; l++)
      {
         for (c = 0; c < C; c++)
         {
            fputc(mapa[l][c], salvarjogo);
         }
         fputs("\n", salvarjogo);
      }
      fprintf(salvarjogo, "pontos=%d\n", meuMago.pontos);
      fprintf(salvarjogo, "vidas=%d\n", meuMago.lives);
      fprintf(salvarjogo, "nivel=%d\n", meuMago.nivel);
      fprintf(salvarjogo, "magox=%d\n", meuMago.posicao.x);
      fprintf(salvarjogo, "magoy=%d\n", meuMago.posicao.y);
      fclose(salvarjogo);
      teste = 1;
   }
   return teste;
}

//---------------------
int lerMapa()
{
   int retorno, l, c, x, y;
   FILE *mapas;
   if (!(mapas = fopen(NOMEARQSALVAMENTO, "r")))
   {
      retorno = 0;
   }
   else
   {
      for (y = 0; y <= L; y++)
      {
         for (x = 0; x <= C; x++)
         {
            mapa[y][x] = ' ';
         }
      }
      for (l = 0; l <= L; l++)
      {
         for (c = 0; c <= C; c++)
         {
            mapa[l][c] = getc(mapas);
         }
      }
      retorno = 1;
   }

   return retorno;
}

//---------------------