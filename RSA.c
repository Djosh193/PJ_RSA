#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


//Pré encriptografia
//Atenção: O valor da pré encriptografia, não pode ser maior que a chave pública
int preEncriptografia (int x){
  if (x == 65) {return 2;} //A
  if (x == 66) {return 3;} //B
  if (x == 67) {return 4;} //C
  if (x == 68) {return 5;} //D
  if (x == 69) {return 6;} //E
  if (x == 70) {return 7;} //F
  if (x == 71) {return 8;} //G
  if (x == 72) {return 9;} //H
  if (x == 73) {return 10;} //I
  if (x == 74) {return 11;} //J
  if (x == 75) {return 12;} //K
  if (x == 76) {return 13;} //L
  if (x == 77) {return 14;} //M
  if (x == 78) {return 15;} //N
  if (x == 79) {return 16;} //O
  if (x == 80) {return 17;} //P
  if (x == 81) {return 18;} //Q
  if (x == 82) {return 19;} //R
  if (x == 83) {return 20;} //S
  if (x == 84) {return 21;} //T
  if (x == 85) {return 22;} //U
  if (x == 86) {return 23;} //V
  if (x == 87) {return 24;} //W
  if (x == 88) {return 25;} //X
  if (x == 89) {return 26;} //Y
  if (x == 90) {return 27;} //Z
  if (x == 32) {return 28;} //SPACE
  return 0;
}

int descriptografia (int x){
  if (x == 2) {return 65;}
  if (x == 3) {return 66;}
  if (x == 4) {return 67;}
  if (x == 5) {return 68;}
  if (x == 6) {return 69;}
  if (x == 7) {return 70;}
  if (x == 8) {return 71;}
  if (x == 9) {return 72;}
  if (x == 10) {return 73;}
  if (x == 11) {return 74;}
  if (x == 12) {return 75;}
  if (x == 13) {return 76;}
  if (x == 14) {return 77;}
  if (x == 15) {return 78;}
  if (x == 16) {return 79;}
  if (x == 17) {return 80;}
  if (x == 18) {return 81;}
  if (x == 19) {return 82;}
  if (x == 20) {return 83;}
  if (x == 21) {return 84;}
  if (x == 22) {return 85;}
  if (x == 23) {return 86;}
  if (x == 24) {return 87;}
  if (x == 25) {return 88;}
  if (x == 26) {return 89;}
  if (x == 27) {return 90;}
  if (x == 28) {return 32;}
  return 0;
}

// Função pra descobrir o MDC entre 2 números, usando para saber se é coprimo
int MDC(long int a, long int b)
{
  if (a > b)
  {
    if (a % b == 0)
    {
      return b;
    }
    else
    {
      return MDC(b, a % b);
    }
  }
  else
  {
    if (b % a == 0)
    {
      return a;
    }
    else
    {
      return MDC(a, b % a);
    }
  }
}

// Funções para encontrar "d"
int unica(int s, int m)
{
  if (s > m)
  {
    return s - m;
  }
  else
  {
    return unica(s + m, m);
  }
}

// Funções para encontrar "d"
void solucao(int s, int m, int m0, int i)
{
  if (s > m0)
  {
    return;
  }
  else
  {
    printf("Solução %d: %d\n", i, s);
    solucao(s + m, m, m0, i + 1);
  }
}

// Funções para encontrar "d"
int mdc_extendido(int a, int b, int *s, int *t)
{
  if (a == 0)
  {
    *s = 0;
    *t = 1;
    return b;
  }
  int s1, t1;

  int MDC = mdc_extendido(b % a, a, &s1, &t1);
  *s = t1 - (b / a) * s1;
  *t = s1;

  return MDC;
}


long long int expRapida(long long int x,  long long int y){ //Calcula x^y em Log Y
	long long int ans = 1;
	while(y>0){
		if(y&1) ans*=x; //y&1 verifica se é impar
		y = y >> 1;
		x*=x;
	}
	return ans;
}

long long int expRapida_mod(long long int x, long long int y, long long int p){ //Calcula x^y%p em Log Y
	long long int ans = 1;
	while(y > 0){
		if(y&1) ans = (ans*x) % p;
		y = y >> 1;
		x = (x*x) % p;
	}
	return ans;
}

char textoOriginal[1000] = {}; // Array onde será armazenado a mensagem original.
long long int C[1000] = {};         // TEXTO criptografado
int M[1000] = {};              // TEXTO descriptografado
int tamanho;
long int np, nq;
int chave,chave2;

