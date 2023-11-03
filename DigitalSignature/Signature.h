#ifndef SIGNATURE
#define SIGNATURE

#include "Rsa.h"
#include "Hash.h"
#include <stdio.h>
#include <stdlib.h>

extern char keyGeneration();
extern int* signString(char* str);
extern void signatureVerification(char* str, int* signature);

#endif // !SIGNATURE