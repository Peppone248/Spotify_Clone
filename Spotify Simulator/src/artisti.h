/*
 * artisti.h
 *
 *  Created on: 28 gen 2018
 *      Author: Antonio Pansini
 */

#ifndef ARTISTI_H_
#define ARTISTI_H_

#include "varlib.h"

char conversione (char a);
void aggiunta_artisti (FILE *ptr);
void modifica_artista (FILE *ptr);
void ricerca_artisti (FILE *ptr);
void visual_artisti (FILE *ptr);
void elimina_artista (FILE *ptr);
void artisti_piu_ascoltati (FILE *ptr);

#endif /* ARTISTI_H_ */
