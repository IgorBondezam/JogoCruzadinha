// sorteia vogal x consoante x vogal para montar matriz

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <conio.c>
#include <locale.h>
#define tam 25
#define maxpal 100
#define muitaPalavra 245480

FILE *arqpal;
FILE *allWord;

int qpal = 0;
char palavras[maxpal][20];
char todasPalavras[muitaPalavra][28];
char palavrasorteada[20];
char pal[tam][tam];
char matrizInicio[tam][tam];
int tamanhoPalavra;
char palavraParaAchar[15];
bool achouPalavra = 0;
int palavrasAchadas = 0;
char palavraJaEncontrada[100][25];

bool abreArquivo();
void leArquivo();
bool pegarPalavra();
void sorteia();
void mostra();
void colocarPalavra();
bool acharPalavra();
bool essaPalavraExiste(char *palavra);
bool verPalavraJaEncontrada();
void duplicarMatriz();
void mostrarInicio();
//---------------------------------------------  MAIN ---------------------------------------------
int main()
{
   setlocale(LC_ALL, "Portuguese");
   srand(time(NULL));
   pegarPalavra();
   sorteia();
   colocarPalavra();
   duplicarMatriz();
   _setcursortype(_NOCURSOR);
   mostrarInicio();
   _setcursortype(_NORMALCURSOR);

   do
   {

      do
      {
         printf("Digite palavras da cruzadinha\npara ganhar pontos de acerto.\nPode estar na vertical ou horizontal.\nAcerte a palavra sorteada para acabar o jogo!!\n\n\n");
         mostra();
         printf("\nDigite uma palavra que esta no jogo.\n");
         gets(palavraParaAchar);
         strupr(palavraParaAchar);
         // Valida a palavra digitada
         if (strlen(palavraParaAchar) < 2 || strlen(palavraParaAchar) > 24)
         {
            printf("\nDigite uma palavra valida(entre 2 a 24 letras)!!\n");
            Sleep(3000);
            system("cls");
         }
      } while (strlen(palavraParaAchar) < 2 || strlen(palavraParaAchar) > 24);

      if (acharPalavra() == 1 && essaPalavraExiste(palavraParaAchar) == 1 && verPalavraJaEncontrada() == 1)
      {
         printf("\n\n\n\n");
         printf("Voce achou uma palavra!!!!");
         strcpy(palavraJaEncontrada[palavrasAchadas], palavraParaAchar);
         palavrasAchadas++;
      }
      else
      {
         printf("\n\n\n\n");
         printf("Palavra nao encontrada, nao existe ou ja foi encontrada!!\n\n");
      }
      Sleep(3000);
      system("cls");
   } while (strcmp(palavraParaAchar, palavrasorteada) != 0);

   printf("\n\nVoce achou %i palavra(s), meus parabens!\n\n", palavrasAchadas);
   return 0;
}
//-----------------------------------------------------------------------------------------------------
void sorteia()
{
   char vog[6] = "AEIOU";
   char con[22] = "BCDFGHJKLMNPQRSTVXWYZ";
   int cont = 1;
   // A=65   Z=90
   for (int x = 0; x < tam; x++)
      for (int y = 0; y < tam; y++)
      {
         if (cont == 1 || cont == 3)
         {
            pal[x][y] = vog[rand() % 5];
         }
         else
         {
            pal[x][y] = con[rand() % 21];
         }
         cont++;
         if (cont > 3)
         {
            cont = 1;
         }
      }
}
//---------------------------------------------
void mostra()
{

   for (int k = 0; k < tam; k++)
   {
      for (int p = 0; p < tam; p++)
      {
         textcolor((rand() % 14) + 1);
         printf("%c ", pal[k][p]);
      }
      printf("\n");
   }
}

