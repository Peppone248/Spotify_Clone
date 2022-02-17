/*
 * varlib.h
 *
 *  Created on: 28 gen 2018
 *      Author: Antonio Pansini
 */

#ifndef VARLIB_H_
#define VARLIB_H_

// Includo librerie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

char conversione(char a);

// Dichiaro una nuova variabile di tipo "artist"
typedef struct {
	int id;
	char nome[21];
	char genere[16];
	char prod[26];
	char nazione[16];
	int anno;
} artist;

// Dichiaro una nuova variabile di tipo "user"
typedef struct {
	int id;
	char username[21];
	char nome[21];
	char cognome[21];
} user;

// Dichiaro una nuova variabile di tipo "preferenza"
typedef struct {
	char artista[26];
	char preferenza[7];
} preferenza;

user utente;
user utentetemp;
artist artista;
artist artistatemp;
preferenza pref;
preferenza preftemp;

#endif /* VARLIB_H_ */
