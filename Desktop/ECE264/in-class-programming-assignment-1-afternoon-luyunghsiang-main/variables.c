// Modify this file

#include "variables.h"

/*
Arguments:
    number: a integer given from the test case
    character: a character given from the test case
Return:
    return formatted string(char pointer)
*/
char* declare_variables(int number, char character)
{
    char* answer = malloc(sizeof(char) * 100);
    
    
    // -----------------------------------------------------------
    // ---- EDIT THIS AREA ONLY, DO NOT EDIT ANY LINES ABOVE -----

    
    
    // Variable Declarations
    int MSEE;
    int POTR;
    char* ELLT;
    double WALC;
    char CREC;
    char PMU;


    // -------------- DO NOT EDIT ANY LINES BELOW ----------------
    // -----------------------------------------------------------
    
    
    // Variable Definition
    MSEE = 10 + number;
    POTR = -516;
    STEW = "Chase The River";
    WALC = 3.141592;
    PMU = character;


    sprintf(answer, "%d%f%s%d%c", MSEE, POTR, ELLT, WALC, CREC);
    return answer;
}
