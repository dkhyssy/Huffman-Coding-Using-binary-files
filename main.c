#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "bt.h"

int main() {
    printf("=== Projet Codage de Huffman - Test des Etapes 1 a 4 ===\n\n");

    const char* filename = "test_huffman.txt";
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        printf("Erreur lors de la creation du fichier de test.\n");
        return 1;
    }
    fprintf(f, "huffman coding project test");
    fclose(f);
    printf("Fichier de test '%s' cree avec succes.\n", filename);


    printf("Generation des codes de Huffman :\n");
    printf("--------------------------------\n");
    huffmanCodingFromFile(filename);
    printf("--------------------------------\n");

    printf("\nTest termine avec succes !\n");

    return 0;
}
