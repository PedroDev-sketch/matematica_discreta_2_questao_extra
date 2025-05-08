#include <stdio.h>

//Aluno: Pedro Teixeira Moriel Sanchez

long long algoritmo_de_euclides(long long G, long long n)
{
    long long sg = G, sn = n;
    printf("Iniciando o Algoritmo de Euclides...\n");
    
    printf("\n");
    while(G)
    {
        printf("%lld mod %lld = %lld\n", n, G, n%G);
        long long temp = n;
        n = G;
        G = temp%G;
    }

    printf("mdc(%lld, %lld) = %lld\n", sg, sn, n);

    return (n == 1 ? 1 : 0);
}

long long divisoes_sucessivas(long long G, long long n)
{
    long long saveG = G, saveN = n;
    printf("\nIniciando Divisoes Sucessivas...\n");
    printf("Iremos calcular %lld^-1 em %lld\n\n", G, n);

    printf("%lldx + %lldy = 1\n", n, G);
    long long rem=1, div;

    long long x0=1, y0=0, x1=0, y1=1;

    while(G)
    {
        div = n/G;
        rem = n%G;

        printf("%lld = %lld * %lld + %lld\n", n, G, div, rem);

        long long itx = x0 - div*x1;
        long long ity = y0 - div*y1;

        x0=x1, y0=y1, x1=itx, y1=ity;

        n = G;
        G = rem;
    }

    if(y0 < 0)
    {
        printf("O inverso modular obtido (%lld) nao pertence a Z%lld\n", y0, saveN);
        printf("Faremos o modulo do inverso obtido por %lld, assim obtendo a resposta apropriada.\n", saveN);
        y0 += saveN;
    }

    printf("\nO inverso modular de %lld eh: %lld\n", saveG, y0);

    return y0;
}

long long algoritmo_de_euclides_silencioso(long long G, long long n)
{
    //Faz a mesma coisa que o normal, mas sem printar o processo no terminal
    //Vai ser usado para calcular phi

    long long sg = G, sn = n;
    
    while(G)
    {
        long long temp = n;
        n = G;
        G = temp%G;
    }

    return (n == 1 ? 1 : 0);
}

long long ehprimo(long long num)
{
    long long count = 0, div=num;
    printf("Os divisores de %lld sao: ", num);

    while(div)
    {
        if(num % div == 0)
        {
            count++;
            printf("%lld ", div);
        }
        div--;
    }
    printf("\n");

    return count==2;
}

