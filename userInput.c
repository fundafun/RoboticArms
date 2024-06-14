#include <stdio.h>
#include "digits.h"



int digit1, digit2, digit3, digit4;

int main() {
    printf("Enter the first digit: ");
    scanf("%1d", &digit1);

    printf("Enter the second digit: ");
    scanf("%1d", &digit2);

    printf("Enter the third digit: ");  
    scanf("%1d", &digit3);

    printf("Enter the fourth digit: ");
    scanf("%1d", &digit4);

    printf("You entered: %d, %d, %d, %d\n", digit1, digit2, digit3, digit4);

    return 0;
}