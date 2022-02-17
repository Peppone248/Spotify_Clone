/*
 * artisti.c
 *
 *  Created on: 28 gen 2018
 *      Author: Antonio Pansini
 */

#include "artisti.h"
#include "varlib.h"

// Funzione che aggiunge artisti in un file (TESTARE FUNZIONAMENTO MEMSET)
void aggiunta_artisti (FILE *ptr) {

	// Variabili locali alla funzione
	int a = 0;
	int i = 0;
	int k = 0;
	int n = 0;
	int uguale = 0;

	int fine = 0;
	char scelta[1];
	int scelta_num;

	// Apertura file in scrittura binaria in aggiornamento
	if ((ptr = fopen("artisti.dat", "rb+")) == NULL) {
		printf("ERRORE: File degli artisti non trovato.\n");

		printf("Creare il file degli artisti? 1) Si  2) No\n");

		// Ciclo che determina l'avvenuta apertura del file
		while (a != 1) {
			scanf("%s", scelta);

			if (isalpha(scelta[0]))
				printf("Errore\n");

			else {
				scelta_num = atoi(scelta);

				switch (scelta_num) {

				// Apertura file in scrittura binaria distruttiva
				case 1:
					ptr = fopen("artisti.dat", "wb");
					fclose(ptr);
					printf("Creazione file in corso...\n");
					sleep(1);
					printf("Il file degli artisti e' stato creato.\n");
					system("pause");
					system("cls");
					a = 1;
					break;

					// Uscita dal ciclo in caso di non creazione del file
				case 2:
					a = 1;
					break;

					// Se la scelta non corrisponde ad 1 o 2, il ciclo ricomincia
				default:
					printf("Errore, reinserire numero.");
					break;

				}
			}
		}


	} else {

		do {

			// Il file viene letto fino alla fine, incrementando ad ogni ciclo la posizione dell'offset "i"
			i = 0;
			while (!feof(ptr)) {
				fseek(ptr,i * sizeof(artista), SEEK_SET);
				fread(&artista, sizeof(artista), 1, ptr);
				i++;
			}

			i--;

			printf("Inserisci nome\n");

			// Cicla fino a quando la variabile "n" non è uguale ad 1 (controlli sul nome artista)
			n = 0;
			while (n != 1) {

				uguale = 0;

				// Azzeramento dell'array "artista.nome"
				memset(&artista.nome, 0, sizeof(artista.nome));

				// Acquisizione nome artista
				fflush(stdin);
				gets(artista.nome);

				// Controllo sulla posizione 20 dell'array "artista.nome", se non è vuota stampa un errore
				if (artista.nome[20] != 0)
					printf("ATTENZIONE: Il nome dell'artista non puo' superare i 20 caratteri.\n");

				// Conversione array per scrittura in file, converte ogni posizione
				k = 0;
				while (artista.nome[k]) {
					artista.nome[k] = conversione(artista.nome[k]);
					k++;
				}



				k = 0;
				rewind(ptr);										// Riavvolgimento dello stream, posizione del puntatore a inizio file
				while (!feof(ptr)) {								// Ciclo che termina alla fine del file
					fseek(ptr, k * sizeof(artista), SEEK_SET);		// Posiziona il puntatore alla posizione determinata dall'offset "k"
					fread(&artistatemp, sizeof(artista), 1, ptr);	// Caricamento in memoria della struct "artistatemp"
					if (!strcmp(artistatemp.nome, artista.nome)) {	// Confronto fra le due stringhe "artistatemp.nome" e "artista.nome"
						printf("\nATTENZIONE: L'artista inserito e' gia' presente nel file!\n");	// Se le due stringhe sono uguali, stampa un messaggio di errore e
						uguale = 1;                                 // setta la variabile di controllo "uguale" ad 1
						break;
					}

					k++;
				}

				if (uguale == 0 && artista.nome[20] == 0)	// Se la variabile di controllo "uguale" è 0 e la posizione 20 dell'array "artista.nome" è vuota,
					n++;                                    // esci dal ciclo
			}


			printf("Inserisci genere\n");

			n = 0;
			while (n != 1) {

				memset(&artista.genere, 0, sizeof(artista.genere));

				fflush(stdin);
				gets(artista.genere);

				if (artista.genere[15] != 0)
					printf("ATTENZIONE: Il genere dell'artista non puo' superare i 15 caratteri.\n");

				k = 0;
				while (artista.genere[k]) {

					k++;
				}

				if (artista.genere[15] == 0) {
					n++;
				}

			}


			printf("Inserisci produttore\n");

			n = 0;

			while (n != 1) {

				memset(&artista.prod, 0, sizeof(artista.prod));

				fflush(stdin);
				gets(artista.prod);

				if (artista.prod[25] != 0)
					printf("ATTENZIONE: Il nome del produttore dell'artista non puo' superare i 25 caratteri.\n");

				k = 0;
				while (artista.prod[k]) {
					artista.prod[k] = conversione(artista.prod[k]);
					k++;
				}

				if (artista.prod[25] == 0) {
					n++;
				}
			}


			printf("Inserisci anno di produzione\n");

			n = 0;

			while (n != 1) {

				artista.anno = 0;

				fflush(stdin);
				scanf("%d", &artista.anno);

				// Controllo sull'anno inserito: se è maggiore o uguale a 2019 o minore di 1900, stampa un errore
				// altrimenti, esci dal ciclo
				if (artista.anno < 1900 || artista.anno >= 2019)
					printf("ATTENZIONE: L'anno di produzione deve essere compreso fra 1900 e 2018. "
							"(Non si accettano mummie ne' artisti dal futuro)\n");
				else n++;

			}


			printf("Inserisci nazionalita'\n");

			n = 0;
			while (n != 1) {

				memset(&artista.nazione, 0, sizeof(artista.nazione));

				fflush(stdin);
				gets(artista.nazione);

				if (artista.nazione[15] != 0)
					printf("ATTENZIONE: La nazionalita' dell'artista non puo' superare i 15 caratteri.\n");

				k = 0;
				while (artista.nazione[k]) {
					artista.nazione[k] = conversione(artista.nazione[k]);
					k++;
				}

				if (artista.nazione[15] == 0) {
					n++;
				}
			}

			// Assegna automaticamente l'id all'inserimento di ogni artista nel file
			artista.id++;

			// Posizionamento del puntatore alla posizione i dell'offset
			// e scrittura della struct artista appena acquisita in tale posizione
			fseek(ptr, i * sizeof(artista), SEEK_SET);
			fwrite(&artista, sizeof(artista), 1, ptr);

			printf("Vuoi continuare ad aggiungere artisti? 1) Si  2) No\n");

			a = 0;
			while (a != 1) {
				scanf("%s", scelta);

				if (isalpha(scelta[0]))
					printf("Errore\n");

				scelta_num = atoi(scelta);

				switch (scelta_num) {

				// Il ciclo di aggiunta artisti ricomincia dall'inizio
				case 1:
					printf("Artista aggiunto\n");
					fine = 0;
					a = 1;
					system("pause");
					system("cls");
					break;

					// Interruzione aggiunta artisti. Ritorno al menù principale
				case 2:
					printf("Aggiunta artisti interrotta\n");
					fine = 1;
					a = 1;
					system("pause");
					system("cls");
					break;

				default:
					printf("Errore, reinserire numero.");
					break;

				}
			}

		}

		// Ciclo che determina l'aggiunta dei dati di un artista
		while (fine != 1);
	}

	// Chiusura del file "artisti.dat"
	fclose(ptr);

}


