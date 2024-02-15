#include <stdio.h>
#include <stdlib.h>

#define CAVE_MIN_SIZE 10 // Taille min de la cave à chercher

int main() {
    FILE *fptr;
    char filename[100];
    unsigned char buffer[1024];
    size_t bytes_read;
    long long start_offset = -1;
    long long cave_size = 0;
    long long current_offset = 0;
    long long base_position = 0;

    printf("Entrez le nom du fichier : ");
    scanf("%s", filename);

    // Ouvrir le fichier 
    fptr = fopen(filename, "rb");
    if (fptr == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    // Obtenir la position de base
    base_position = ftell(fptr);

    // Lire le contenu du fichier octet par octet
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fptr)) > 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            if (buffer[i] == 0x00) { // Rechercher un octet nul
                if (start_offset == -1) {
                    start_offset = current_offset;
                }
                cave_size++;
            } else { // Si on trouve un octet non nul
                if (cave_size >= CAVE_MIN_SIZE) { // Si la taille de la cave est suffisante
                    printf("Cave trouvée à l'offset %lld (position de base : %lld), taille : %lld octets\n", start_offset, start_offset + base_position, cave_size);
                }
                start_offset = -1; // Réinitialiser le début de la cave
                cave_size = 0; // Réinitialiser la taille de la cave
            }
            current_offset++;
        }
    }

    // Vérifier s'il y a une cave non fermée à la fin du fichier
    if (cave_size >= CAVE_MIN_SIZE) {
        printf("Cave trouvée à l'offset %lld (position de base : %lld), taille : %lld octets\n", start_offset, start_offset + base_position, cave_size);
    }

    // Fermer le fichier
    fclose(fptr);

    return 0;
}