int main()
{
  int escolha = 0;

  while (escolha != 4)
  {
    printf("Digite:\n1 - Gerar Chave Pública\n2 - Encriptografar\n3 - Descriptografar\n4 - Sair\n");

    scanf("%d", &escolha);
    if (escolha == 1)
    {
      // Nº 1 - Chave Pública

      long int p, q;  // Números primos
      long int e;     // Expoente de encriptografia.
      long int teste; // Parametro que deve ser coprimo a "e".
      printf("Você selecionou a opção 1 - Gerar Chave Pública.\n");
      printf("Digite um par de números primos, exemplo: 3 5\n");
      scanf("%ld %ld", &p, &q);
      printf("Agora digite um expoente -e- relativamente primo:\n");
      printf ("Não usar expoentes de 2 digitos\n");
      scanf("%ld", &e);
      np = p;
      nq = q;
      teste = (p - 1) * (q - 1);

      while (MDC(e, teste) != 1)
      {
        printf("Esse número -e- não é coprimo, favor digite outro!\n");
        printf("Agora digite um expoente -e- relativamente primo:\n");
        scanf("%ld", &e);
      }

      if (MDC(e, teste) == 1)
      {
        printf("Expoente criado com sucesso!\n");
      }

      long int n = p * q; // Chave Pública
      chave = n;
      chave2 = e;

      FILE *pont_arq; // Arquivo txt
      pont_arq = fopen("publicKey.txt", "w");

      if (pont_arq == NULL)
      {
        printf("Erro na criação do arquivo!\n");
        return 1;
      }

      fprintf(pont_arq, "%ld %ld", n, e);

      fclose(pont_arq);

      printf("Chave Pública criada com sucesso!\n");
      printf("Favor anote sua Chave Pública:\nNúmero n:%ld\nNúmero e:%ld\n", n, e);
    }
    if (escolha == 2)
    {
      // Nº 2 - Encriptografia

      printf("Você selecionou a opção 2 - Encriptografar.\n");

      int flag = 0;
      printf("ATENÇÃO\n");
      printf("USAR APENAS LETRAS MAIÚSCULAS e SEM CARACTERES ESPECIAIS\n");

      while (flag != 1)
      {

        printf("Digite a mensagem a ser encriptografada:\n");
        fgets(textoOriginal, 1000, stdin);
        printf("A mensagem digitada foi:\n%s\n", textoOriginal);
        printf("A mensagem está correta?\nDigite 1 para Sim.\nDigite 2 para Não\n");
        scanf("%d", &flag);
      }
      int count = strlen(textoOriginal); // Tamanho da Msg

      long int n, e;
      tamanho = count;
      printf("Digite a sua chave pública:\n");
      printf("Número n:\n");
      scanf("%ld", &n);
      if (n != chave){
        printf ("Erro: Essa não é sua chave!\n");
        return 1;
      }
      printf("Número e:\n");
      scanf("%ld", &e);
      if (e != chave2){
        printf ("Erro: Essa não foi o -e- escolhido!\n");
        return 1;
      }

      // base ^e ≡ C mod n
      long int base; // Parametro de Pré-encriptografia.
      int i;

      FILE *cripto; // Arquivo txt
      cripto = fopen("encriptada.txt", "w");

      if (cripto == NULL)
      {
        printf("Erro na criação do arquivo!\n");
        return 1;
      }

      for (i = 0; i < count-1; i++)
      {
        base = preEncriptografia(textoOriginal[i]);

        //C[i] = (long long int)pow(base, e) % n;
        //C[i] = expRapida (base, e);
        C[i] = expRapida (base, e);

        fprintf(cripto, "%lld", C[i]);
      }
      fclose(cripto);
      printf("Mensagem Encriptada com sucesso!\n");
    }
    if (escolha == 3)
    {
      // Nº 3 - Descriptografia

      printf("Você selecionou a opção 3 - Descriptografar.\n");

      long int p, q, e;

      printf("Digite os números primos por exemplo: 3 5\n");
      scanf("%ld %ld", &p, &q);
      if (np != p){
        printf ("Erro: Esse não foi o -p- escolhido.\n");
        return 1;
      }
      if (nq != q){
        printf ("Erro: Esse não foi o -q- escolhido.\n");
        return 1;
      }
      printf("Digite o número e:\n");
      scanf("%ld", &e);
      if (chave2 != e){
        printf ("Erro: Esse não foi o -e- escolhido.\n");
        return 1;
      }

      int n = p * q;
      int teste = (p - 1) * (q - 1);

      int d; // Expoente da descriptografia, é o inverso de e.d ≡ 1 mod teste.
      int mdc, s, t, x; // Parametros para encontrar "d".

      mdc = mdc_extendido(e, teste, &s, &t);
      if (mdc == 1)
      {
        x = (1 * s) % teste;
        d = unica(x, teste);
        printf("Valor de D: %d\n", d);
      }
      else
      {
        printf("Algo deu errado com a coprimalidade do expoente d escolhido\n");
      }
      //Maneira alternativa de calcular d, usando a expressao de fi (teste)
      //d = ( (2 * teste) + 1 )/ e ;

      FILE *descripto; // Arquivo txt
      descripto = fopen("desencriptada.txt", "w");

      if (descripto == NULL)
      {
        printf("Erro na criação do arquivo!\n");
        return 1;
      }

      int i;
      long long int fator; // Parametro de desencriptografia

      for (i = 0; i < tamanho-1; i++)
      {

        fator = expRapida_mod (C[i], d, n);

        M[i] = descriptografia(fator);

        fprintf(descripto, "%c", M[i]);
      }

      fclose(descripto);
      printf("Mensagem Desencriptada com sucesso!\n");
    }
  }

  return 0;
}