void modifica_artista (FILE *ptr) {

	// Variabili locali alla funzione
	int n = 0;
	int scelta_id = 0;
	int a = 0;
	char scelta[1] = {0};
	int scelta_num = 0;
	int i = 0;
	int k = 0;

	// Apertura file in scrittura binaria in aggiornamento
	if ((ptr = fopen("artisti.dat", "rb+")) == NULL) {
		printf("ERRORE FILE.\n"); }
	else {

		// Cicla fino a quando la variabile "a" non è uguale ad 1 (controllo sull'id artista da ricercare nel file)
		a = 0;
		while (a != 1) {

			// Acquisizione dell'id dell'artista da modificare
			printf("Inserisci id da modificare\n");
			scanf("%d", &scelta_id);

			// Ciclo che scorre il file degli artisti fino alla fine,
			// con caricamento della struct "artista" in memoria
			i = 0;
			rewind(ptr);
			while (!feof(ptr)) {
				fseek(ptr, i * sizeof(artista), SEEK_SET);
				fread(&artista, sizeof(artista), 1, ptr);

				// Se l'id inserito in precedenza corrisponde ad un id presente nel file degli artisti,
				// viene ritornato un messaggio di conferma e inizia la modifica dell'artista trovato
				if (scelta_id == artista.id) {
					printf("Artista trovato!\n");
					system("pause");
					system("cls");

					printf("Inserisci nuovo nome\n");

					// Cicla fino a quando la variabile "n" non è uguale ad 1 (acquisizione nuovi dati dell'artista)
					n = 0;
					while (n != 1) {

						// Azzeramento campo "artista.nome"
						memset(&artista.nome, 0, sizeof(artista.nome));

						// Acquisizione in input del nome dell'artista
						fflush(stdin);
						gets(artista.nome);

						// Controllo sulla posizione 20 dell'array "artista.nome", se non è vuota stampa un errore
						if (artista.nome[20] != 0)
							printf("ATTENZIONE: Il nome dell'artista non puo' superare i 20 caratteri.\n");

						// Conversione array per scrittura in file, converte ogni posizione
						k = 0;
						while (artista.nome[k]) {
							artista.nome[k] = conversione(artista.nome[k]);
							k++;
						}

						if (artista.nome[20] == 0) // Se la posizione 20 dell'array "artista.nome" è vuota,
							n++;                   // esci dal ciclo

					}


					printf("Inserisci genere\n");

					n = 0;
					while (n != 1) {

						memset(&artista.genere, 0, sizeof(artista.genere));

						fflush(stdin);
						gets(artista.genere);

						if (artista.genere[15] != 0)
							printf("ATTENZIONE: Il genere dell'artista non puo' superare i 15 caratteri.\n");

						k = 0;
						while (artista.genere[k]) {
							artista.genere[k] = conversione(artista.genere[k]);
							k++;
						}

						if (artista.genere[15] == 0) {
							n++;
						}

					}


					printf("Inserisci produttore\n");

					n = 0;
					while (n != 1) {

						memset(&artista.prod, 0, sizeof(artista.prod));

						fflush(stdin);
						gets(artista.prod);

						if (artista.prod[25] != 0)
							printf("ATTENZIONE: Il produttore dell'artista non puo' superare i 25 caratteri.\n");

						k = 0;
						while (artista.prod[k]) {
							artista.prod[k] = conversione(artista.prod[k]);
							k++;
						}

						if (artista.prod[15] == 0) {
							n++;
						}
					}


					printf("Inserisci anno di produzione\n");

					n = 0;
					while (n != 1) {

						artista.anno = 0;

						fflush(stdin);
						scanf("%d", &artista.anno);

						// Controllo sull'anno inserito: se è maggiore o uguale a 2019 o minore di 1900, stampa un errore
						// altrimenti, esci dal ciclo
						if (artista.anno < 1900 || artista.anno >= 2019)
							printf("ATTENZIONE: L'anno di produzione deve essere compreso fra 1900 e 2018."
									"Non si accettano mummie ne' cantanti dal futuro.\n");
						else n++;

					}


					printf("Inserisci nazionalita'\n");

					n = 0;
					while (n != 1) {

						memset(&artista.nazione, 0, sizeof(artista.nazione));

						fflush(stdin);
						gets(artista.nazione);

						if (artista.nazione[15] != 0)
							printf("ATTENZIONE: La nazionalita' dell'artista non puo' superare i 15 caratteri.\n");

						k = 0;
						while (artista.nazione[k]) {
							artista.nazione[k] = conversione(artista.nazione[k]);
							k++;
						}

						if (artista.nazione[15] == 0) {
							n++;
						}
					}

					// Posizionamento del puntatore alla posizione i dell'offset
					// e scrittura della struct artista appena acquisita in tale posizione
					fseek(ptr, i * sizeof(artista), SEEK_SET);
					fwrite(&artista, sizeof(artista), 1, ptr);

					printf("\nModifica effettuata con successo! Digita 1 per proseguire\n");

					while (a != 1) {
						scanf("%s", scelta);

						if (isalpha(scelta[0]))
							printf("Errore\n");

						scelta_num = atoi(scelta);

						switch (scelta_num) {

						// Artista modificato, ritorno al menù degli artisti
						case 1:
							a = 1;
							printf("Ritorno al menu' degli artisti...\n");
							sleep(1);
							system("cls");
							break;

						default:
							printf("Errore, reinserire numero.");
							break;

						}

					}

				}

				i++;

			}

		}

		// Chiusura file "artisti.dat"
		fclose(ptr);

	}

}


