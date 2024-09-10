#include "tools/hint.h"
#include "tools/color.h"
#include "tools/info.h"
#include <stdio.h>
const char* hello = "Hello, WinterCode";
int main() {
    printf("%s%s%s\n ", TWINKLING, hello, RESET);
    welcomeMessage();
    invalidMessage();
    successMessage();
    failureMessage();
    illegalMessage();
    loadingMessage();
    exitingMessage();
    
    return 0;
}
