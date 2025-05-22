#include <stdio.h>
#include <time.h>

int main() {
    time_t dabartinis_laikas;
    struct tm *lokalus_laikas, *utc_laikas;

    // Gauti dabartinį laiką
    dabartinis_laikas = time(NULL);
    if (dabartinis_laikas == -1) {
        perror("time");
        return 1;
    }

    // Konvertuoti į lokalų laiką
    lokalus_laikas = localtime(&dabartinis_laikas);
    if (lokalus_laikas == NULL) {
        perror("localtime");
        return 1;
    }

    // Konvertuoti į UTC laiką
    utc_laikas = gmtime(&dabartinis_laikas);
    if (utc_laikas == NULL) {
        perror("gmtime");
        return 1;
    }

    // Atspausdinti abu
    printf("Lokalus laikas: %s", asctime(lokalus_laikas));
    printf("UTC (GMT) laikas: %s", asctime(utc_laikas));

    return 0;
}
