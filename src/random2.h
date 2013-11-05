

#include <stdint.h>
#include <stdbool.h>

#ifndef RANDOM2_H
#define RANDOM2_H

/*
FICHIER RANDOM.H
Librairie de random 
*/


/*Initialise la seed*/
void rand_init();

/*Renvoie un float/double aléatoire entre 0.0 et 1.0*/
float random_float_uniform();
double random_double_uniform();

/*Renvoie un float/double aléatoire entre a et b*/
float random_float(float a, float b);
double random_double(double a, double b);

/*Renvoie un booleen aléatoire*/
bool random_boolean(); 

/*Renvoie un int/long aléatoire entre a et b*/
int random_int(int a, int b);
unsigned int random_uint(unsigned int a, unsigned int b);

long random_long(long a, long b);
unsigned long random_ulong(unsigned long a, unsigned long b);

int8_t random_int8(int8_t a, int8_t b);
int16_t random_int16(int16_t a, int16_t b);
int32_t random_int32(int32_t a, int32_t b);
int64_t random_int64(int64_t a, int64_t b);

uint8_t random_uint8(uint8_t a, uint8_t b);
uint16_t random_uint16(uint16_t a, uint16_t b);
uint32_t random_uint32(uint32_t a, uint32_t b);
uint64_t random_uint64(uint64_t a, uint64_t b);

/*Renvoie une string de int alétoire*/
char *random_char_int(int longueur);

/*Renvoie une chaine de caractère aléatoire*/
char *random_char(int longueur);

#endif