int main()
{
    long long H, G, n;

    printf("\nCalcularemos a^x mod n1\n");
    printf("Para isso, precisaremos descobrir a:\n");
    printf("a eh dado pela divisao modular de H por G em Zn\n");

    printf("\nTrocando G por G^-1, podemos fazer uma multiplicacao modular para \nobter o resultado da divisao.\n");
    printf("G^-1 eh o numero que, multiplicado por G em n, resulta em 1.\n");

    printf("\nEscolha H: ");
    scanf("%lld", &H);

    printf("Escolha G: ");
    scanf("%lld", &G);

    printf("Escolha n: ");
    scanf("%lld", &n);

    printf("\nVerificaremos se G e n sao coprimos, provando a existencia de um G^-1\n");
    long long coprimo = algoritmo_de_euclides(G,  n);
    if(!coprimo)
    {
        printf("\n%lld e %lld nao sao coprimos, impossibilitando a divisao!\n", n, G);
        return 0;
    }
    else printf("\n%lld e %lld sao coprimos!\n", n, G);

    long long inverso = divisoes_sucessivas(G, n);

    long long a = (H * inverso) % n;
    printf("\nRealizando a multiplicacao modular, descobrimos que a eh: %lld\n", a);

    printf("\nAgora que temos o a, voce pode escolher os valores de x e n1.\n");

    long long x, n1;

    printf("\nEscolha x: ");
    scanf("%lld", &x);

    printf("Escolha n1: ");
    scanf("%lld", &n1);

    if(n1 == 1)
    {
        printf("\nComo n1 = 1, podemos afirmar que a^x mod n1 = 0, afinal, todo numero eh divisivel por 1.\n");
        return 0;
    }

    printf("Agora veremos se a e n1 sao coprimos, relembrando, se eles forem coprimos, o mdc entre eles sera 1.\n");
    coprimo = algoritmo_de_euclides(a, n1);

    if(!coprimo)
    {
        printf("\n%lld e %lld nao sao coprimos!\n", a, n1);
        return 0;
    }
    else printf("\n%lld e %lld sao coprimos!\n", a, n1);

    printf("\nVerificacao se %lld(n1) eh primo:\n", n1);
    long long n1primo = ehprimo(n1);

    long long x1;
    if(n1primo) 
    {
        //Fermat
        x1=n1-1;
        printf("\nLogo, n1 eh primo, usaremos Fermat.\n");

        printf("\nA primeira coisa a conferir, eh se n1 divide a.\n");
        printf("a mod n1\n");
        printf("%lld mod %lld = %lld", a, n1, a%n1);

        if(a%n1 == 0)
        {
            printf("\nComo p divide a, o modulo eh 0.\n");
            return 0;
        }

        printf("\nComo p nao divide a, podemos seguir.\n");

        printf("Seguindo o Pequeno Teorema de Fermat, e as afirmacoes previas,\n");
        printf("podemos dizer que a^(n1 - 1) eh congruente a 1 mod n1\n");

        printf("\nDefinimos x1 como n1 - 1.\n");
    }


    else 
    {
        //Euler
        printf("\nLogo, n1 nao eh primo, usaremos Euler\n");

        x1=0;

        printf("Ja conferimos se a e n1 sao coprimos\n");
        if(coprimo) printf("e sabemos que eles sao coprimos, logo, podemos prosseguir com Euler.\n");
        else {printf("e sabemos que eles nao sao coprimos, impossibilitando euler.\n");return 0;}

        printf("Seguindo o Teorema de Euler, temos a^phi(n1) eh congruente a 1 mod n1\n");
        printf("Sendo phi(n1) os numeros iguais e menores que n1, que sao seus coprimos\n");

        long long buffern1 = n1;
        printf("\nOs coprimos de n1 sao:\n");
        while(buffern1)
        {
            if(algoritmo_de_euclides_silencioso(n1, buffern1))
            {
                x1++;
                printf("%lld ", buffern1);
            }
            buffern1--;
        }

        printf("\nLogo, phi(n1) = %lld\n", x1);
        printf("\nDefinimos x1 como phi(n1).\n");
    }

    printf("\nUtilizando o Teorema da Divisao para decompor o expoente x (%lld):\n", x);
    long long q = x/x1, r = x%x1;
    printf("%lld = %lld * %lld + %lld\n", x, x1, q, r);

    printf("\nTomando essa decomposicao em conta, podemos alterar a^x mod n1:\n");
    printf("%lld^%lld mod %lld\n", a, x, n1);
    printf("%lld^(%lld * %lld + %lld) mod %lld\n", a, x1, q, r, n1);
    printf("((%lld^(%lld * %lld) mod %lld) * (%lld^%lld mod %lld)) mod %lld\n", a, x1, q, n1, a, r, n1, n1);
    printf("(((%lld^%lld)^%lld mod %lld) * (%lld^%lld mod %lld)) mod %lld\n", a, x1, q, n1, a, r, n1, n1);

    printf("\nCalculando os valores intermediarios:\n");

    long long x2=1;
    printf("\nx2 = a^x1 mod n1\n");
    printf("x2 = %lld^%lld mod %lld:\n", a, x1, n1);
    printf("Como definimos previamente, por ");
    if(n1primo) printf("Fermat\n");
    else printf("Euler\n");
    printf("%lld^%lld mod %lld congruente a 1 mod %lld\n", a, x1, n1, n1);
    printf("\nOu seja, x2 = 1\n");

    printf("\nx2^q mod n1\n");
    printf("%lld^%lld mod %lld:\n", x2, q, n1);
    printf("Como x2 eh igual a 1, esse valor intermediario tambem eh igual a 1.\n");

    printf("\n%lld^%lld mod %lld:\n", a, r, n1);
    long long bufferr=r, buffera=1;
    while(bufferr--) buffera *= a;
    long long ans = buffera%n1;
    printf("%lld^%lld mod %lld = %lld\n", a, r, n1, ans);

    printf("\nNo fim das contas, temos:\n");
    printf("((%lld^%lld) * (%lld^%lld)) mod %lld\n", x2, q, a, r, n1);
    printf("((%lld^%lld) mod %lld * (%lld^%lld) mod %lld) mod %lld\n", x2, q, n1, a, r, n1, n1);
    printf("\n Utilizando os valores intermediarios descobertos:\n");
    printf("(%lld^%lld) mod %lld = 1\n", x2, q, n1);
    printf("(%lld^%lld) mod %lld = %lld\n", a, r, n1, ans);
    printf("\n%lld mod %lld = %lld\n", ans, n1, ans%n1);

    return 0;
}