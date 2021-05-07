
#include <stdio.h>
#include <conio.h>
#include <windows.h>

//#include "raylib/src/raylib.h"

#define L 30
#define C 60

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
};

struct Mago meuMago =
    {
        {
            .x = 1,
            .y = 1,
        },
        .valor_x = 0,
        .valor_y = 0,

};

//------------------

char mapa[L][C];
void entrada_teclado();
void movimenta();
void imprimir_mapa();
void cursor();
void hidecursor();

//-------------MAIN
int main()
{

   system("cls");

   hidecursor();

   while (1)
   {
      entrada_teclado();
      movimenta();
      imprimir_mapa();

      Sleep(1000 / 30);
      cursor(0, 0);
   }
}

//---------------------

char mapa[L][C] =
    {
        {"############################################################"},
        {"#                                                          #"},
        {"#                                                          #"},
        {"#    XXXXXXXXXXXXXXXXXXXX    X              X              #"},
        {"#                  X         X              X              #"},
        {"#                            X              X    XXXXXXX   #"},
        {"#           X      X         X              X              #"},
        {"#           X      X         X              X              #"},
        {"#           x      X         X              X              #"},
        {"#           X      X         X              X              #"},
        {"#           X      X         X              X              #"},
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
         break;
      case 80:                 //seta baixo
         meuMago.valor_y = +1; //baixo
         meuMago.valor_x = 0;
         break;
      case 75:                 //seta esquerda
         meuMago.valor_x = -1; //esquerda
         meuMago.valor_y = 0;
         break;
      case 77:                 //seta direita
         meuMago.valor_x = +1; //direita
         meuMago.valor_y = 0;
         break;
      case 119:                //comando 'w'
         meuMago.valor_y = -1; //cima
         meuMago.valor_x = 0;
         break;
      case 115:                //comando 's'
         meuMago.valor_y = +1; //baixo
         meuMago.valor_x = 0;
         break;
      case 97:                 //comando 'a'
         meuMago.valor_x = -1; //esquerda
         meuMago.valor_y = 0;
         break;
      case 100:                //comando 'd'
         meuMago.valor_x = +1; //direita
         meuMago.valor_y = 0;
         break;
         //default
      }
   }
}

//---------------------
void movimenta()
{

   mapa[meuMago.posicao.y][meuMago.posicao.x] = ' ';

   int nx = meuMago.valor_x + meuMago.posicao.x;
   int ny = meuMago.valor_y + meuMago.posicao.y;

   if (mapa[ny][nx] == '#')
   {

      meuMago.valor_x = 0;
      meuMago.valor_y = 0;
   }

   meuMago.posicao.x += meuMago.valor_x;
   meuMago.posicao.y += meuMago.valor_y;

   mapa[meuMago.posicao.y][meuMago.posicao.x] = 'J';

   //---------para deixar um clic por movimento a
   // meuMago.valor_x = 0;
   // meuMago.valor_y = 0;
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
