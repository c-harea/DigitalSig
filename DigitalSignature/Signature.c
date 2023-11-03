#include "Signature.h"

static int n, pubKey, prvKey;

char keyGeneration() {

    unsigned int p, q, lambda;

    printf("Enter the first prime number: ");
    scanf("%u", &p);

    if (!prime(p)) {
        printf("\nWrong Input, you must enter a prime number\n");
        getchar();
        return 0;
    }

    printf("\nEnter the second prime number: ");
    scanf("%u", &q);

    if (!prime(q)) {
        printf("\nWrong Input, you must enter a prime number\n");
        getchar();
        return 0;
    }

    n = p * q;
    printf("\nThe compute of n is: %u\n", n);

    lambda = lcm(p - 1, q - 1);
    printf("The lambda value is: %u\n", lambda);

    printf("Choose a coprime number(e - private key) < %u: ", lambda);
    scanf("%u", &prvKey);

    if (prvKey > lambda) {
        printf("\nWrong Input, you must choose a prime number < %u\n", lambda);
        getchar();
        return 0;
    }

    if (!prime(prvKey)) {
        printf("\nWRONG INPUT\n");
        getchar();
        return 0;
    }

    pubKey = modInverse(prvKey, lambda);
    printf("The compute of d(public key) is: %u\n", pubKey);
}

int* signString(char* str) {

    char* hash = SHA256_Main(str);
    printf("String hash: \n");
    printf("%s\n", hash);

    int* signature = (int*)malloc(65 * sizeof(int));

    for (int i = 0; i < HASH_CHAR_LEN; i++)
    {
        signature[i] = (int)hash[i];
        signature[i] = moduloPow(signature[i], prvKey, n);
    }

    return signature;
}

void signatureVerification(char* str, int* signature) {

    char* hash = malloc(HASH_CHAR_LEN + 1);

    hash[HASH_CHAR_LEN] = '\0';

    for (int i = 0; i < HASH_CHAR_LEN; i++)
    {
        signature[i] = moduloPow(signature[i], pubKey, n);
        hash[i] = (char)signature[i];
    }

    printf("\n\nDecrypted signature: \n");
    printf("%s\n", hash);

    char* strHash = SHA256_Main(str);

    printf("\n\nComputed string hash value: \n");
    printf("%s\n", strHash);

    for (int i = 0; i < HASH_CHAR_LEN; i++)
    {
        if (strHash[i] != hash[i])
        {
            printf("\nSignature didn't pass!");

            return;
        }
    }

    printf("\nSignature passed!");

}