#include "stdafx.h"
#include <stdlib.h>
#include <string.h>

struct Racun {
	int ukupno=0;
	void ispis() {
		printf("Ukupan racun iznosi: \t %d \n\n", ukupno);
	}
};
char** Alociranje() {
	char **arr = (char **)malloc(100 * sizeof(char *));
	for (int i = 0; i < 100; i++) {
		arr[i] = (char *)malloc(30 * sizeof(char));
	}
	return arr;
}
struct blagajna : public Racun {
	Racun racun;
	char **cuga = Alociranje();
	int cijena[100];
	FILE *fpRacun;
	void Sort(int sort, int i) {
		if (sort == 1)
		{
			SortiranjeAbecedno(i);
		}
		else
		{
			SortiranjePoCijeni(i);
		}
	}
	void SortiranjePoCijeni(int i) {
		char temp[30];
		int Ctemp;
		for (int j = 0; j < i; j++)
		{
			for (int k = 0; k < i-1; k++)
			{
				if (cijena[k]>cijena[k+1])
				{
					Ctemp = cijena[k];
					cijena[k] = cijena[k+1];
					cijena[k+1] = Ctemp;
					strcpy(temp, cuga[k]);
					strcpy(cuga[k], cuga[k+1]);
					strcpy(cuga[k + 1], temp);
				}
			}
		}
	}
	void SortiranjeAbecedno(int i) {
		char temp[30];
		int Ctemp;
		for (int j = 0; j < i; j++)
		{
			for (int k = 0; k < i - 1; k++)
			{
				if (strcmp(cuga[k],cuga[k+1])>0)
				{
					Ctemp = cijena[k];
					cijena[k] = cijena[k + 1];
					cijena[k + 1] = Ctemp;
					strcpy(temp, cuga[k]);
					strcpy(cuga[k], cuga[k + 1]);
					strcpy(cuga[k + 1], temp);
				}
			}
		}
	}
	void brisanje(int i, FILE*fp, FILE*fp1) {
		int i_izbor = NULL, flag = 0;
		do {
			for (int k = 0; k < i; k++)
			{
				ispis(k);
			}
			printf("\t %d. Izlaz \n\n", i + 1);
			printf("Unesite broj:");
			scanf("%d", &i_izbor);
			getchar();
			printf("\n");
			if (i_izbor == i + 1)
			{
				break;
			}
			else if (i_izbor < i + 1 && i_izbor>0)
			{
				do
				{
					printf("Obrisano pice je: %s\t\t\t%d kn\n\n-------------\n", cuga[i_izbor - 1], cijena[i_izbor - 1]);
					for (int c = i_izbor - 1; c < i - 1; c++)
					{
						for (int k = 0; k < 30 - 1; k++)
						{
							cuga[c][k] = cuga[c + 1][k];
						}
						cijena[c] = cijena[c + 1];
					}
					i--;
					break;
				} while (flag == 0);

			}
			else {
				printf("Krivo je uneseno, unesite ponovno.\n\n");
			}
		} while (flag == 0);
		for (int k = 0; k < i; k++)
		{
			fprintf(fp, "%s", cuga[k]);
			fprintf(fp1, "%d\n", cijena[k]);
		}
	}
	void ispis(int i) {
		printf("\t %d. %s \t", i + 1, cuga[i]);
		printf("\t %d kn", cijena[i]);
		printf("\n");
	}
	int ucitavanje(FILE*fp, FILE*fp1) {
		int i = 0;
		while (fgets(cuga[i], 30, fp) && fscanf(fp1, "%d", &cijena[i])) {
			i++;
		}
		return i;
	}
	void Odabir(int i) {
		int i_izbor = NULL, flag = 0;
		do {
			printf("Unesite broj:");
			scanf("%d", &i_izbor);
			getchar();
			printf("\n");
			if (i_izbor == i + 1)
			{
				break;
			}
			else if (i_izbor < i + 1 && i_izbor>0)
			{
				do
				{
					printf("Izabran je: \t %s \t\t\t %d \n\n", cuga[i_izbor - 1], cijena[i_izbor - 1]);
					racun.ukupno += cijena[i_izbor - 1];
					fprintf(fpRacun, "%s \t %d kn \n", cuga[i_izbor - 1], cijena[i_izbor - 1]);
					break;
				} while (flag == 0);

			}
			else {
				printf("Krivo je uneseno, unesite ponovno.\n\n");
			}
		} while (flag == 0);
	}
	void ObrisiNapitak() {
		int i = 0;
		FILE *fp = fopen("cuga.txt", "r");
		FILE *fp1 = fopen("cijena_cuge.txt", "r");
		printf("Izaberite pice za obrisati:");
		printf("\n");
		i = ucitavanje(fp, fp1);
		fclose(fp);
		fclose(fp1);
		fp = fopen("cuga.txt", "w");
		fp1 = fopen("cijena_cuge.txt", "w");
		brisanje(i, fp, fp1);
		fclose(fp);
		fclose(fp1);
	}
	void ObrisinAkciju() {
		int i = 0;
		FILE *fp = fopen("akcije.txt", "r");
		FILE *fp1 = fopen("cijena_akcije.txt", "r");
		printf("Izaberite akciju za obrisati:");
		printf("\n");
		i = ucitavanje(fp, fp1);
		fclose(fp);
		fclose(fp1);
		fp = fopen("akcije.txt", "w");
		fp1 = fopen("cijena_akcije.txt", "w");
		brisanje(i, fp, fp1);
		fclose(fp);
		fclose(fp1);
	}
	void ObrisiAlkohol() {
		int i = 0;
		FILE *fp = fopen("alkohol.txt", "r");
		FILE *fp1 = fopen("cijena_alkohola.txt", "r");
		printf("Izaberite alkohol za obrisati:");
		printf("\n");
		i = ucitavanje(fp, fp1);
		fclose(fp);
		fclose(fp1);
		fp = fopen("alkohol.txt", "w");
		fp1 = fopen("cijena_alkohola.txt", "w");
		brisanje(i, fp, fp1);
		fclose(fp);
		fclose(fp1);
	}
	void ispisNapitaka(int sort) {
		int i_izbor = NULL, i = 0;
		FILE *fp = fopen("cuga.txt", "r");
		FILE *fp1 = fopen("cijena_cuge.txt", "r");
		printf("Izaberite jedno od pica:");
		printf("\n");
		i = ucitavanje(fp, fp1);
		Sort(sort, i);
		for (int k = 0; k < i; k++)
		{
			ispis(k);
		}
		fclose(fp);
		fclose(fp1);
		printf("\t %d. Izlaz \n\n", i + 1);
		Odabir(i);
	}
	void ispisAkcije(int sort) {
		int i_izbor = NULL, i = 0;
		FILE *fp = fopen("akcije.txt", "r");
		FILE *fp1 = fopen("cijena_akcije.txt", "r");
		printf("Izaberite jedno od pica:");
		printf("\n");
		i = ucitavanje(fp, fp1);
		Sort(sort, i);
		for (int k = 0; k < i; k++)
		{
			ispis(k);
		}
		fclose(fp);
		fclose(fp1);
		printf("\t %d. Izlaz \n\n", i + 1);
		Odabir(i);
	}
	void ispisAlkohola(int sort) {
		int i_izbor = NULL, i = 0;
		FILE *fp = fopen("alkohol.txt", "r");
		FILE *fp1 = fopen("cijena_alkohola.txt", "r");
		printf("Izaberite jedno od pica:");
		printf("\n");
		i = ucitavanje(fp, fp1);
		Sort(sort, i);
		for (int k = 0; k < i; k++)
		{
			ispis(k);
		}
		fclose(fp);
		fclose(fp1);
		printf("\t %d. Izlaz \n\n", i + 1);
		Odabir(i);
	}
};

