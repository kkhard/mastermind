#include <stdio.h> // printf, scanf
#include <stdlib.h> // rand, srand, sizeof, malloc, free
#include <time.h> // time
#include <string.h> // strcmp, strcpy

int validate_color_code(char* input, char* result);

int main() {
    // Seed wird anhand der aktuellen Zeit ausgerichtet, damit immer andere Werte erzeugt werden
    srand((unsigned int)time(NULL));
    // Zufallszahlen erstellen, auf deren Basis die Farben generiert werden
    int numbers[4];
    for (int i = 0; i < 4; ++i) {
        numbers[i] = (rand() % 6) + 1;
    }
    // Zufallszahlen in einen String umwandeln, der die einzelnen Farben (rot, gruen, blau, gelb, orange, lila) enthält
    char color_code[5];
    for (int i = 0; i < 5; ++i) {
        if (i == 4) {
            color_code[i] = '\0';
        } else {
            switch(numbers[i]) {
                case 1:
                    color_code[i] = 'R';
                    break;
                case 2: 
                    color_code[i] = 'G';
                    break;
                case 3:
                    color_code[i] = 'B';
                    break;
                case 4:
                    color_code[i] = 'Y';
                    break;
                case 5:
                    color_code[i] = 'O';
                    break;
                case 6:
                    color_code[i] = 'P';
                    break;
                default:
                    break;
            }
        }
    }
    printf("*******************************************************************************************************************************\n"
    "***** Welcome to Master Mind 2024!\n***** Your task is to guess the color code of four randomly selcted colors.\n"
    "***** Colors you can select from are: red, green, blue, yellow, orange, purple.\n" 
    "***** Please enter your code in the following format: 'RGBR' for red, green, blue, red.\n"
    "***** You will receive hints in the form of black and white pins.\n***** A black pin means your guess is correct and in the right position," 
    " a white pin means your guess is correct but not in the right position.\n***** The round cap is 12.\n"
    "*******************************************************************************************************************************");
    // Schleife, sodass das Spiel 12 Runden lang geht
    for (int i = 0; i < 12; ++i) {
        printf("\nRound %d, please enter your guess (colors: red, green, blue, yellow, orange, purple): ", i + 1);
        char input[5];
        scanf("%4s", input);
        if (validate_color_code(input, color_code) == 0) {
            printf("You win!\n");
            return 0;
        }
    }
    printf("You could not guess the code, restart the program if you'd like to try again. The correct code was: %s\n", color_code);
}

int validate_color_code(char* input, char* result) {
    // Kopie des Zielstrings wird erstellt, sodass mit ihm gearbeitet werden kann, insbesondere um die Ausgabe weißer und schwarzer Pins zu vereinfachen;
    // den ursprünglichen Ergebnis-String darf nicht manipuliert werden, da andernfalls undefined behavior auftritt
    char copy_result[5];
    strcpy(copy_result, result);
    // Kopie des Inputstrings wird erstellt, sodass mit ihm gearbeitet werden kann (s.o. bzgl. Zielstring)
    char copy_input[5];
    strcpy(copy_input, input);
    // Zählervariablen für die pins, die die Hinweise geben
    int white = 0;
    int black = 0;
    // Gleichheit wird geprüft, zudem werden die schwarzen Pins gezählt
    for (int i = 0; i < 4; ++i) {
        if (strcmp(copy_input, copy_result) == 0) {
            return 0;
        } else if (copy_input[i] == copy_result[i]) {
            copy_result[i] = '_';  // Manipulation der bereits geprüften Positionen, sodass diese fortan ungleich sind
            copy_input[i] = '*'; 
            black++;
        }
    }
    // nun werden die weißen Pins gezählt
    for (int i = 0; i < 4; ++i) {
        for (int k = 0; k < 4; ++k) {
            if (copy_input[i] == copy_result[k]) {
                white++;
                copy_result[k] = '_'; // Manipulation der bereits geprüften Positionen, sodass diese fortan ungleich sind
                copy_input[i] = '*'; 
            }
        }
    }
    // Ausgabe
    printf("Black pins: %d, White pins: %d\n", black, white);
    return 1;
}