//---------------------------------------------
bool pegarPalavra()
{
   srand(time(NULL));
   if (abreArquivo() == 0)
      return 0;
   leArquivo();
   // mostraPalavras();
   strcpy(palavrasorteada, palavras[rand() % maxpal]);
   tamanhoPalavra = strlen(palavrasorteada);
   printf("\n\n\n%s\n\n\n", palavrasorteada);
   return 1;
}
//---------------------------------------------
bool abreArquivo()
{
   arqpal = fopen("..\\palavras.txt", "r"); // leitura
   if (arqpal == NULL)
   { // Se houve erro na leitura do arquivo
      printf("Problemas na leitura do arquivo\n");
      system("pause");
      return 0; // n�o conseguiu abrir o arquivo
   }
   else
   {
      fclose(arqpal);
   }
   allWord = fopen("..\\palavrasDoPortuguesBR.txt", "r");
   if (allWord == NULL)
   { // Se houve erro na leitura do arquivo
      printf("Problemas na leitura do arquivo de todas as palavras\n");
      system("pause");
      return 0; // n�o conseguiu abrir o arquivo
   }
   else
   {
      fclose(allWord);
      return 1;
   }
}
//---------------------------------------------
void leArquivo()
{
   arqpal = fopen("..\\palavras.txt", "r"); // leitura
   qpal = 0;
   while (!feof(arqpal))
   {
      // fgets(string,tamanho,arquivo)
      fgets(palavras[qpal], 20, arqpal);
      palavras[qpal][strlen(palavras[qpal]) - 1] = '\0';
      qpal++;
   }
   fclose(arqpal);

   allWord = fopen("..\\palavrasDoPortuguesBR.txt", "r");
   qpal = 0;
   while (!feof(allWord))
   {
      // fgets(string,tamanho,arquivo)
      fgets(todasPalavras[qpal], 28, allWord);
      todasPalavras[qpal][strlen(todasPalavras[qpal]) - 1] = '\0';
      strupr(todasPalavras[qpal]);
      qpal++;
   }
   fclose(allWord);
}
//---------------------------------------------
void colocarPalavra()
{
   srand(time(NULL));
   int coluna, linha, vertOuHori;
   // 0 palavra na horizontal  -    1 palavra na vertical  - 2 horizontal contrario  - 3 vertical contrario
   vertOuHori = (rand() % 4);

   if (vertOuHori == 0)
   {
      linha = (rand() % 25);

      do
      {
         coluna = (rand() % 25);
      } while (25 - coluna < tamanhoPalavra);

      printf("%i - %i - %i - Horizontal\n\n", coluna, linha, tamanhoPalavra); 
      Sleep(2000);

      for (int i = 0; i != tamanhoPalavra; i++)
      {
         pal[linha][i + coluna] = palavrasorteada[i];
      }
   }
   else if (vertOuHori == 1)
   {
      coluna = (rand() % 25);

      do
      {
         linha = (rand() % 25);
      } while (25 - linha < tamanhoPalavra);

      printf("%i - %i - %i - vertical\n\n", coluna, linha, tamanhoPalavra); 
      Sleep(2000);

      for (int i = 0; i != tamanhoPalavra; i++)
      {
         pal[linha + i][coluna] = palavrasorteada[i];
      }
   }
   else if (vertOuHori == 2)
   {
      linha = (rand() % 25);

      do
      {
         coluna = (rand() % 25);
      } while (25 - coluna < tamanhoPalavra);

      printf("%i - %i - %i - horizontal invertida\n\n", coluna, linha, tamanhoPalavra); 
      Sleep(2000);
      int valorInverto = strlen(palavrasorteada) - 1;
      for (int i = 0; i != tamanhoPalavra; i++)
      {
         pal[linha][i + coluna] = palavrasorteada[valorInverto];
         valorInverto--;
      }
   }
   else if (vertOuHori == 3)
   {
      coluna = (rand() % 25);

      do
      {
         linha = (rand() % 25);
      } while (25 - linha < tamanhoPalavra);

      printf("%i - %i - %i - vertical invertida\n\n", coluna, linha, tamanhoPalavra);
      Sleep(2000);
      int valorInverso = strlen(palavrasorteada) - 1;
      for (int i = 0; i != tamanhoPalavra; i++)
      {
         pal[linha + i][coluna] = palavrasorteada[valorInverso];
         valorInverso--;
      }
   }
}
//---------------------------------------------
bool acharPalavra()
{
   int i = 0, j = 0;
   int tamanhoPalavraParaAchar = strlen(palavraParaAchar);
   int iterarPalavraParaAchar = 0;

   // validar horizontal
   do
   {
      for (i = 0; i < tam; i++)
      {
         for (j = 0; j < tam; j++)
         {
            if (palavraParaAchar[iterarPalavraParaAchar] == pal[i][j])
            {
               if (tamanhoPalavraParaAchar - 1 == iterarPalavraParaAchar)
               {
                  return 1;
               }
               else
               {
                  iterarPalavraParaAchar++;
               }
            }
            else
            {
               iterarPalavraParaAchar = 0;
            }
         }
         iterarPalavraParaAchar = 0;
      }

   } while (i != 25 && j != 25);
   // validar vertical
   do
   {
      for (i = 0; i < tam; i++)
      {
         for (j = 0; j < tam; j++)
         {
            if (palavraParaAchar[iterarPalavraParaAchar] == pal[j][i])
            {
               if (tamanhoPalavraParaAchar - 1 == iterarPalavraParaAchar)
               {
                  return 1;
               }
               else
               {
                  iterarPalavraParaAchar++;
               }
            }
            else
            {
               iterarPalavraParaAchar = 0;
            }
         }
         iterarPalavraParaAchar = 0;
      }

   } while (i != 25 && j != 25);

   do
   {
      for (i = tam - 1; i > 0; i--)
      {
         for (j = tam - 1; j > 0; j--)
         {
            if (palavraParaAchar[iterarPalavraParaAchar] == pal[i][j])
            {
               if (tamanhoPalavraParaAchar - 1 == iterarPalavraParaAchar)
               {
                  return 1;
               }
               else
               {
                  iterarPalavraParaAchar++;
               }
            }
            else
            {
               iterarPalavraParaAchar = 0;
            }
         }
         iterarPalavraParaAchar = 0;
      }

   } while (i != 0 && j != 0);

   do
   {
      for (i = tam - 1; i > 0; i--)
      {
         for (j = tam - 1; j > 0; j--)
         {
            if (palavraParaAchar[iterarPalavraParaAchar] == pal[j][i])
            {
               if (tamanhoPalavraParaAchar - 1 == iterarPalavraParaAchar)
               {
                  return 1;
               }
               else
               {
                  iterarPalavraParaAchar++;
               }
            }
            else
            {
               iterarPalavraParaAchar = 0;
            }
         }
         iterarPalavraParaAchar = 0;
      }

   } while (i != 0 && j != 0);

   return 0;
}

