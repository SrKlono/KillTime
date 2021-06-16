#include <stdio.h>  //std stuff 
#include <stdlib.h> //std stuff too
#include <conio.h> //pra usar o getch, getchar, system, etc.
#include <ctype.h> //pra mecher cm texto (toupper)
#include <TIME.H> //usei pro timer
#include <string.h> //manipular string usei no array d inimigos

//stats pers

char nome[16];
char classe[30];

int hpMax = 10;
double hpAtual = 10;

double atk = 3;
double def = 0.5;
int desvio = 2;

int level = 1;

int xp = 0;
int xpTNL = 10; //xp to next level

char local[30] = "Floresta";

//stats inim
double hpInim = 4;
char nomeInim[16] = "Slime";
double atkInim = 1;
int xpGanho = 2;

//util
char ch; //selecao de acao do pers
int i; //getch's
int dc; //calculo do dodge

//timer
void delay(int number_of_seconds)
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;

	// Storing start time
	clock_t start_time = clock();

	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds);
}

int Floresta() {
	strcpy_s(local, _countof(local), "Floresta");

	int ec;
	ec = rand() % (5 + 1 - 1) + 1;

	switch (ec) {
	case 1:
		strcpy_s(nomeInim, _countof(nomeInim), "Goblin");
		hpInim = 6;
		atkInim = 2;
		xpGanho = 3;
		break;
	case 2:
		strcpy_s(nomeInim, _countof(nomeInim), "Slime");
		hpInim = 4;
		atkInim = 1;
		xpGanho = 2;
		break;
	case 3:
		strcpy_s(nomeInim, _countof(nomeInim), "Morcego");
		hpInim = 4;
		atkInim = 3;
		xpGanho = 5;
		break;
	case 4:
		strcpy_s(nomeInim, _countof(nomeInim), "Golem");
		hpInim = 8;
		atkInim = 1;
		xpGanho = 2;
		break;
	case 5:
		strcpy_s(nomeInim, _countof(nomeInim), "Zumbi");
		hpInim = 4;
		atkInim = 4;
		xpGanho = 5;
		break;
	}

	return hpInim, atkInim, xpGanho;
}

int Cemiterio() {
	strcpy_s(local, _countof(local), "Cemiterio");
	
	int ec;
	ec = rand() % (5 + 1 - 1) + 1;

	switch (ec) {
	case 1:
		strcpy_s(nomeInim, _countof(nomeInim), "Ghoul");
		hpInim = 7;
		atkInim = 3;
		xpGanho = 4;
		break;
	case 2:
		strcpy_s(nomeInim, _countof(nomeInim), "Necromante");
		hpInim = 4;
		atkInim = 3;
		xpGanho = 2;
		break;
	case 3:
		strcpy_s(nomeInim, _countof(nomeInim), "Esqueleto");
		hpInim = 6;
		atkInim = 4;
		xpGanho = 5;
		break;
	case 4:
		strcpy_s(nomeInim, _countof(nomeInim), "Vampiro");
		hpInim = 8;
		atkInim = 3;
		xpGanho = 5;
		break;
	case 5:
		strcpy_s(nomeInim, _countof(nomeInim), "Zumbi");
		hpInim = 4;
		atkInim = 4;
		xpGanho = 5;
		break;
	}

	return hpInim, atkInim, xpGanho;
}



void enemyChooser() {
	if (level < 5) {
		Floresta();
	}
	if (level >= 5) {
		Cemiterio();
	}
}


int levelUp() {
	level = level + 1;
	hpMax = hpMax + 5;
	hpAtual = hpMax;
	atk = atk + 1;

	return atk, hpAtual, hpMax;
}

