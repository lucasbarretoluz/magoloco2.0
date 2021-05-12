#include <stdio.h>
#include <conio.h>
#include <windows.h>

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
   int vidas;
   int pontos;
   int nivel;
   boolean aura; //controle da arma secreta
};

// struct Arma
// {
//    struct cordenada posicao;
//    bool ativo;
// };

// struct Arma arma =
//     {
//         {
//             .x = 0,
//             .y = 0,
//         },
//         // ativo = false,
// };

struct Mago meuMago =
    {
        {
            .x = 1,
            .y = 1,
        },
        .valor_x = 0,
        .valor_y = 0,
        .vidas = 3,
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
void arma_secreta();

//-------------MAIN
int main()
{

   system("cls");

   hidecursor();

   while (meuMago.vidas > 0)
   {
      entrada_teclado();
      movimenta();
      imprimir_mapa();

      Sleep(1000 / 30);
      cursor(0, 0);
   }
   system("cls");
   printf("\n TURURU GAME OVER!");
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
        {"#           X      X         X      G       X              #"},
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
   char ch1;
   if (_kbhit())
   {
      ch1 = _getch();

      switch (ch1)
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
      case 87:                 //comando 'W'
         meuMago.valor_y = -1; //cima
         meuMago.valor_x = 0;
         break;
      case 115:                //comando 's'
         meuMago.valor_y = +1; //baixo
         meuMago.valor_x = 0;
         break;
      case 83:                 //comando 'S'
         meuMago.valor_y = +1; //baixo
         meuMago.valor_x = 0;
         break;
      case 97:                 //comando 'a'
         meuMago.valor_x = -1; //esquerda
         meuMago.valor_y = 0;
         break;
      case 65:                 //comando'A'
         meuMago.valor_x = -1; //esquerda
         meuMago.valor_y = 0;
         break;
      case 100:                //comando 'd'
         meuMago.valor_x = +1; //direita
         meuMago.valor_y = 0;
         break;
      case 68:                 //comando 'D'
         meuMago.valor_x = +1; //direita
         meuMago.valor_y = 0;
         break;
      case 102: //Letra f aura
         meuMago.aura = true;
         break;
      }
   }
}

//---------------------
void movimenta()
{

   mapa[meuMago.posicao.y][meuMago.posicao.x] = ' ';

   int nx = meuMago.valor_x + meuMago.posicao.x;
   int ny = meuMago.valor_y + meuMago.posicao.y;
   int i, x;
   if (mapa[ny][nx] == '#')
   {
      meuMago.valor_x = 0;
      meuMago.valor_y = 0;
   }
   if ((mapa[ny][nx] == 'Z') || (mapa[ny][nx] == 'T') || (mapa[ny][nx] == 'X'))
   {
      meuMago.vidas -= 1;
      meuMago.valor_x = 0;
      meuMago.valor_y = 0;
   }
   if (mapa[ny][nx] == 'G')
   {
      meuMago.pontos += 100;
   }

   if (meuMago.aura == true)
   {
      for (i = 0; i <= 2; i++)
      {
         for (x = 0; x <= 2; x++)
         {
            mapa[meuMago.posicao.y - i][meuMago.posicao.x - x] = 'O';
            mapa[meuMago.posicao.y - i][meuMago.posicao.x + x] = 'O';
            mapa[meuMago.posicao.y + i][meuMago.posicao.x - x] = 'O';
            mapa[meuMago.posicao.y + i][meuMago.posicao.x + x] = 'O';
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
void arma_secreta()
{
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
   printf("\nVIDAS = %d          NIVEL = %d           PONTOS = %d", meuMago.vidas, meuMago.nivel, meuMago.pontos);
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