void Dodajnapitak() {
	char naziv[30];
	int cijena = NULL;
	FILE *fp = fopen("cuga.txt", "a+");
	FILE *fp1 = fopen("cijena_cuge.txt", "a+");
	printf("Unesite naziv napitka ili broj 0 za izlaz: ");
	fgets(naziv, 30, stdin);
	if (strcmp(naziv,"0")==1)
	{
		printf("------------------\n\n");
		return;
	}
	do {
		printf("Unesite cijenu napitka: ");
		scanf("%d", &cijena);
		if (cijena <= 0)
		{
			printf("Nepravilno unesena cijena, molim unesite ponovno. \n\n");
		}
	} while (cijena <= 0);
	fprintf(fp, "%s", naziv);
	fprintf(fp1, "%d\n", cijena);
	fclose(fp);
	fclose(fp1);
	printf("\n ---------------- \n\n");
}
void Dodajakciju() {
	char naziv[40];
	int cijena = NULL;
	FILE *fp = fopen("akcije.txt", "a+");
	FILE *fp1 = fopen("cijena_akcije.txt", "a+");
	printf("Unesite naziv akcije: ");
	fgets(naziv, 40, stdin);
	if (strcmp(naziv, "0") == 1)
	{
		printf("------------------\n\n");
		return;
	}
	do {
		printf("Unesite cijenu akcije: ");
		scanf("%d", &cijena);
		if (cijena <= 0)
		{
			printf("Nepravilno unesena cijena, molim unesite ponovno. \n\n");
		}
	} while (cijena <= 0);
	fprintf(fp, "%s", naziv);
	fprintf(fp1, "%d\n", cijena);
	fclose(fp);
	fclose(fp1);
	printf("\n ---------------- \n\n");
}
void Dodajalkohol() {
	char naziv[30];
	int cijena = NULL;
	FILE *fp = fopen("alkohol.txt", "a+");
	FILE *fp1 = fopen("cijena_alkohola.txt", "a+");
	printf("Unesite naziv alkoholnog pica: ");
	fgets(naziv, 30, stdin);
	if (strcmp(naziv, "0") == 1)
	{
		printf("------------------\n\n");
		return;
	}
	do {
		printf("Unesite cijenu alkoholnog pica: ");
		scanf("%d", &cijena);
		if (cijena <= 0)
		{
			printf("Nepravilno unesena cijena, molim unesite ponovno. \n\n");
		}
	} while (cijena <= 0);
	fprintf(fp, "%s", naziv);
	fprintf(fp1, "%d\n", cijena);
	fclose(fp);
	fclose(fp1);
	printf("\n ---------------- \n\n");
}

