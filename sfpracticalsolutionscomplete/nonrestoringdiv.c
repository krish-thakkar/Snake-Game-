#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to add two binary numbers
char* add(const char* A, const char* M) {
    int carry = 0;
    char* Sum = (char*)malloc(strlen(A) + 1);
    int i = strlen(A) - 1;
    for (; i >= 0; i--) {
        int temp = (A[i] - '0') + (M[i] - '0') + carry;
        if (temp > 1) {
            Sum[i] = (temp % 2) + '0';
            carry = 1;
        } else {
            Sum[i] = temp + '0';
            carry = 0;
        }
    }
    Sum[strlen(A)] = '\0';
    return Sum;
}

// Function to find the complement of a binary number
char* complement(const char* m) {
    char* M = (char*)malloc(strlen(m) + 1);
    int i = 0;
    for (; i < strlen(m); i++) {
        M[i] = ((m[i] - '0') + 1) % 2 + '0';
    }
    M[strlen(m)] = '\0';

    char* result = add(M, "0001");
    free(M);
    return result;
}

// Function to perform Non-Restoring Division
void nonRestoringDivision(char* Q, const char* M, char* A, int size) {
    int count = size;
    char* comp_M = complement(M);
    char flag[13] = "successful\0"; // Increase the size to accommodate the full string

    printf("Initial Values: A: %s Q: %s M: %s\n", A, Q, M);

    while (count) {
        printf("\nStep: %d", size - count + 1);
        printf(" Left Shift and ");

        memmove(A + 1, A, strlen(A));
        A[0] = Q[0];

        if (strcmp(flag, "successful") == 0) {
            char* sum = add(A, comp_M);
            strcpy(A, sum);
            free(sum);
            printf("Subtract: ");
        } else {
            char* sum = add(A, M);
            strcpy(A, sum);
            free(sum);
            printf("Addition: ");
        }

        printf("A: %s Q: %s_", A, Q + 1);

        if (A[0] == '1') {
            memmove(Q, Q + 1, strlen(Q));
            Q[size - 1] = '0';
            printf(" -Unsuccessful");
            strcpy(flag, "unsuccessful");
            printf(" A: %s Q: %s -Addition in next Step\n", A, Q);
        } else {
            memmove(Q, Q + 1, strlen(Q));
            Q[size - 1] = '1';
            strcpy(flag, "successful");
            printf(" Successful");
            printf(" A: %s Q: %s -Subtraction in next step\n", A, Q);
        }
        count--;
    }
    printf("\nQuotient(Q): %s Remainder(A): %s\n", Q, A);
    free(comp_M);
}

// Function to convert decimal to binary string
char* decimalToBinary(int num, int size) {
    char* binary = (char*)malloc(size + 1);
    int i = size - 1;
    for (; i >= 0; i--) {
        binary[i] = (num & 1) + '0';
        num >>= 1;
    }
    binary[size] = '\0';
    return binary;
}

// Function to find the two's complement of a binary number for negative numbers
char* twosComplement(const char* m, int size) {
    char* M = (char*)malloc(size + 1);
    int i = 0;
    for (; i < size; i++) {
        M[i] = (m[i] == '1') ? '0' : '1'; // Flip the bits
    }
    M[size] = '\0';

    // Adding 1 to the least significant bit
    for (i = size - 1; i >= 0; i--) {
        if (M[i] == '0') {
            M[i] = '1';
            break;
        } else {
            M[i] = '0';
        }
    }

    return M;
}

int main() {
    int choice;
    const int size = 4;
    char Q[size + 1], A[size + 1];
    char divisor[size + 1]; // Declare divisor array

    do {
        printf("\nMenu:\n1. Unsigned Non-Restoring Division\n2. Signed Non-Restoring Division\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int dividend, divisorSize;
                printf("Enter unsigned dividend (less than 16): ");
                scanf("%d", &dividend);
                printf("Enter divisor (less than 16): ");
                scanf("%d", &divisorSize);

                char* binaryDividend = decimalToBinary(dividend, size);
                char* binaryDivisor = decimalToBinary(divisorSize, size);
                strcpy(Q, binaryDividend);
                strcpy(A, "0000");
                strcpy(divisor, binaryDivisor);
                nonRestoringDivision(Q, divisor, A, size);

                free(binaryDividend);
                free(binaryDivisor);
                break;
            }
            case 2: {
                int dividend, divisorSize;
                printf("Enter signed dividend (less than 16): ");
                scanf("%d", &dividend);
                printf("Enter divisor (less than 16): ");
                scanf("%d", &divisorSize);

                // Handle negative dividend by getting its two's complement
                char* binaryDividend;
                if (dividend >= 0) {
                    binaryDividend = decimalToBinary(dividend, size);
                } else {
                    binaryDividend = twosComplement(decimalToBinary(abs(dividend), size), size);
                }

                char* binaryDivisor = decimalToBinary(divisorSize, size);
                strcpy(Q, binaryDividend);
                strcpy(A, (dividend < 0) ? "1111" : "0000");
                strcpy(divisor, binaryDivisor);
                nonRestoringDivision(Q + 1, divisor, A, size);

                free(binaryDividend);
                free(binaryDivisor);
                break;
            }
            case 3: {
                printf("Exiting the program.\n");
                break;
            }
            default: {
                printf("Invalid choice! Please enter a valid option.\n");
                break;
            }
        }
    } while (choice != 3);

    return 0;
}
