/*
 ============================================================================
 Name        : Spotify Simulator 2018
 Author      : Antonio Pansini
 Version     : 1.0
 Copyright   : Progetto creato da Antonio Pansini - Laboratorio di Programmazione ITPS B 2016/2017 UniBA
 Description : Questo programma simula alcune funzionalità di Spotify. Per ulteriori informazioni, consultare la documentazione allegata
 ============================================================================
 */

#include "varlib.h"
#include "artisti.h"
#include "utenti.h"
#include "preferenze.h"

// Il programma inizia con la funzione main
int main() {

	system("COLOR 0A");

	// Dichiarazione di variabili utilizzate nel main
	int a = 0;
	int b = 0;
	FILE *aPtr = 0;
	char scelta[1];
	int scelta_num = 0;

	// Necessario per visualizzare l'output del processo nella console di Eclipse
	setvbuf(stdout, NULL, _IONBF, 0);

	// Schermata di benvenuto all'utente
	printf("Spotify Simulator 2018 - La musica e' di casa.\n\n");
	system("pause");
	system("cls");

	// Ciclo che determina le possibili scelte dell'utente (menù iniziale)
	while (a != 1) {

		printf("MENU' PRINCIPALE\n\n");
		printf("1. Apri il menu' degli artisti\n2. Apri il menu' degli utenti\n3. Apri il menu' delle preferenze\n4. Esci da Spotify Simulator\n");
		scanf("%s", scelta);
		system("cls");

		// Se il carattere inserito "scelta" è una lettera, restituisce un messaggio di errore
		if (isalpha(scelta[0]))
			printf("Errore\n");

		else {

			// Converte la variabile "scelta" da carattere a intero e la assegna alla variabile "scelta_num"
			scelta_num = atoi(scelta);

			// Menù artisti
			switch (scelta_num) {

			case 1:
				printf("Menu' degli artisti\n\n");

				b = 0;
				while (b != 1) {

					printf("1. Aggiungi un artista\n2. Modifica un artista\n"
							"3. Visualizza gli artisti in elenco\n4. Ricerca di un artista\n"
							"5. Elimina un artista\n6. Classifica artisti piu' ascoltati\n7. Torna al menu' principale\n");
					scanf("%s", scelta);
					system("cls");

					if (isalpha(scelta[0]))
						printf("Errore\n");

					else {

						scelta_num = atoi(scelta);

						// Chiamata delle funzioni relative agli artisti tramite selezione multipla
						switch (scelta_num) {

						case 1:
							aggiunta_artisti (aPtr);
							break;

						case 2:
							modifica_artista (aPtr);
							break;

						case 3:
							system("cls");
							visual_artisti (aPtr);
							break;

						case 4:
							ricerca_artisti (aPtr);
							break;

						case 5:
							elimina_artista (aPtr);
							break;

						case 6:
							artisti_piu_ascoltati (aPtr);
							break;

						case 7:
							b = 1;
							break;

						default:
							printf("Scelta errata, riprova.\n\n");
							break;

						}

					}

				}

				break;

				// Menù utenti
			case 2:
				printf("Menu' degli utenti\n\n");

				b = 0;
				while (b != 1) {

					printf("1. Aggiungi un utente\n2. Modifica un utente\n"
							"3. Visualizza gli utenti in elenco\n4. Elimina utente\n"
							"5. Visualizza il profilo globale utenti\n6. Torna al menu' principale\n");
					scanf("%s", scelta);
					system("cls");

					if (isalpha(scelta[0]))
						printf("Errore\n");

					else {

						scelta_num = atoi(scelta);

						// Chiamata delle funzioni relative agli artisti tramite selezione multipla
						switch (scelta_num) {

						case 1:
							aggiunta_utenti (aPtr);
							break;

						case 2:
							modifica_utente (aPtr);
							break;

						case 3:
							system("cls");
							visual_utenti (aPtr);
							break;

						case 4:
							elimina_utente (aPtr);
							break;

						case 5:
							profilo_utenti (aPtr);
							break;

						case 6:
							b = 1;
							break;

						default:
							printf("Scelta errata, riprova\n\n");
							break;

						}

					}

				}

				break;

				// Menù preferenze
			case 3:
				printf("Menu' delle preferenze\n\n");

				b = 0;
				while (b != 1) {

					printf("1. Aggiungi preferenza\n2. Elimina preferenza\n3. Torna al menu' principale\n");
					scanf("%s", scelta);
					system("cls");

					if (isalpha(scelta[0]))
						printf("Errore\n");

					else {

						scelta_num = atoi(scelta);

						// Chiamata delle funzioni relative alle preferenze tramite selezione multipla
						switch (scelta_num) {

						case 1:
							aggiunta_pref (aPtr);
							break;

						case 2:
							elimina_pref (aPtr);
							break;

						case 3:
							b = 1;
							break;

						default:
							printf("Scelta errata, riprova\n");
							break;

						}

					}


				}

				break;

				// Salva tutti i file utilizzati e chiude il programma
			case 4:
				printf("Il programma sta per essere terminato...\n");
				sleep(1);

				printf("Grazie per aver utilizzato 'Spotify Simulator 2018 - La musica e' di casa!'\n\n");
				system("pause");
				exit(0);

				break;

				// Se viene inserito un caso non dispoibile, viene ritornato un messaggio di errore
			default:
				printf("Scelta errata, riprova\n\n");
				system("pause");
				system("cls");
				break;

			}
		}
	}
	return 0;
}


