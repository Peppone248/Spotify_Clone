/*
 * varlib.c
 *
 *  Created on: 28 gen 2018
 *      Author: Antonio Pansini
 */

#include "varlib.h"

// Funzione conversione caratteri per scrittura nei file
char conversione(char a) {

	// Se il carattere passato alla funzione è una lettera, questa viene convertita in minuscolo
	if (isalpha(a))
	{
		a = tolower(a);
	}

	// Se il carattere passato alla funzione è uno spazio, questo viene convertito in underscore
	if (a == ' ')
		a = '_';

	// Restituisce il carattere c passato alla funzione
	return a;
}