void ricerca_artisti (FILE *ptr) {

	// Variabili locali alla funzione
	int a = 0;
	int b = 0;
	int k = 0;
	int i = 0;
	int trovato = 0;
	char scelta[1];
	char genere_temp[16];
	int scelta_num = 0;
	int anno_temp = 0;

	// Cicla fino a quando la variabile "a" non è uguale ad 1 (controllo sull'id artista da ricercare nel file)
	a = 0;
	while (a != 1) {

		// Apertura del file in lettura binaria
		if ((ptr = fopen("artisti.dat", "rb")) == NULL) {
			printf("ERRORE FILE.\n"); }
		else {

			// Inizio della funzione di ricerca: il programma chiede all'utente di scegliere
			// se utilizzare la ricerca per genere o per anno di attività, prendendo in input il numero relativo alla scelta.
			// E' anche possibile tornare al menù principale direttamente da questo punto, digitando 3
			printf("Benvenuto! Come desideri effettuare la ricerca? (usare il minuscolo e '_' dove necessario)\n");
			printf("1) Per genere  2) Per anno di attivita' 3) Esci dalla funzione di ricerca\n");
			scanf("%s", scelta);

			if (isalpha(scelta[0]))
				printf("Errore, inserire numero\n\n");

			else {
				scelta_num = atoi(scelta);

				switch (scelta_num) {

				case 1:

					// Ciclo fino alla fine del file per leggere l'intero file degli artisti
					k = 0;
					rewind(ptr);
					while (!feof(ptr)) {
						fseek(ptr, k * sizeof(artista), SEEK_SET);
						fread(&artista, sizeof(artista), 1, ptr);
						k++;
					}

					k--; // Ultimo indirizzo relativo all'ultima struct "artista" scritta del file

					// Acquisizione termine di ricerca (genere)
					printf("Inserisci genere\n");
					fflush(stdin);
					gets(genere_temp);

					// Inizializzazione di un ciclo for che va da "b" (utilizzata per muoversi all'interno del file degli artisti e leggerlo)
					// fino a b (utilizzata per salvare l'ultimo indirizzo relativo all'ultima struct "artista" scritta nel file)
					system("cls");
					printf("Risultati della ricerca per genere:\n\n");
					for (b = 0; b < k; b++) {

						fseek(ptr, b * sizeof(artista), SEEK_SET);
						fread(&artista, sizeof(artista), 1, ptr);

						// Se il genere inserito è uguale ad un genere presente nel file degli artisti,
						// stampa tutti gli artisti con il genere ricercato
						if (!strcmp(artista.genere, genere_temp)) {

							// Conversione delle iniziali di nome, genere, nome produttore e nazionalità artista in maiuscole
							artista.nome[0] = toupper(artista.nome[0]);
							artista.genere[0] = toupper(artista.genere[0]);
							artista.prod[0] = toupper(artista.prod[0]);
							artista.nazione[0] = toupper(artista.nazione[0]);

							// Scorre il nome del'artista: se contiene un underscore, lo trasforma in spazio
							// e converte la lettera successiva ad esso in maiuscola
							i = 0;
							while (artista.nome[i]) {
								if (artista.nome[i] == '_') {
									artista.nome[i] = ' ';
									artista.nome[i+1] = toupper(artista.nome[i+1]);
								}
								i++;
							}

							// Scorre il nome del produttore dell'artista: se contiene un underscore, lo trasforma in spazio
							// e converte la lettera successiva ad esso in maiuscola
							i = 0;
							while (artista.prod[i]) {
								if (artista.prod[i] == '_') {
									artista.prod[i] = ' ';
									artista.prod[i+1] = toupper(artista.prod[i+1]);
								}
								i++;
							}

							// Scorre il nome della nazionalità dell'artista: se contiene un underscore, lo trasforma in spazio
							// e converte la lettera successiva ad esso in maiuscola
							i = 0;
							while (artista.nazione[i]) {
								if (artista.nazione[i] == '_') {
									artista.nazione[i] = ' ';
									artista.nazione[i+1] = toupper(artista.nazione[i+1]);
								}
								i++;
							}

							// Scorre il genere dell'artista: se contiene un underscore, lo trasforma in spazio
							// e converte la lettera successiva ad esso in maiuscola
							i = 0;
							while (artista.genere[i]) {
								if (artista.genere[i] == '_') {
									artista.genere[i] = ' ';
									artista.genere[i+1] = toupper(artista.genere[i+1]);
								}
								i++;
							}

							// Stampa di tutti gli artisti ricercati per genere
							// e setta la variabile di controllo "trovato" ad 1
							printf("ID: %d\n", artista.id);
							printf("Nome: %s\n", artista.nome);
							printf("Genere: %s\n", artista.genere);
							printf("Produttore: %s\n", artista.prod);
							printf("Nazionalita': %s\n", artista.nazione);
							printf("Anno: %d\n\n", artista.anno);
							trovato = 1;


						}

					}

					// Se la variabile di controllo "trovato" è diversa da 1, ritorna errore
					if (trovato != 1)
						printf("Nessun artista trovato\n");


					system("pause");
					system("cls");
					fclose(ptr);  // Chiusura del file "artisti.dat"

					break;


				case 2:

					// Ciclo fino alla fine del file per leggere l'intero file degli artisti
					k = 0;
					rewind(ptr);
					while (!feof(ptr)) {
						fseek(ptr, k * sizeof(artista), SEEK_SET);
						fread(&artista, sizeof(artista), 1, ptr);
						k++;
					}

					k--; // Ultimo indirizzo relativo all'ultima struct "artista" scritta del file

					// Acquisizione termine di ricerca (anno di attività dell'artista)
					printf("Inserisci anno di attivita'\n");
					fflush(stdin);
					scanf("%d", &anno_temp);

					// Inizializzazione di un ciclo for che va da "b" (utilizzata per muoversi all'interno del file degli artisti e leggerlo)
					// fino a b (utilizzata per salvare l'ultimo indirizzo relativo all'ultima struct "artista" scritta nel file)
					system("cls");
					printf("Risultati della ricerca per anno di attivita':\n\n");
					for (b = 0; b < k; b++) {

						fseek(ptr, b * sizeof(artista), SEEK_SET);
						fread(&artista, sizeof(artista), 1, ptr);

						// Se l'anno inserito è uguale ad un anno di attività presente nel file degli artisti,
						// stampa tutti gli artisti con l'anno di attività ricercato
						if (artista.anno == anno_temp) {

							// Conversione delle iniziali di nome, genere, nome produttore e nazionalità artista in maiuscole
							artista.nome[0] = toupper(artista.nome[0]);
							artista.genere[0] = toupper(artista.genere[0]);
							artista.prod[0] = toupper(artista.prod[0]);
							artista.nazione[0] = toupper(artista.nazione[0]);

							// Scorre il nome del'artista: se contiene un underscore, lo trasforma in spazio
							// e converte la lettera successiva ad esso in maiuscola
							i = 0;
							while (artista.nome[i]) {
								if (artista.nome[i] == '_') {
									artista.nome[i] = ' ';
									artista.nome[i+1] = toupper(artista.nome[i+1]);
								}
								i++;
							}

							// Scorre il nome del produttore dell'artista: se contiene un underscore, lo trasforma in spazio
							// e converte la lettera successiva ad esso in maiuscola
							i = 0;
							while (artista.prod[i]) {
								if (artista.prod[i] == '_') {
									artista.prod[i] = ' ';
									artista.prod[i+1] = toupper(artista.prod[i+1]);
								}
								i++;
							}

							// Scorre il nome della nazionalità dell'artista: se contiene un underscore, lo trasforma in spazio
							// e converte la lettera successiva ad esso in maiuscola
							i = 0;
							while (artista.nazione[i]) {
								if (artista.nazione[i] == '_') {
									artista.nazione[i] = ' ';
									artista.nazione[i+1] = toupper(artista.nazione[i+1]);
								}
								i++;
							}

							// Scorre il genere dell'artista: se contiene un underscore, lo trasforma in spazio
							// e converte la lettera successiva ad esso in maiuscola
							i = 0;
							while (artista.genere[i]) {
								if (artista.genere[i] == '_') {
									artista.genere[i] = ' ';
									artista.genere[i+1] = toupper(artista.genere[i+1]);
								}
								i++;
							}

							// Stampa di tutti gli artisti ricercati per anno di attività
							// e setta la variabile di controllo "trovato" ad 1
							printf("ID: %d\n", artista.id);
							printf("Nome: %s\n", artista.nome);
							printf("Genere: %s\n", artista.genere);
							printf("Produttore: %s\n", artista.prod);
							printf("Nazionalita': %s\n", artista.nazione);
							printf("Anno: %d\n\n", artista.anno);
							trovato = 1;


						}

					}

					// Se la variabile di controllo "trovato" è diversa da 1, ritorna errore
					if (trovato != 1)
						printf("Nessun artista trovato\n");

					system("pause");
					system("cls");
					fclose(ptr);  // Chiusura del file "artisti.dat"

					break;

				case 3:
					a = 1;
					system("cls");
					fclose(ptr);
					break;

				}

			}
		}
	}
}


