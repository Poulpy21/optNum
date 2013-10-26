#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

void rand_init(void) {
	srand(time(NULL));
}

/*Renvoie un float/double aléatoire entre 0.0 et 1.0*/
float random_float_uniform() {
	return (float)rand()/(float)RAND_MAX;
}

double random_double_uniform() {
	return (double)rand()/(double)RAND_MAX;
}


/*Renvoie un float/double aléatoire entre a et b*/
float random_float(float a, float b) {
	return a + (b - a) * random_float_uniform();
}

double random_double(double a, double b) {
	return a + (b - a) * random_double_uniform();
}


/*Renvoie un booleen aléatoire*/
bool random_boolean() {
	return (random_float_uniform() > 0.5f);
}

/*Renvoie un int/long aléatoire entre a et b*/
int random_int(int a, int b) {
	return (int) ((b - a + 1) * random_double_uniform());
}

unsigned int random_uint(unsigned int a, unsigned int b) {
	return (unsigned int) ((b - a + 1) * random_double_uniform());
}

long random_long(long a, long b) {
	return (long) ((b - a + 1) * random_double_uniform());
}

unsigned long random_ulong(unsigned long a, unsigned long b) {
		return (unsigned long) ((b - a + 1) * random_double_uniform());
	}

int8_t random_int8(int8_t a, int8_t b) {
	return (int8_t) ((b - a + 1) * random_double_uniform());
}

int16_t random_int16(int16_t a, int16_t b) {
	return (int16_t) ((b - a + 1) * random_double_uniform());
}

int32_t random_int32(int32_t a, int32_t b) {
	return (int32_t) ((b - a + 1) * random_double_uniform());
}

int64_t random_int64(int64_t a, int64_t b) {
	return (int64_t) ((b - a + 1) * random_double_uniform());
}

uint8_t random_uint8(uint8_t a, uint8_t b) {
	return (uint8_t) ((b - a + 1) * random_double_uniform());
}

uint16_t random_uint16(uint16_t a, uint16_t b) {
	return (uint16_t) ((b - a + 1) * random_double_uniform());
}

uint32_t random_uint32(uint32_t a, uint32_t b) {
	return (uint32_t) ((b - a + 1) * random_double_uniform());
}

uint64_t random_uint64(uint64_t a, uint64_t b) {
	return (uint64_t) ((b - a + 1) * random_double_uniform());
}


/*Renvoie une string de int alétoire*/
char *random_char(int longueur)
{
	char *chaine = malloc((longueur + 1) * sizeof(char));

	for (int i = 0; i < longueur; i++) { 
		chaine[i] = (char) (rand() % 26 + 'a');		
	}

	chaine[longueur] = '\0';

	return chaine;
}

/*Renvoie une chaine de caractère aléatoire*/
char *random_char_int(int longueur)
{
	char *chaine = malloc((longueur + 1) * sizeof(char));
	for (int i = 0; i < longueur; i++) { 
		chaine[i] = (char) (rand() % 10 + '0');		
	}

	chaine[longueur] = '\0';

	return chaine;
}
