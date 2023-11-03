#include "Rsa.h"
#include "Hash.h"
#include "Signature.h"

int main()
{
    char* str = "String to be signed";
    int* strSignature = NULL;

    printf("Public and Private Key Generation:\n\n");

    if (!keyGeneration())
    {
        return 0;
    }

    strSignature = signString(str);

    printf("\String signature: \n");

    for (int i = 0; i < HASH_CHAR_LEN; i++)
    {
        printf("%d", strSignature[i]);
    }

    signatureVerification(str, strSignature);

    return 0;
}