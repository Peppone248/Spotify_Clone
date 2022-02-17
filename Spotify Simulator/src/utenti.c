/*
 * utenti.c
 *
 *  Created on: 28 gen 2018
 *      Author: Antonio Pansini
 */

#include "utenti.h"
#include "varlib.h"

void aggiunta_utenti (FILE *ptr) {

	// Variabili locali alla funzione
	int a = 0;
	int i = 0;
	int k = 0;
	int n = 0;
	int uguale = 0;

	int fine = 0;
	char scelta[1];
	int scelta_num;

	// Apertura file in scrittura binaria
	if ((ptr = fopen("utenti.dat", "rb+")) == NULL) {
		printf("ERRORE: File degli utenti non trovato.\n");

		printf("Creare il file degli utenti? 1) Si  2) No\n");

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
					ptr = fopen("utenti.dat", "wb");
					fclose(ptr);
					printf("Creazione file in corso...\n");
					sleep(1);
					printf("Il file degli utenti e' stato creato.\n");
					system("pause");
					system("cls");
					a = 1;
					break;

					//
				case 2:
					a = 1;
					break;

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
				fseek(ptr,i * sizeof(utente), SEEK_SET);
				fread(&utente, sizeof(utente), 1, ptr);
				i++;
			}

			i--;

			printf("Inserisci username\n");

			// Cicla fino a quando la variabile "n" non è uguale ad 1 (controlli sul nome artista)
			n = 0;
			while (n != 1) {

				uguale = 0;

				// Azzeramento campo "utente.username"
				memset(&utente.username, 0, sizeof(utente.username));

				// Acquisizione nome utente
				fflush(stdin);
				gets(utente.username);

				// Controllo sulla posizione 20 dell'array "utente.username", se non è vuota stampa un errore
				if (utente.username[20] != 0)
					printf("ATTENZIONE: L'username non puo' superare i 20 caratteri\n");

				// Conversione array per scrittura in file, converte ogni posizione
				k = 0;
				while (utente.username[k]) {
					utente.username[k] = conversione(utente.username[k]);
					k++;
				}


				k = 0;
				rewind(ptr);		                                           // Riavvolgimento dello stream, posizione del puntatore a inizio file
				while (!feof(ptr)) {								           // Ciclo che termina alla fine del file
					fseek(ptr, k * sizeof(utente), SEEK_SET);		           // Posiziona il puntatore alla posizione determinata dall'offset "k"
					fread(&utentetemp, sizeof(utente), 1, ptr);	               // Caricamento in memoria della struct "utentetemp"
					if (!strcmp(utentetemp.username, utente.username)) {	       // Confronto fra le due stringhe "utentetemp.nome" e "utente.nome"
						printf("\nATTENZIONE: L'utente inserito e' gia' presente nel file!\n");	// Se le due stringhe sono uguali, stampa un messaggio di errore e
						uguale = 1;                                            // setta la variabile di controllo "uguale" ad 1
						break;
					}

					k++;
				}

				if (uguale == 0 && utente.username[20] == 0) // Se la variabile di controllo "uguale" è 0 e la posizione 20 dell'array "artista.nome" è vuota,
					n++;                                     // esci dal ciclo
			}


			printf("Inserisci nome dell'utente\n");

			n = 0;

			while (n != 1) {

				memset(&utente.nome, 0, sizeof(utente.nome));

				fflush(stdin);
				gets(utente.nome);

				if (utente.nome[20] != 0)
					printf("ATTENZIONE: Il nome dell'utente non puo' superare i 20 caratteri\n");

				k = 0;
				while (utente.nome[k]) {
					utente.nome[k] = conversione(utente.nome[k]);
					k++;
				}

				if (utente.nome[20] == 0) {
					n++;
				}

			}


			printf("Inserisci cognome dell'utente\n");

			n = 0;

			while (n != 1) {

				memset(&utente.cognome, 0, sizeof(utente.cognome));

				fflush(stdin);
				gets(utente.cognome);

				if (utente.cognome[20] != 0)
					printf("ATTENZIONE: Il cognome non puo' superare i 20 caratteri\n");

				k = 0;
				while (utente.cognome[k]) {
					utente.cognome[k] = conversione(utente.cognome[k]);
					k++;
				}

				if (utente.cognome[20] == 0) {
					n++;
				}
			}

			// Assegna automaticamente l'id all'inserimento di ogni utente nel file
			utente.id++;

			// Posizionamento del puntatore alla posizione i dell'offset
			// e scrittura della struct utente appena acquisita in tale posizione
			fseek(ptr, i * sizeof(utente), SEEK_SET);
			fwrite(&utente, sizeof(utente), 1, ptr);

			printf("Vuoi continuare ad aggiungere utenti? 1) Si  2) No\n");

			a = 0;
			while (a != 1) {
				scanf("%s", scelta);

				if (isalpha(scelta[0]))
					printf("Errore\n");

				scelta_num = atoi(scelta);

				switch (scelta_num) {

				// Il ciclo di aggiunta utenti ricomincia dall'inizio
				case 1:
					printf("Utente aggiunto\n");
					fine = 0;
					a = 1;
					system("pause");
					system("cls");
					break;

					// Interruzione aggiunta utenti. Ritorno al menù principale
				case 2:
					printf("Aggiunta utenti interrotta\n");
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

		// Ciclo che determina l'aggiunta dei dati di un utente
		while (fine != 1);
	}

	// Chiusura del file "utenti.dat"
	fclose(ptr);

}


void modifica_utente (FILE *ptr) {

	// Variabili locali alla funzione
	int n = 0;
	int a = 0;
	char username_temp[20];
	char scelta[1] = {0};
	int scelta_num = 0;
	int i = 0;
	int k = 0;

	// Apertura file in scrittura binaria in aggiornamento
	if ((ptr = fopen("utenti.dat", "rb+")) == NULL) {
		printf("ERRORE FILE.\n"); }
	else {

		// Cicla fino a quando la variabile "a" non è uguale ad 1 (controllo sull'username dell'utente da ricercare nel file)
		a = 0;
		while (a != 1) {

			// Acquisizione dell'username dell'utente da modificare
			printf("Inserisci username da modificare (in minuscolo)\n");
			fflush(stdin);
			gets(username_temp);

			// Ciclo che scorre il file degli artisti fino alla fine,
			// con caricamento della struct "utente" in memoria
			i = 0;
			rewind(ptr);
			while (!feof(ptr)) {
				fseek(ptr, i * sizeof(utente), SEEK_SET);
				fread(&utente, sizeof(utente), 1, ptr);

				// Se l'username inserito in precedenza corrisponde ad un username presente nel file degli utenti,
				// viene ritornato un messaggio di conferma e inizia la modifica dell'utente trovato
				if (!strcmp(username_temp, utente.username)) {
					printf("Utente trovato!\n");
					system("pause");
					system("cls");

					printf("Inserisci nuovo username\n");

					// Cicla fino a quando la variabile "n" non è uguale ad 1 (acquisizione nuovi dati dell'utente)
					n = 0;
					while (n != 1) {

						// Azzeramento campo "utente.usernamew"
						memset(&utente.username, 0, sizeof(utente.username));

						// Acquisizione in input del nome dell'utente
						fflush(stdin);
						gets(utente.username);

						// Controllo sulla posizione 20 dell'array "artista.nome", se non è vuota stampa un errore
						if (utente.username[20] != 0)
							printf("ATTENZIONE: L'username non puo' superare i 20 caratteri.\n");

						// Conversione array per scrittura in file, converte ogni posizione
						k = 0;
						while (utente.username[k]) {
							utente.username[k] = conversione(utente.username[k]);
							k++;
						}

						if (utente.username[20] == 0) // Se la posizione 20 dell'array "artista.nome" è vuota,
							n++;                      // esci dal ciclo

					}


					printf("Inserisci nome\n");

					n = 0;
					while (n != 1) {

						memset(&utente.nome, 0, sizeof(utente.nome));

						fflush(stdin);
						gets(utente.nome);

						if (utente.nome[20] != 0)
							printf("ATTENZIONE: Il nome dell'utente non puo' superare i 15 caratteri.\n");

						k = 0;
						while (utente.nome[k]) {
							utente.nome[k] = conversione(utente.nome[k]);
							k++;
						}

						if (utente.nome[20] == 0) {
							n++;
						}

					}


					printf("Inserisci cognome\n");

					n = 0;
					while (n != 1) {

						memset(&utente.cognome, 0, sizeof(utente.cognome));

						fflush(stdin);
						gets(utente.cognome);

						if (utente.cognome[20] != 0)
							printf("ATTENZIONE: Il cognome dell'utente non puo' superare i 20 caratteri.\n");

						k = 0;
						while (utente.cognome[k]) {
							utente.cognome[k] = conversione(utente.cognome[k]);
							k++;
						}

						if (utente.cognome[15] == 0) {
							n++;
						}
					}


					// Posizionamento del puntatore alla posizione i dell'offset
					// e scrittura della struct artista appena acquisita in tale posizione
					fseek(ptr, i * sizeof(utente), SEEK_SET);
					fwrite(&utente, sizeof(utente), 1, ptr);

					printf("\nModifica effettuata con successo! Digita 1 per proseguire\n");

					a = 0;
					while (a != 1) {
						scanf("%s", scelta);

						if (isalpha(scelta[0]))
							printf("Errore\n");

						scelta_num = atoi(scelta);

						switch (scelta_num) {

						// Utente modificato, ritorno al menù degli utenti
						case 1:
							a = 1;
							printf("Ritorno al menu' degli utenti...\n");
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

		// Chiusura file "utenti.dat"
		fclose(ptr);

	}


}


void visual_utenti (FILE *ptr) {

	// Variabili locali alla funzione
	int a, b = 0;
	int k = 0;

	// Apertura file in lettura binaria
	if ((ptr = fopen("utenti.dat", "rb")) == NULL) {
		printf("ERRORE FILE.\n"); }
	else {

		// Ciclo fino alla fine del file per leggere l'intero file degli utenti
		rewind(ptr);
		while (!feof(ptr)) {
			fread(&utente, sizeof(utente), 1, ptr);
			b++;
		}

		b--; // Ultimo indirizzo relativo all'ultima struct "utente" scritta del file

		printf("UTENTI IN ELENCO:\n\n");

		// Inizializzazione di un ciclo for che va da "a" (utilizzata per posizionarsi all'interno del file degli utenti e leggerlo),
		// fino a "b" (utilizzata per salvare l'ultimo indirizzo relativo all'ultima struct "utente" scritta nel file).
		for (a = 0; a < b; a++) {
			fseek(ptr, a * sizeof(utente), SEEK_SET);
			fread(&utente, sizeof(utente), 1, ptr);

			// Conversione delle iniziali di username, nome e cognome dell'utente in maiuscole
			utente.username[0] = toupper(utente.username[0]);
			utente.nome[0] = toupper(utente.nome[0]);
			utente.cognome[0] = toupper(utente.cognome[0]);

			// Scorre l'username dell'utente: se contiene un underscore, lo trasforma in spazio
			// e converte la lettera successiva ad esso in maiuscola
			k = 0;
			while (utente.username[k]) {
				if (utente.username[k] == '_') {
					utente.username[k] = ' ';
					utente.username[k+1] = toupper(utente.username[k+1]);
				}

				k++;
			}

			// Scorre il cognome dell'utente: se contiene un underscore, lo trasforma in spazio
			// e converte la lettera successiva ad esso in maiuscola
			k = 0;
			while (utente.cognome[k]) {
				if (utente.cognome[k] == '_') {
					utente.cognome[k] = ' ';
					utente.cognome[k+1] = toupper(utente.cognome[k+1]);
				}

				k++;
			}

			// Stampa di tutti i dati dell'utente contenuti nel file
			printf("ID utente: %d\n", utente.id);
			printf("Username: %s\n", utente.username);
			printf("Nome utente: %s\n", utente.nome);
			printf("Cognome utente: %s\n\n", utente.cognome);

		}

		// Chiusura del file "utenti.dat"
		system("pause");
		system("cls");
		fclose(ptr);

	}
}


void elimina_utente(FILE *ptr) {

	int id_temp; // Variabile id utente  temporanea
	FILE *file2; // Puntatore utilizzato per l'apertura del file utenti temporaneo

	printf("Eliminazione utente dal database\n\n");
	printf("Inserisci l'id dell'utente da eliminare: \n");

	// Acquisizione in input dell'id utente temporaneo
	scanf("%d", &id_temp);

	// Apertura simultanea del file "utenti.dat" in lettura binaria
	// e del file "temp_utenti.dat" in scrittura binaria
	ptr = fopen("utenti.dat", "rb");
	file2 = fopen("temp_utenti.dat", "wb");

	// Riavvolgimento dello stream del file "utenti.dat"
	rewind(ptr);

	// Lettura del file "utenti.dat" fino alla fine,
	// se l'id dell'utente inserito è diverso da quello caricato in memoria,
	// scrivo l'intera struct "utente" nel nuovo file eccetto quella contenente l'id inserito
	while ((fread(&utente, sizeof(utente), 1, ptr)) > 0)
	{
		if (utente.id != id_temp)
		{
			fwrite(&utente, sizeof(utente), 1, file2);
		}
	}

	// Chiusura dei file
	fclose(file2);
	fclose(ptr);

	// Eliminazione del file "artisti.dat" dal disco
	remove("utenti.dat");

	// Ridenominazione del file "temp_artisti.dat" in "artisti.dat"
	rename("temp_utenti.dat", "utenti.dat");

	// Utente cancellato. Ritorno al menù degli utenti
	printf("Utente cancellato\n");
	system("pause");
	system("cls");

}


void profilo_utenti (FILE *ptr) {

	// Contatori variabili ascolti, like, dislike
	int ascolti_count = 0;
	int like_count = 0;
	int dislike_count = 0;

	// Variabili locali alla funzione
	int n = 0;
	int k = 0;
	int i = 0;
	int j = 0;

	// Puntatori a char contenenti le preferenze
	char *listen = "Ascolta";
	char *like = "Like";
	char *dislike = "Dislike";

	// Apertura file in lettura binaria
	if ((ptr = fopen("preferenze.dat", "rb")) == NULL) {	//apertura file in modalità lettura binaria
		printf("ERRORE FILE.\n");

	} else {

		// Ciclo fino alla fine del file per leggere l'intero file delle preferenze
		n = 0;
		rewind(ptr);
		while (!feof(ptr)) {
			fread(&preftemp, sizeof(pref), 1, ptr);
			n++;
		}

		n--; // Ultimo indirizzo relativo all'ultima struct "preftemp" scritta del file

	}

	// Chiusura del file "preferenze.dat"
	fclose(ptr);

	// Apertura file in lettura binaria
	if ((ptr = fopen("artisti.dat", "rb")) == NULL) {

		printf("ERRORE FILE.\n");

	} else {

		// Ciclo fino alla fine del file per leggere l'intero file degli artisti
		rewind(ptr);
		while (!feof(ptr)) {
			fread(&artista, sizeof(artista), 1, ptr);
		}

		// Assegnazione dell'id dell'ultimo artista presente nel file alla variabile "j"
		j = artista.id;

	}

	// Chiusura del file "artisti.dat"
	fclose(ptr);

	system("cls");
	printf("Elenco degli artisti ascoltati e votati dagli utenti di Spotify Simulator:\n"
			"ATTENZIONE: L'elenco puo' contenere anche artisti eliminati dal file\n\n\n");

	printf("%-22s %-2s %-2s %-2s\n\n", "       "
			"Artista", "NroAscolti", "Like", "Dislike\n");

	// Inizializzazione ciclo for che va dall'indirizzo 0 all'indirizzo j (id dell'ultimo artista nel file)
	for(i = 0; i < j; i++) {

		if ((ptr = fopen("artisti.dat", "rb")) == NULL) {
			printf("ERRORE FILE.\n");

		} else {

			// Posizionamento dell'offset "i" nel file "artisti.dat" e lettura delle struct presenti
			fseek(ptr, i * sizeof(artista), SEEK_SET);
			fread(&artista, sizeof(artista), 1, ptr);
		}

		// Chiusura del file "artisti.dat"
		fclose(ptr);

		// Apertura del file "preferenze.dat"
		if ((ptr = fopen("preferenze.dat", "rb")) == NULL) {
			printf("ERRORE FILE.\n");

		} else {

			// Azzeramento contatori dei voti
			ascolti_count = 0;
			like_count = 0;
			dislike_count = 0;

			k = 0;
			rewind(ptr);                                                // Riavvolgimento dello stream, posizione del puntatore a inizio file
			for (k = 0; k < n; k++) {                                   // Ciclo che va dall'indirizzo 0 all'indirizzo "n" (ultimo indirizzo file preferenze)
				fseek(ptr, k * sizeof(pref), SEEK_SET);                 // Posiziona il puntatore alla posizione determinata dall'offset "k"
				fread(&preftemp, sizeof(pref), 1, ptr);                 // Caricamento in memoria della struct "preftemp"
				if (!strcmp(preftemp.artista, artista.nome)             // Confronto fra le due stringhe "preftemp.artista" e "artista.nome" e
						&& !strcmp(preftemp.preferenza, listen)) {      // verifica la presenza della stringa "listen" nel campo "preftemp.preferenza".
					ascolti_count++;                                    // Se corretto, incrementa contatore degli ascolti di 1
				}

				if (!strcmp(preftemp.artista, artista.nome)             // Confronto fra le due stringhe "preftemp.artista" e "artista.nome" e
						&& !strcmp(preftemp.preferenza, like)) {        // verifica la presenza della stringa "like" nel campo "preftemp.preferenza".
					like_count++;                                       // Se corretto, incrementa contatore dei like di 1
				}

				if (!strcmp(preftemp.artista, artista.nome)             // Confronto fra le due stringhe "preftemp.artista" e "artista.nome" e
						&& !strcmp(preftemp.preferenza, dislike)) {     // verifica la presenza della stringa "dislike" nel campo "preftemp.preferenza".
					dislike_count++;                                    // Se corretto, incrementa contatore dei dislike di 1
				}

			}

		}

		// Chiusura del file "preferenze.dat"
		fclose(ptr);

		// Scorre il nome dell'artista: se contiene un underscore, lo trasforma in spazio
		// e converte la lettera successiva ad esso in maiuscola.
		// Comprende correzione della posizione "k" per la visualizzazione di tutti gli artisti
		k = 0;
		if (isalpha(artista.nome[k]))
		{
			artista.nome[k] = toupper(artista.nome[k]);
		}

		while (artista.nome[k]) {
			if (artista.nome[k] == '_') {
				artista.nome[k] = ' ';
				k++;

				if (isalpha(artista.nome[k]))
					artista.nome[k] = toupper(artista.nome[k]);

				k--;
			}

			k++;
		}


		// Stampa dei dati in output
		printf("%-27s %-6d %-6d %-3d\n", artista.nome, ascolti_count, like_count, dislike_count);

	}

	printf("\n");
	system("pause");
	system("cls");

}