void visual_artisti (FILE *ptr) {

	// Variabili locali alla funzione
	int a, b = 0;
	int k = 0;

	// Apertura file in lettura binaria
	if ((ptr = fopen("artisti.dat", "rb")) == NULL) {
		printf("ERRORE FILE.\n");

	} else {

		// Ciclo fino alla fine del file per leggere l'intero file degli artisti
		rewind(ptr);
		while (!feof(ptr)) {
			fread(&artista, sizeof(artista), 1, ptr);
			b++;
		}

		b--; // Ultimo indirizzo relativo all'ultima struct "artista" scritta del file

		printf("ARTISTI IN ELENCO:\n\n");

		// Inizializzazione di un ciclo for che va da "a" (utilizzata per posizionarsi all'interno del file degli artisti e leggerlo),
		// fino a "b" (utilizzata per salvare l'ultimo indirizzo relativo all'ultima struct "artista" scritta nel file).
		for (a = 0; a < b; a++) {
			fseek(ptr, a * sizeof(artista), SEEK_SET);
			fread(&artista, sizeof(artista), 1, ptr);

			// Conversione delle iniziali di nome, genere, nome produttore e nazionalità artista in maiuscole
			artista.nome[0] = toupper(artista.nome[0]);
			artista.genere[0] = toupper(artista.genere[0]);
			artista.prod[0] = toupper(artista.prod[0]);
			artista.nazione[0] = toupper(artista.nazione[0]);

			// Scorre il nome dell'artista: se contiene un underscore, lo trasforma in spazio
			// e converte la lettera successiva ad esso in maiuscola
			k = 0;
			while (artista.nome[k]) {
				if (artista.nome[k] == '_') {
					artista.nome[k] = ' ';
					artista.nome[k+1] = toupper(artista.nome[k+1]);
				}

				k++;
			}

			// Scorre il nome del produttore dell'artista: se contiene un underscore, lo trasforma in spazio
			// e converte la lettera successiva ad esso in maiuscola
			k = 0;
			while (artista.prod[k]) {
				if (artista.prod[k] == '_') {
					artista.prod[k] = ' ';
					artista.prod[k+1] = toupper(artista.prod[k+1]);
				}
				k++;
			}

			// Scorre la nazionalita' dell'artista: se contiene un underscore, lo trasforma in spazio
			// e converte la lettera successiva ad esso in maiuscola
			k = 0;
			while (artista.nazione[k]) {
				if (artista.nazione[k] == '_') {
					artista.nazione[k] = ' ';
					artista.nazione[k+1] = toupper(artista.nazione[k+1]);
				}

				k++;
			}

			// Scorre il genere dell'artista: se contiene un underscore, lo trasforma in spazio
			// e converte la lettera successiva ad esso in maiuscola
			k = 0;
			while (artista.genere[k]) {
				if (artista.genere[k] == '_') {
					artista.genere[k] = ' ';
					artista.genere[k+1] = toupper(artista.genere[k+1]);
				}

				k++;
			}

			// Stampa di tutti i dati dell'artista contenuti nel file
			printf("ID: %d\n", artista.id);
			printf("Nome: %s\n", artista.nome);
			printf("Genere: %s\n", artista.genere);
			printf("Produttore: %s\n", artista.prod);
			printf("Anno attivita': %d\n", artista.anno);
			printf("Nazionalita': %s\n\n", artista.nazione);

		}

		// Chiusura del file "artisti.dat"
		system("pause");
		system("cls");
		fclose(ptr);

	}

}


