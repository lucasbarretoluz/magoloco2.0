#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define NOMEARQSALVAMENTO "jogosalvo.txt"
#define L 30
#define C 60
#define false 0
#define true 1

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
        }};
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

//------------------

char mapa[L][C];
void entrada_teclado();
void movimenta();
void imprimir_mapa();
void cursor();
void hidecursor();
int salvaJogo();

//-------------MAIN
int main()
{
   char opcaoMenu;
   int teste = 0, testeSalvar = 0;
   tesouro1.colisao = 0;
   srand(time(NULL));
   do //atribui as posições iniciais aleatória do tesouro
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
   do //atribui a posição aleatória do mago.
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
      entrada_teclado();
      if (tab.pressionada == 1) //abre o menu.
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
            meuMago.pontos = 0;                                //zera os pontos
            meuMago.lives = 3;                                 //reseta as vidas.
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
            break;
            /*case 99:            //c
            case 67:            //C
               meuMago.nivel=carregaJogo();
               tab.pressionada=0;
               if(meuMago.nivel==0)
               {
                  printf("\nERRO AO CARREGAR ARQUIVO, OU ARQUIVO INEXISTENTE");
               }
               getchar();
               system("cls");
               break;*/
         }
      }
      movimenta();
      imprimir_mapa();
      Sleep(1000 / 30);
      cursor(0, 0);
      if (meuMago.lives == 0)
      {
         printf("\n TURURU\nVOCE PERDEU");
         sair.pressionada = 1;
      }
   }
   getchar();
}

//---------------------
char mapa[L][C] =
    {
        {"############################################################"},
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
        {"#           X                                              #"},
        {"#           X              XXXXXXXXXXXXXXXXXX           XX #"},
        {"#                                                       X  #"},
        {"#                                                       X  #"},
        {"#     XXXXXXXXXXXXXXXXXXXXXXXXXX     XXXXXXXXXXXXXXXX      #"},
        {"#                                                          #"},
        {"#                                                          #"},
        {"############################################################"}};

//------------------Entrada do teclado
void entrada_teclado()
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
         meuMago.aura = true;
         break;
      case 9: //comando 'tab' = menu.
         tab.pressionada += 1;
         meuMago.aura = false;
         //default
      }
   }
}

//---------------------
void movimenta()
{
   int i, x;
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
   if (meuMago.aura == true)
   {

      for (i = -2; i <= 2; i++)
      {
         for (x = -2; x <= 2; x++)
         {
            if ((mapa[ny + i][nx + x] == ' ') || (mapa[ny + i][nx + x] == 'Z'))
            {
               mapa[meuMago.posicao.y + i][meuMago.posicao.x + x] = 'O';
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
void imprimir_mapa()
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
void cursor(int x, int y)
{

   COORD coord = {x, y};

   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//---------------------
void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

//---------------------
int salvaJogo()
{
   FILE *salvarjogo;
   int l, c, teste;
   if (!(salvarjogo = fopen(NOMEARQSALVAMENTO, "w+")))
   {
      teste = 0;
   }
   else
   {
      for (l = 0; l <= L; l++)
      {
         for (c = 0; c <= C; c++)
         {
            fprintf(salvarjogo, "%s\n", mapa[l]);
         }
      }
      /*for(c=0; c<=C; c++)          //salva dados dos monstros
    {
        fprintf(salvarjogo, "tipo=%d\n", p1->monst[c].tipo);
        fprintf(salvarjogo, "vidasmonst=%d\n", p1->monst[c].vidas);
        fprintf(salvarjogo, "movx=%d\n", p1->monst[c].dx);
        fprintf(salvarjogo, "movy=%d\n", p1->monst[c].dy);
    }*/
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