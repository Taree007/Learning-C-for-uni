/* Gintare Jasiukeviciute IFD 3/2 e8330 */
/* Failas: e8330_nice01.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Naudojimas: %s <nice reikšmė>\n", argv[0]);
        return 1;
    }

    int nice_val = atoi(argv[1]);

    // Bandom nustatyti nice reikšmę
    errno = 0;
    int actual_nice = nice(nice_val);
    if (actual_nice == -1 && errno != 0) {
        perror("nice");
        return 1;
    }
    printf("Nustatytas nice lygis: %d\n", actual_nice);

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    volatile unsigned long long sum = 0;
    for (unsigned long long i = 0; i < 50000000000ULL; i++) {
        sum += i;
    }

    gettimeofday(&end_time, NULL);

    // Laiko skirtumas
    double elapsed = (end_time.tv_sec - start_time.tv_sec) +
                     (end_time.tv_usec - start_time.tv_usec) / 1e6;

    printf("Pradžios laikas: %ld.%06ld s\n", start_time.tv_sec, start_time.tv_usec);
    printf("Pabaigos laikas: %ld.%06ld s\n", end_time.tv_sec, end_time.tv_usec);
    printf("Trukmė: %.3f sekundžių\n", elapsed);

    // CPU sunaudotas laikas
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    double user_time = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec / 1e6;
    double sys_time = usage.ru_stime.tv_sec + usage.ru_stime.tv_usec / 1e6;

    printf("Naudotojo (user) CPU laikas: %.3f s\n", user_time);
    printf("Sistemos (system) CPU laikas: %.3f s\n", sys_time);
    printf("Iš viso CPU laiko: %.3f s\n", user_time + sys_time);

    return 0;
}