void elimina_artista(FILE *ptr) {

	int id_temp;  // Variabile id artista temporanea
	FILE *file2;  // Puntatore utilizzato per l'apertura del file artisti temporaneo

	printf("Eliminazione artista dal database\n\n");
	printf("Inserisci l'id dell'artista da eliminare: \n");

	// Acquisizione in input dell'id artista temporaneo
	scanf("%d", &id_temp);

	// Apertura simultanea del file "artisti.dat" in lettura binaria
	// e del file "temp_artisti.dat" in scrittura binaria
	ptr = fopen("artisti.dat", "rb");
	file2 = fopen("temp_artisti.dat", "wb");

	// Riavvolgimento dello stream del file "artisti.dat"
	rewind(ptr);

	// Lettura del file "artisti.dat" fino alla fine,
	// se l'id dell'artista inserito è diverso da quello caricato in memoria,
	// scrivo l'intera struct "artista" nel nuovo file eccetto quella contenente l'id inserito
	while ((fread(&artista, sizeof(artista), 1, ptr)) > 0) {
		if (artista.id != id_temp) {
			fwrite(&artista, sizeof(artista), 1, file2);
		}

	}

	// Chiusura dei file
	fclose(file2);
	fclose(ptr);

	// Eliminazione del file "artisti.dat" dal disco
	remove("artisti.dat");

	// Ridenominazione del file "temp_artisti.dat" in "artisti.dat"
	rename("temp_artisti.dat", "artisti.dat");

	// Artista cancellato. Ritorno al menù degli artisti
	printf("Artista cancellato\n");
	system("pause");
	system("cls");

}



