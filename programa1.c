/*

 * programa1.c
 *
 *  Created on: Aug 15, 2011
 *      Authors: Pedro Artur F. Vitti
 *     			 Luiz Paulo de Farias Junior
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/*Pega a variável de ambiente*/
extern char **environ;

/*Seta a flag verbose*/
int interativo = 0;

char *c_ptr;

void printHelp() {
	printf("\nuso: ./programa1 [-h] [-a] [-e] [-t VARIAVEL] [-v]");
	printf("\n");
	printf("\n-h, --help");
	printf("\n\tajuda, imprime essa mensagem com a forma de usar o comando");
	printf("\n\tna saída padrão stdout");
	printf("\n");
	printf("\n-a, --arguments");
	printf("\n\timprime os argumentos da linha de comando, 1 por linha");
	printf("\n ");
	printf("\n-e, --environment ");
	printf("\n\timprime as variáveis de ambiente, 1 por linha");
	printf("\n");
	printf("\n-t, --variavel [VARIAVEL]");
	printf("\n\timprime o valor da  de ambiente, 1 por linha, no estilo");
	printf("\n\tvariável = ‘algumacoisa’");
	printf("\n");
	printf("\n-v, --verbose");
	printf("\n\tmodo interativo, imprime informações adicionais sobre os valores obtidos pela");
	printf("\n\tfunção getopt() ou getopt_long()\n\n");
}

int
main(argc, argv)
int argc;
char **argv;
{
	if(argc == 1)
		printHelp();

	int c;

	while (1) {
		static struct option long_options[] = {
				{"help", 		0, 0, 'h'},
				{"arguments", 	0, 0, 'a'},
				{"environment", 0, 0, 'e'},
				{"variavel", 	1, 0, 't'},
				{"verbose", 	0, 0, 'v'},
				{ 0,			0, 0,  0 }
		};
		/*getopt_long stores the option index here.*/
		int option_index = 0;

		c = getopt_long (argc, argv, "haet:v", long_options, &option_index);

		/*Fim das opcoes.*/
		if (c == -1)
			break;

		switch (c) {

		case 'h':{
			printHelp();
			break;
		}
		case 'a':{
			printf("\nopcao -a: Argumentos:\n\n");
			int k;
			/*Ultima posição de arg eh sempre null*/
			for (k = 0; k < argc-1; k++)
				printf ("argv[%d]=%s\n", k, argv[k]);
			printf("\n");
			break;
		}
		case 'e':{
			printf("\nopcao -e: Variaveis de Ambiente:\n\n");
			int j = 0;
			for ( ; *environ; ++environ)
				printf("envp[%i]='%s'\n",j++,*environ);
			printf("\n");
			break;
		}
		case 't':{
			c_ptr = getenv(optarg);
			printf("opcao -t: %s='%s'\n",optarg, c_ptr==NULL ? "NAO ENCONTRADA\n" : c_ptr );
			break;
		}
		case 'v':{
			interativo = 1;
			printf ("opcao -v: Modo Interativo Ativado\n");
			break;
		}
		case '?':
			/*getopt_long already printed an error message.*/
			break;

		default:
			abort ();

		}
		if (interativo==1)
				printf("getopt: c=%c, argumento = %s\n",c,optarg);
	}

	/*Imprime argumentos inválidos*/
	if (optind < argc)	{
		printf ("Argumentos não válidos:\n ");
		while (optind < argc)
			printf ("%s\n", argv[optind++]);
		putchar ('\n');
	}

	exit (0);
}
