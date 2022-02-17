/*
 * preferenze.c
 *
 *  Created on: 28 gen 2018
 *      Author: Antonio
 */

#include "preferenze.h"

void aggiunta_pref (FILE *ptr) {

	// Variabili locali alla funzione
	int k, i, a, b = 0;

	int presente = 0; // Variabile di controllo

	// Puntatori a char contenenti le preferenze
	char *listen = "Ascolta";
	char *like = "Like";
	char *unlike = "Dislike";

	// Apertura file in lettura binaria
	if ((ptr = fopen("preferenze.dat", "rb")) == NULL) {
		printf("ERRORE FILE.\n");

	} else {

		// Ciclo fino alla fine del file per leggere l'intero file delle preferenze
		i = 0;
		rewind(ptr);
		while (!feof(ptr)) {
			fread(&pref, sizeof(pref), 1, ptr);
			i++;
		}

		i--; // Ultimo indirizzo relativo all'ultima struct "preftemp" scritta del file

	}

	// Chiusura del file "preferenze.dat"
	fclose(ptr);

	// Schermata di benvenuto all'utente
	system("cls");
	printf("Accesso al database degli artisti...");
	sleep(1);
	printf("elenco caricato!\n");
	printf("Salve utente, quale artista desideri ascoltare?\n");

	// Cicla fino a quando la variabile "a" non è uguale ad 1 (ricerca artista da votare nel database)
	a = 0;
	while (a != 1) {

		// Inizializza la variabile di controllo "presente"
		presente = 0;

		// Azzeramento campo "pref.artista"
		memset(&pref.artista, 0, sizeof(pref.artista));

		// Acquisizione in input del nome dell'artista votato
		fflush(stdin);
		gets(pref.artista);

		// Conversione array per scrittura in file, converte ogni posizione
		k = 0;
		while (pref.artista[k]) {
			pref.artista[k] = conversione(pref.artista[k]);
			k++;
		}

		// Apertura file in lettura binaria
		if ((ptr = fopen("artisti.dat", "rb")) == NULL) {
			printf("ERRORE FILE.\n");

		} else {

			k = 0;
			rewind(ptr);										// Riavvolgimento dello stream, posizione del puntatore a inizio file
			while (!feof(ptr)) {								// Ciclo che termina alla fine del file
				fseek(ptr, k * sizeof(artista), SEEK_SET);		// Posiziona il puntatore alla posizione determinata dall'offset "k"
				fread(&artistatemp, sizeof(artista), 1, ptr);	// Caricamento in memoria della struct "artistatemp"
				if (!strcmp(artistatemp.nome, pref.artista)) {	// Confronto fra le due stringhe "artistatemp.nome" e "pref.artista"
					printf("\nOK! Artista trovato!\n");			// Se le due stringhe sono uguali, stampa un messaggio di conferma e
					presente = 1;                               // setta la variabile di controllo "presente" a 1
					break;
				}

				k++; // Incremento dell'offset "k"
			}

			if (presente == 1) {	// Se la variabile di controllo "presente" è uguale ad 1, esci dal ciclo. Altrimenti...
				a++;
				system("pause");

			} else printf("Artista non trovato, reinserire il nome.\n"); // ...ritorna un messaggio di errore
		}

		fclose(ptr);	// Chiusura del file "artisti.dat"
	}

	system("cls");

	strcpy(pref.preferenza, listen);	// Copia la stringa "listen" nel campo "pref.preferenza"

	// Apertura file in scrittura binaria
	if ((ptr = fopen("preferenze.dat", "rb+")) == NULL) {
		printf("ERRORE FILE.\n");

	} else {

		// Posiziona puntatore alla posizione determinata dall'offset "j"
		// e scrive la struct "pref" nel file "preferenze.dat"
		fseek(ptr, i * sizeof(pref), SEEK_SET);
		fwrite(&pref, sizeof(pref), 1, ptr);

		k = 0;
		presente = 0;


		// Se la variabile di controllo "presente" è uguale ad 0 (artista trovato nel database)
		if (presente == 0) {

			printf("L'artista che hai appena ascoltato ti e' piaciuto? 1) Si 2) No\n");

			// Cicla fino a quando la variabile "a" non è uguale ad 1 (scelta dell'utente sì/no)
			a = 0;
			while (a != 1) {

				// Acquisizone della scelta dell'utente
				scanf("%d", &b);

				// Se la scelta corrisponde ad 1 oppure a 2, esci dal ciclo. Altrimenti...
				if (b == 1 || b == 2)
					a++;

				else
					printf("Scelta non disponibile, riprova.\n"); // ...ritorna un messaggio di errore
			}

			// Azzeramento campo "pref.preferenza"
			memset(&pref.preferenza, 0, sizeof(pref.preferenza));

			// Se la variabile b è uguale ad 1, copia la stringa like nel campo "pref.preferenza"
			// (Aggiunge "like" all'artista appena ascoltato
			if (b == 1)	{

				strcpy(pref.preferenza, like);
				printf("Hai messo 'Like' all'artista appena ascoltato.\n");
				system("pause");
				system("cls");
			}

			// Altrimenti se la variabile b è uguale a 2, copia la stringa dislike nel campo "pref.preferenza"
			// (Aggiunge "dislike" all'artista appena ascoltato
			else if (b == 2) {
				strcpy(pref.preferenza, unlike);
				printf("Hai messo 'Dislike' all'artista appena ascoltato.\n");
				system("pause");
				system("cls");
			}


			i++;	// Incremento dell'offset  "i"

			// Posiziona puntatore alla posizione determinata dall'offset "j"
			// e scrive la struct "pref" nel file "preferenze.dat"
			fseek(ptr, i * sizeof(pref), SEEK_SET);
			fwrite(&pref, sizeof(pref), 1, ptr);
		}
	}

	// Chiusura del file "preferenze.dat"
	fclose(ptr);
}


