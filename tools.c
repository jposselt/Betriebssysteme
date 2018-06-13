//#include <stddef.h>
//#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "tools.h"

/* Bestimmt die Dateiendung */
const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

/*Hilfsfunktion zum Lesen des Dateiinhalts */
const char *get_file_content(const char *filename) {
    char *buffer = "";

    /* Öffne Datei zum Lesen */
    FILE *infile = fopen(filename, "r");

    /* Abbruch, falls Datei nicht existiert */
    if (infile == NULL) {
        perror("Fehler beim Lesen der Datei: ");
        return buffer;
    }

    /* Suche Dateiender */
    if (fseek (infile, 0, SEEK_END)) {
        perror("Fehler beim Lesen der Datei: ");
    }

    /* Länge der Datei*/
    long length = ftell (infile);
    if (length < 0) {
        perror("Fehler beim Lesen der Datei: ");
    }

    /* Zurück zum Anfang */
    if (fseek (infile, 0, SEEK_SET)) {
        perror("Fehler beim Lesen der Datei: ");
    }

    /* Datei einlesen */
    buffer = malloc (length);
    if (buffer) {
        fread (buffer, 1, length, infile);
    } else {
        perror("Fehler beim Lesen der Datei: ");
    }

    /* Datei schließen */
    fclose(infile);

    /* Rückgabe */
    return buffer;
}

int write_file(const char *filename, const char *content) {
    FILE *outfile = fopen(filename, "w");
    if (outfile != NULL)
    {
        fputs(content, outfile);
        fclose(outfile);
        return EXIT_SUCCESS;
    } else {
        perror("Fehler beim Schreiben der Datei: ");
        return EXIT_FAILURE;
    }
}