void artisti_piu_ascoltati (FILE *ptr) {

	// Variabili locali alla funzione
	int i = 0;
	int k, n, b, z = 0;
	int temp = 0;
	char *listen = "Ascolta";

	// Apertura file in lettura binaria
	if ((ptr = fopen("preferenze.dat", "rb")) == NULL) {
		printf("ERRORE FILE.\n");

	} else {

		// Ciclo fino alla fine del file per leggere l'intero file delle preferenze
		n = 0;
		rewind(ptr);
		while (!feof(ptr)) {
			fread(&preftemp, sizeof(pref), 1, ptr);
			n++;
		}

		n--; // Indirizzo ultima struct presente nel file "preferenze.dat"

	}

	// Chiusura file "preferenze.dat"
	fclose(ptr);

	// Apertura file in lettura binaria
	if ((ptr = fopen("artisti.dat", "rb")) == NULL) {
		printf("ERRORE FILE.\n");
	} else {

		// Ciclo fino alla fine del file per leggere l'intero file degli artisti
		b = 0;
		rewind(ptr);
		while (!feof(ptr)) {
			fread(&artista, sizeof(artista), 1, ptr);
			b++;
		}

		b--; // Indirizzo ultima struct presente nel file "artisti.dat"

	}

	// Chiusura del file "artisti.dat"
	fclose(ptr);

	// Dichiarazione vettore "num_artisti" contenente tutti gli artisti presenti nel file
	int num_artisti[b];

	// Azzeramento del vettore "num_artisti"
	for (i = 0; i < b; i++) {
		num_artisti[i] = 0;
	}

	// Dichiarazione vettore "num_artisti_copy" contenente tutti gli artisti presenti nel file
	int num_artisti_copy[b];

	// Azzeramento del vettore "num_artisti_copy"
	for (i = 0; i < b; i++) {
		num_artisti_copy[i] = 0;
	}

	// Inizializzazione ciclo for che va da "i" fino a "b" (numero totale di artisti) con posizionamento dell'offset "i"
	// alla struct "artista" e lettura della struct
	for (i = 0; i < b; i++) {

		if ((ptr = fopen("artisti.dat", "rb")) == NULL) {
			printf("ERRORE FILE.\n");

		} else {

			fseek(ptr, i * sizeof(artista), SEEK_SET);
			fread(&artista, sizeof(artista), 1, ptr);
		}

		// Chiusura del file "artisti.dat"
		fclose(ptr);

		// Apertura del file in lettura binaria
		if ((ptr = fopen("preferenze.dat", "rb")) == NULL) {
			printf("ERRORE FILE.\n");

		} else {

			// Inizializzazione ciclo for che va da "k" a "n" (numero totale di preferenze) con posizionamento dell'offset "k"
			// alla struct "pref" e lettura della struct.
			// Se le stringhe "artista.nome" e "pref.artista" (il nome dell'artista è uguale) e se il campo "pref.preferenza"
			// riferito all'artista contiene la preferenza "listen", incrementa il numero totale degli artisti
			rewind(ptr);
			for (k = 0; k < n; k++) {
				fseek(ptr, k * sizeof(pref), SEEK_SET);
				fread(&pref, sizeof(pref), 1, ptr);
				if (!strcmp(pref.artista, artista.nome)
						&& !strcmp(pref.preferenza, listen)) {
					num_artisti[i]++;
				}
			}
		}

		fclose(ptr); // Chiusura del file "preferenze.dat"
	}

	// Duplicazione del vettore per ordinamento bubble sort
	for (i = 0; i < b; i++) {
		num_artisti_copy[i] = num_artisti[i];
	}

	// Bubble sort usato per l'ordinamento di ascolti e posizione degli artisti
	for(i = 0; i < b-1; i++) {
		for(k = 0; k < b-i-1; k++) {
			if(num_artisti[k] < num_artisti[k+1]) {
				temp = num_artisti[k];
				num_artisti[k] = num_artisti[k+1];
				num_artisti[k+1] = temp;
			}
		}
	}

	printf("Classifica degli artisti piu' ascoltati dagli utenti\n\n");
	printf("%-15s %s\n\n", "Posizione", "Artista");

	// Apertura file in lettura binaria
	if ((ptr = fopen("artisti.dat", "rb")) == NULL) {
		printf("ERRORE FILE.\n");

	} else {

		// Inizializzazione posizione artista
		n = 1;

		// Inizializzazione ciclo for che va da "i" a "b" (numero totale artisti),
		// usato per riportare tutte le posizioni degli artisti, con incremento di "n"
		for (i = 0; i < b; i++) {

			printf("%-16d", n);

			// Inizializzazione ciclo for che va da "k" a "b" (numero totale artisti)
			for(k = 0; k < b; k++) {

				// Se il valore contenuto nel primo vettore con indice "i"
				// è uguale al valore contenuto nel secondo vettore con indice "k",
				// posiziona il puntatore alla posizione "k*sizeof" e leggi la struct artista
				if(num_artisti[i] == num_artisti_copy[k]) {
					fseek(ptr, k * sizeof(artista), SEEK_SET);
					fread(&artista, sizeof(artista), 1, ptr);

					// Conversione di caratteri per la visualizzazione di "artista.nome"
					z = 0;
					if (isalpha(artista.nome[z])) {
						artista.nome[z] = toupper(artista.nome[z]);
					}

					while (artista.nome[z]) {
						if (artista.nome[z] == '_')	{
							artista.nome[z] = ' ';
							z++;

							if (isalpha(artista.nome[z]))
								artista.nome[z] = toupper(artista.nome[z]);

							z--;
						}

						z++;
					}

					// Stampa il valore dell'artista, con valore di flag
					// utilizzato per evitare che un artista con lo stesso numero di ascolti di un altro artista
					// possa apparire due volte nella classifica
					printf("%s\n", artista.nome);
					num_artisti_copy[k] = -1;
					break;
				}
			}

			n++;	// Incremento contatore delle posizioni degli artisti

		}

		// Chiusura del file "artisti.dat"
		fclose(ptr);
		printf("\n");
		system("pause");
		system("cls");

	}

}
