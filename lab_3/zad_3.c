#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

struct struktura{
int a;
double b;
char c;
};

void *lok_watek (void *arg_wsk) {
struct struktura s_lok = *((struct struktura*)arg_wsk);
s_lok.a++;
s_lok.b++;
s_lok.c++;
printf("watek poboczny(lok_watek): a =%d\tb =%f\tc=%c\n", s_lok.a, s_lok.b, s_lok.c);
return NULL;
}

void *glob_watek (void *arg_wsk) {
struct struktura *s_wsk = (struct struktura*)arg_wsk;
s_wsk->a++;
s_wsk->b++;
s_wsk->c++;
printf("watek poboczny(glob_watek): a =%d\tb =%f\tc=%c\n", s_wsk->a, s_wsk->b, s_wsk->c);
return NULL;
}


int main() {

struct struktura main_struct = {3, 2.5, 'a'};
    pthread_t tid_1;

    printf("watek glowny: a =%d\tb =%f\tc=%c\n", main_struct.a, main_struct.b, main_struct.c);

    //lok_watek
    pthread_create(&tid_1, NULL, lok_watek, &main_struct);
    pthread_join(tid_1, NULL);
    printf("watek glowny: a =%d\tb =%f\tc=%c\n", main_struct.a, main_struct.b, main_struct.c);

    //glob_watek
    pthread_create(&tid_1, NULL, glob_watek, &main_struct);
    pthread_join(tid_1, NULL);
    printf("watek glowny: a =%d\tb =%f\tc=%c\n", main_struct.a, main_struct.b, main_struct.c);

   




return(0);

}
