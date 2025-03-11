#ifndef _czytelnia_
#define _czytelnia_

/*** Definicje typow zmiennych ***/
typedef struct {
  int l_p, l_wait_p; // liczba piszacych
  int l_c, l_wait_c; // liczba czytajacych
  // <- zasoby czytelni
  pthread_mutex_t mutex;
  pthread_cond_t czytelnicy;
  pthread_cond_t pisarze;
  pthread_rwlock_t rwlock;

} cz_t;

/*** Deklaracje procedur interfejsu ***/
void inicjuj(cz_t* czytelnia_p);
void czytam(cz_t* czytelnia_p);
void pisze(cz_t* czytelnia_p);

int my_read_lock_lock(cz_t* czytelnia_p);
int my_read_lock_unlock(cz_t* czytelnia_p);
int my_write_lock_lock(cz_t* czytelnia_p);
int my_write_lock_unlock(cz_t* czytelnia_p);

#endif