void elimina_pref(FILE *ptr) {

	// Puntatori a char contenente l'ascolto di un artista
	char *listen = "Ascolta";

	char pref_utente[7];	// Dichiarazione variabile preferenza utente temporanea

	// Variabili locali alla funzione
	int j, k, a, b, i = 0;

	int presente = 0; // Variabile di controllo

	// Apertura file in lettura binaria
	if ((ptr = fopen("preferenze.dat", "rb")) == NULL) {
		printf("ERRORE FILE.\n");

	} else {

		// Ciclo fino alla fine del file per leggere l'intero file degli artisti
		j = 0;
		rewind(ptr);
		while (!feof(ptr)) {
			fread(&preftemp, sizeof(pref), 1, ptr);
			j++;
		}

		j--;	// Ultimo indirizzo relativo all'ultima struct "preftemp" scritta del file

		// Inserimento nome dell'artista
		system("cls");
		printf("Inserire il nome dell'artista di cui si vuole eliminare l'ultimo voto: \n");

		// Azzeramento variabile di controllo e azzeramento campo "pref.artista"
		presente = 0;
		memset(&pref.artista, 0, sizeof(pref.artista));

		// Acquisizione in input del nome dell'artista votato
		fflush(stdin);
		gets(pref.artista);

		// Conversione array per scrittura in file, converte ogni posizione
		k = 0;
		while (pref.artista[k]) {
			pref.artista[k] = conversione(pref.artista[k]);
			k++;
		}

		k = 0;
		presente = 0;
		rewind(ptr);											// Riavvolgimento dello stream, posizione del puntatore a inizio file
		while (!feof(ptr)) {								    // Ciclo che termina alla fine del file
			fseek(ptr, k * sizeof(pref), SEEK_SET);			    // Posiziona il puntatore alla posizione determinata dall'offset "k"
			fread(&preftemp, sizeof(pref), 1, ptr);				// Caricamento in memoria della struct "preftemp"
			if (!strcmp(preftemp.artista, pref.artista)	        // Confronto fra le due stringhe "preftemp.artista" e "pref.artista" e
					&& strcmp(preftemp.preferenza, listen)) {	// verifica la presenza della stringa "listen" nel campo "preftemp.preferenza". Se corretto,
				printf("\nArtista in elenco!\n");               // ritorna un messaggio di conferma (l'artista è stato trovato nel database) e
				presente = 1;                                   // setta la variabile di controllo "presente" ad 1
				break;
			}

			k++;   // Incremento offset "k"
		}
	}

	// Chiusura del file "preferenze.dat"
	fclose(ptr);

	// Copia il contenuto del campo "preftemp.preferenza" nella variabile temporanea "pref_utente"
	strcpy(pref_utente, preftemp.preferenza);

	// Se la variabile di controllo "presente" è uguale ad 1 (artista trovato nel database)
	if (presente == 1) {

		printf("Ultimo voto assegnato all'artista: '%s', "
				"vuoi eliminarlo? 1) Si  2) No\n", preftemp.preferenza);

		// Cicla fino a quando la variabile "a" non è uguale ad 1 (scelta dell'utente sì/no)
		a = 0;
		while (a != 1) {

			// Acquisizone della scelta dell'utente
			scanf("%d", &b);

			// Se la scelta corrisponde ad 1 oppure a 2, esci dal ciclo. Altrimenti...
			if (b == 1 || b == 2)
				a++;

			else
				printf("Scelta errata, riprova.\n"); // ...ritorna un messaggio di errore
		}

		// Se la variabile "b" è uguale ad 1
		if (b == 1) {

			// Apertura file in scrittura binaria distruttiva
			ptr = fopen("pref_temp.txt", "wb");
			fclose(ptr);	//chiusura del file

			// Inizializzazione ciclo for che va dall'indirizzo 0 all'indirizzo k,
			// apertura del file "preferenze.dat" in lettura, caricamento della struct "preftemp" in memoria e chiusura del file "preferenze.dat".
			// Apertura del file "pref_temp.txt" in scrittura binaria, scrittura della struct "preftemp" in memoria
			// e chiusura del file "pref_temp.txt"
			for (i = 0; i < k; i++) {

				if ((ptr = fopen("preferenze.dat", "rb")) == NULL) {
					printf("ERRORE FILE.\n");
				} else {
					fseek(ptr, i * sizeof(pref), SEEK_SET);
					fread(&preftemp, sizeof(pref), 1, ptr);
				}

				fclose(ptr);

				if ((ptr = fopen("pref_temp.txt", "rb+")) == NULL) {
					printf("ERRORE FILE.\n");
				} else {
					fseek(ptr, i * sizeof(pref), SEEK_SET);
					fwrite(&preftemp, sizeof(pref), 1, ptr);
				}

				fclose(ptr);
			}

			// Assegna il valore dell'offset "k" ad "a" e incrementa a di 1
			a = k;
			a++;

			// Inizializzazione ciclo for che va dall'indirizzo "a" all'indirizzo j (indirizzi totali),
			// apertura del file "preferenze.dat" in modalità lettura, caricamento della struct "preftemp" in memoria, chiusura del file "preferenze.dat".
			// Apertura del file "pref_temp.txt" in scrittura binaria, scrittura della struct "preftemp" in memoria alla posizione dell'indirizzo "k"
			// e chiusura del file "pref_temp.txt"
			for (i = a; i < j; i++) {

				if ((ptr = fopen("preferenze.dat", "rb")) == NULL) {
					printf("ERRORE FILE.\n");
				} else {
					fseek(ptr, i * sizeof(pref), SEEK_SET);
					fread(&preftemp, sizeof(pref), 1, ptr);
				}

				fclose(ptr);

				if ((ptr = fopen("pref_temp.txt", "rb+")) == NULL) {
					printf("ERRORE FILE.\n");
				} else {
					fseek(ptr, k * sizeof(pref), SEEK_SET);
					fwrite(&preftemp, sizeof(pref), 1, ptr);
				}

				k++;
				fclose(ptr);
			}

			// Apertura file in scrittura binaria distruttiva
			ptr = fopen("preferenze.dat", "wb");
			fclose(ptr);  // Chiusura del file "preferenze.dat"

			// Inizializzazione ciclo for che va dall'indirizzo 0 all'indirizzo k (indirizzi totali),
			// apertura del file "pref_temp.txt" in modalità lettura, caricamento della struct "preftemp" in memoria, chiusura del file "pref_temp.txt".
			// Apertura del file "preferenze.dat" in scrittura binaria, scrittura della struct  in memoria
			// e chiusura del file "preferenze.dat"
			for (i = 0; i < k; i++) {

				if ((ptr = fopen("pref_temp.txt", "rb")) == NULL) {
					printf("ERRORE FILE.\n");

				} else {
					fseek(ptr, i * sizeof(pref), SEEK_SET);
					fread(&preftemp, sizeof(pref), 1, ptr);
				}

				fclose(ptr);

				if ((ptr = fopen("preferenze.dat", "rb+")) == NULL) {
					printf("ERRORE FILE.\n");

				} else {
					fseek(ptr, i * sizeof(pref), SEEK_SET);
					fwrite(&preftemp, sizeof(pref), 1, ptr);
				}

				fclose(ptr);
			}

			printf("\nVoto eliminato.\n");
			system("pause");
			system("cls");

			// Se la variabile "b" è diversa da 1, ritorna un messaggio di errore (voto non eliminato)
		} else {
			printf("Voto non eliminato.\n");
			system("pause");
			system("cls");

		}

		// Se la varabile di controllo "presente" è diversa da 1, ritorna un messaggio di errore (artista non trovato)
	} else {
		printf("Artista non presente in elenco.\n");
		system("pause");
	}

}

