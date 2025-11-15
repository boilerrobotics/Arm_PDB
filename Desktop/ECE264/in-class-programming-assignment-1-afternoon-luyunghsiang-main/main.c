// Do NOT modify this file

#include "variables.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }

    char* answer = declare_variables(atoi(argv[1]), argv[2][0]);
    printf("%s", answer);
    free(answer);
    return EXIT_SUCCESS;
}