int main()
{
	FILE *fpRacun = fopen("racun.txt", "w");
	blagajna blagajnaA;
	blagajnaA.fpRacun = fpRacun;
	int flag = 0, izbor, i=0;
	fputs("Racun: \n", fpRacun);
	do
	{
		printf("Izbornik:\n");
		printf("1. Napitci:\n");
		printf("2. Akcije:\n");
		printf("3. Alkohol:\n");
		printf("4. Ispis:\n");
		printf("5. Dodaj napitak:\n");
		printf("6. Dodaj akciju:\n");
		printf("7. Dodaj alkohol:\n");
		printf("8. Obrisi napitak:\n");
		printf("9. Obrisi akciju:\n");
		printf("10. Obrisi alkohol:\n");
		printf("11. Izlaz:\n");
		printf("Unesite broj: ");
		scanf("%d",&izbor);
		getchar();
		printf("\n");
		switch (izbor) {
		case 1:
			printf("Ispis napitaka abecedno (1) ili po cijeni (2) ? ");
			do {
				scanf("%d", &i);
			} while (i != 1 && i != 2);
			printf("\n");
			blagajnaA.ispisNapitaka(i);
			i = 0;
			break;
		case 2:
			printf("Ispis napitaka abecedno (1) ili po cijeni (2) ? ");
			do {
				scanf("%d", &i);
			} while (i != 1 && i != 2);
			printf("\n");
			blagajnaA.ispisAkcije(i);
			i = 0;
			break;
		case 3:
			printf("Ispis napitaka abecedno (1) ili po cijeni (2) ? ");
			do {
				scanf("%d", &i);
			} while (i != 1 && i != 2);
			printf("\n");
			blagajnaA.ispisAlkohola(i);
			i = 0;
			break;
		case 4:
			blagajnaA.racun.ispis();
			break;
		case 5:
			Dodajnapitak();
			break;
		case 6:
			Dodajakciju();
			break;
		case 7:
			Dodajalkohol();
			break;
		case 8:
			blagajnaA.ObrisiNapitak();
			break;
		case 9:
			blagajnaA.ObrisinAkciju();
			break;
		case 10:
			blagajnaA.ObrisiAlkohol();
			break;
		case 11:
			fprintf(fpRacun, "Ukupno: \t %d kn \n", blagajnaA.racun.ukupno);
			fclose(fpRacun);
			flag = 1;
			break;
		default:
			printf("Nije dobro uneseno, molim unesite ponovno\n");
			break;
		}
	} while (flag==0);
    return 0;
}