//combate 
void Combat() {
	do {
		printf("_______________________________________________________________________________________________________________________\n");
		printf("                                                                                                                       \n");
		printf("             Nome: %s                   Classe: %s                   Lv: %d                   HP: %.1f/%d\n", nome, classe, level, hpAtual, hpMax); //stats UI
		printf("_______________________________________________________________________________________________________________________\n\n");

		printf("\n	Local: %s\n\n\n\n", local);

		printf("                         Inimigo: %s                                           HP: %.0f\n\n", nomeInim, hpInim);
		
		printf("\n\n\n\n\n");
		
		printf(".===========================================================.==========================================================.\n");
		printf("|                                                           |                                                          |\n");
		printf("|                        (A)tacar                           |                        (B)loquear                        |\n");
		printf("|                                                           |                                                          |\n");
		printf("|-----------------------------------------------------------+----------------------------------------------------------|\n");
		printf("|                                                           |                                                          |\n");
		printf("|                        (F)ugir                            |                        (D)esviar                         |\n");
		printf("|                                                           |                                                          |\n");
		printf("'==========================================================='=========================================================='\n");

		ch = toupper(_getch());

		switch (ch)
		{
		case 'A':
			hpInim = hpInim - atk;

			printf("Voc%c ataca o %s causando %.1f de dano", 136, nomeInim, atk);
			printf("."); 	delay(1); printf("."); 	delay(1); printf("."); delay(1);

			if (hpInim > 0) {
				hpAtual = hpAtual - atkInim * (def * 1.2);

				printf(" %s ataca de volta causando %.1f de dano", nomeInim, atkInim * (def * 1.2));
				delay(2);
			}
			break;

		case 'D':
			dc = rand() % (desvio + 1 - 1) + 1; //1 = falha; 2 >= sucesso;

			printf("Voc%c tenta desviar", 136);
			printf("."); 	delay(1); printf("."); 	delay(1); printf("."); delay(1);
			if (dc >= 2) {
				hpInim = hpInim - atk * 1.2;

				printf(" e concegue! Causando em retorno %.1f de dano", atk * 1.2);
				delay(2);
			}
			else {
				hpAtual = hpAtual - atkInim * 1.2;
				printf(" e falha... Recebeu %.1f de dano", atkInim * 1.2);
				delay(2);
			}
			break;

		case 'B':
			hpInim = hpInim - atk * 0.7;
			hpAtual = hpAtual - atkInim * def;

			printf("Voc%c bloqueia recebendo %.1f de dano", 136, atkInim * def);
			printf("."); 	delay(1); printf("."); 	delay(1); printf(".\n"); delay(1);
			printf("E devolvendo %.1f de dano", atk * 0.7);
			delay(2);
			break;

		case 'F':
			printf("Voc%c n%co concegue fugir", 136, 198);
			printf("."); 	delay(1); printf("."); 	delay(1); printf("."); delay(1);
			break;
		}

		if (hpInim <= 0) {

			xp = xp + xpGanho;
			printf("\n\n%s morreu. Voc%c ganhou %d de xp", nomeInim, 136, xpGanho);
			delay(3);

			if (xp >= xpTNL) {
				//xp = 0; ativar quando acabar os testes
				xpTNL = xpTNL + 5;

				printf(" **Voc%c subiu de nivel!**",136);
				delay(3);

				levelUp();
			}

			
			enemyChooser();

		}
		system("cls");
	} while (hpAtual > 0);
}

//criacao de pers
static void newGame() {
	printf("\n	Digite seu nome: ");
	scanf_s("%s", &nome, (unsigned)_countof(nome));

	system("cls");

	int osd;

	classLoop:
	printf("\n   Escolha uma [classe]:\n\n");

	printf("	[1] Guerreiro - Ataque e defesa balanceados\n");
	printf("	[2] Paladino  - Pouco ataque, mas uma defesa concideravelmente alta\n");
	printf("	[3] Berserker - Muito ataque, pouca defesa\n");
	printf("	[4] Rogue     - Pouco ataque, defesa decente, e uma grande chance de desviar\n");

	osd = _getch();

	switch (osd)
	{
	case 49:
		strcpy_s(classe, _countof(classe), "Guerreiro");
		atk = 3;
		def = 0.4;
		break;
	case 50:
		strcpy_s(classe, _countof(classe), "Paladino");
		atk = 2;
		def = 0.3;
		break;
	case 51:
		strcpy_s(classe, _countof(classe), "Berserker");
		atk = 5;
		def = 0.6;
		break;
	case 52:
		strcpy_s(classe, _countof(classe), "Rogue");
		atk = 2;
		def = 0.6;
		desvio = 4;
		break;
	default:
		printf("\nEssa n%co %c uma classe valida!", 198, 130);
		delay(3);
		system("cls");
		goto classLoop;
	}


	printf("\n\n	%s o %s, entendi, vamos come%car ent%co", nome, classe, 135, 132);
	delay(1); printf("."); 	delay(1); printf("."); 	delay(1); printf("."); delay(1);
	system("cls");
	Combat();
}

void menu() {

loadLoop:

	printf("\n	[1] New Game");
	printf("\n	[2] Load Game");

	ch = _getch();


	switch (ch)
	{
	case 49:
		system("cls");
		newGame();
		break;
	case 50:
		printf("\n\n	Essa n%co %c uma opc%co valida!", 198, 130, 198);
		delay(3);
		system("cls");
		goto loadLoop;
		break;
	default:
		printf("\n\n	Essa n%co %c uma opc%co valida!", 198, 130, 198);
		delay(3);
		system("cls");
		goto loadLoop;
	}
}

// titlescreen
void main() {
	printf("\n					        |  .  |  |    _|_ . __  _ \n					        |< |  |  |     |_ | |||(/_\n\n");
	printf("					 --Precione qualquer tecla para come%car--\n", 135);
	ch = _getch();
	system("cls");
	menu();
}