//---------------------------------------------
bool essaPalavraExiste(char *palavra)
{
   for (int i = 0; i < muitaPalavra; i++)
   {

      if (strcmp(palavra, todasPalavras[i]) == 0)
      {
         return 1;
      }
   }
   return 0;
}

//---------------------------------------------
bool verPalavraJaEncontrada()
{
   for (int i = 0; i < palavrasAchadas; i++)
   {
      if (strcmp(palavraParaAchar, palavraJaEncontrada[i]) == 0)
      {
         return 0;
      }
   }
   return 1;
}

void duplicarMatriz()
{

   for (int k = 0; k < tam; k++)
   {
      for (int p = 0; p < tam; p++)
      {
         textcolor((rand() % 14) + 1);
         matrizInicio[k][p] = ' ';
      }
      printf("\n");
   }
}

void mostrarInicio()
{
   int controlador = 0, cont = 0, contadorVerticalParaEspaco = 0, contadorHorizontalParaEspaco = 0, controladorEspaco = 0;

   for (int k = 0; k < tam; k++)
   {
      for (int p = 0; p < tam; p++)
      {
         if (controlador == 0)
         {
            textcolor((rand() % 14) + 1);
            matrizInicio[k][p] = pal[k][p];
         }
         if (controlador == 1)
         {
            textcolor((rand() % 14) + 1);
            matrizInicio[k][24 - p] = pal[k][24 - p];
         }

         if (cont > 15)
         {
            if (controladorEspaco == 0)
            {
               matrizInicio[contadorVerticalParaEspaco][contadorHorizontalParaEspaco] = ' ';
               contadorHorizontalParaEspaco++;
            }
            else
            {
               matrizInicio[contadorVerticalParaEspaco][24 - contadorHorizontalParaEspaco] = ' ';
               contadorHorizontalParaEspaco++;
            }
            if (contadorHorizontalParaEspaco % 25 == 0)
            {
               contadorHorizontalParaEspaco = 0;
               contadorVerticalParaEspaco++;
               if (controladorEspaco == 0)
               {
                  controladorEspaco = 1;
               }
               else
               {
                  controladorEspaco = 0;
               }
            }
         }

         for (int i = 0; i < tam; i++)
         {
            for (int j = 0; j < tam; j++)
            {
               printf("%c ", matrizInicio[i][j]);
            }
            printf("\n");
         }
         system("cls");
         cont++;
      }

      if (controlador == 0)
      {
         controlador = 1;
      }
      else
      {
         controlador = 0;
      }
   }

   for (int i = 0; i < tam; i++)
   {
      for (int j = 0; j < tam; j++)
      {
         printf("%c ", pal[i][j]);
      }
      printf("\n");
   }

   system("pause");
   system("cls");
}