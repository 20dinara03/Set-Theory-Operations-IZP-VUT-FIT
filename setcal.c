#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 29

char* COMMAND_LIST[20] = {"empty", "card", "complement" , "union", "intersect", "minus", "subseteq", "subset", "equals", "reflexive", "symmetric", "antisymmetric", "transitive", "function", "domain", "codomain", "injective", "surjective", "bijective"};

#define SET_CLEAN {\
    for (int i = 0; i < setCounter; i++) {\
        cleanArray(&sets[i].elements, sets[i].size);\
        free(sets[i].elements);\
    }\
}\

#define RELATIONS_CLEAN {\
    for (int i = 0; i < relationCounter; i++) {\
        for (int f = 0; f < relations[i].size; f++) {\
            free(relations[i].elements[f][0]);\
            free(relations[i].elements[f][1]);\
            free(relations[i].elements[f]);\
        }\
        free(relations[i].elements);\
    }\
}\

#define SAR_CLEAN {\
    if (sets != NULL) {\
        free(sets);\
    }\
    if (relations != NULL) {\
        free(relations);\
    }\
    fclose(file);\
}\

#define  MEMORY_CLEAN {\
    if (uni.elements != NULL) {\
        cleanArray(&uni.elements, uni.size);\
        free(uni.elements);\
    }\
    free(bufferLine);\
    SET_CLEAN\
    RELATIONS_CLEAN\
    SAR_CLEAN\
}\

#define IS_SET_EMPTY {\
    if (elementsCounter == 0) {\
        if (endOfLine(source[1]) || (source[1] == ' ' && endOfLine(source[2]))) {\
            (*array) = malloc(sizeof *array);\
            (*array)[0] = malloc(1);\
            (*array)[0][0] = '\0';\
            return 1;\
        }\
    }\
}\

#define IS_RELATION_EMPTY {\
    if (relationsCounter == 0) {\
        if (endOfLine(source[1]) || (source[1] == ' ' && endOfLine(source[2]))) {\
            (*array) = malloc(sizeof *array);\
            (*array)[0] = malloc(2 * sizeof **array);\
            (*array)[0][0] = malloc(1);\
            (*array)[0][1] = malloc(1);\
            (*array)[0][0][0] = '\0';\
            (*array)[0][1][0] = '\0';\
            return 1;\
        }\
    }\
}\

typedef struct {
    char** elements;
    int size;
} universe;

//Structure for sets
typedef struct {
    char** elements;
    int position;
    int size;
} set;

//Structure for relations
typedef struct {
    char*** elements;
    int position;
    int size;
} relation;

//Cleans an array of chars
void clean(char *c) {
    int count = 0;

    while(c[count] != '\0') {
        c[count] = '\0';
        count++;
    }
}

//Checks, if end of line is reached
bool endOfLine(char c) {
    if (c == '\0' || c == '\n') {
        return true;
    }
    return false;
}

//empty A
bool Empty(set *A) {
    if (A->elements[0][0] == '\0'){
        return true;
    } else {
        return false;
    }
}

//card A
void Card(set *A) {
    printf ("%d\n", A->size);
}

//union A, B
void Union(set *A, set *B) {
    printf("S ");
    if (B->size == 0) {
        for (int k = 0; k < A->size; k++) {
            printf("%s ", A->elements[k]);
            // printf("elem: %")
        }
    } else {
        for (int k = 0; k < A->size; k++) {
            printf("%s ", A->elements[k]);
            // printf("elem: %")
        }
        for (int i = 0; i < B->size; ++i) {
            for (int j = 0; j < A->size; ++j) {
                if (strcmp(B->elements[i], A->elements[j]) == 0) {
                    break;
                }
                if (j != A->size - 1) {
                    continue;
                }
                if (strcmp(B->elements[i], A->elements[A->size - 1]) != 0) {
                    printf("%s ", B->elements[i]);
                }
            }
        }
    }
    printf("\n");
}

//intersect A, B
void Intersect(set *A, set *B) {
    printf("S");
    for (int i = 0; i < A->size; ++i) {
        for (int j = 0; j < B->size; ++j) {
            if (strcmp(A->elements[i], B->elements[j]) == 0) {
                printf(" %s", A->elements[i]);
                break;
            }
        }
    }
    printf("\n");
}

//subseteq A, B
bool Subseteq(set *A, set *B) {
    if ((Empty(A)) || (Empty(B))) {
        return true;
    } else {
        for (int i = 0; i < A->size; ++i) {
            for (int j = 0; j < B->size; ++j) {
                if (strcmp(A->elements[i], B->elements[j]) == 0) {
                    break;
                }
                if (j != B->size - 1) {
                    continue;
                }
                if (strcmp(A->elements[i], B->elements[B->size - 1]) != 0) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

//equals A, B
bool Equals(set *A, set *B) {
    if (A->size == B->size) {
        return Subseteq(A, B);
    }
    return false;
}

//subset A, B
bool Subset(set *A, set *B) {
    if (Equals(A, B)) {
        return false;
    } else if(B->size == 0){
        return false;
    } else {
        for (int i = 0; i < A->size; ++i) {
            for (int j = 0; j < B->size; ++j) {
                if (strcmp(A->elements[i], B->elements[j]) == 0) {
                    break;
                }
                if (j != B->size - 1) {
                    continue;
                }
                if (strcmp(A->elements[i], B->elements[B->size - 1]) != 0) {
                    return false;
                }
            }
        }
        return true;
    }
}

//minus A, B
void Minus(set *A, set *B) {
    printf("S ");
    bool found = false;
    for (int i = 0; i < A->size; ++i) {
        for (int j = 0; j < B->size; ++j) {
            if (strcmp(A->elements[i], B->elements[j]) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            printf("%s ", A->elements[i]);
        }
    }
    printf("\n");
}

//complement A
void Complement(set *A, universe *Universe) {
    // printf ("A: %s\n", A->elements);
    printf("S");
    if (A->size == Universe->size) {
        printf("\n");
    } else if (Universe->size == 0) {
        for (int i = 0; i < A->size; ++i) {
            printf(" %s ", A->elements[i]);
        }
    } else
    {
        // printf ("\nAsize: %d\nUnisize: %d\n", A->size, Universe->size);
        for (int i = 0; i < Universe->size; ++i) {
            for (int j = 0; j < A->size; ++j) {
                // printf ("\nUnielem: %s\nAelem: %s\n", Universe->elements[i], A->elements[j]);
                if (strcmp(A->elements[j], Universe->elements[i]) == 0) {
                    break;
                }
                if (j != A->size - 1) {
                    continue;
                }
                if (strcmp(Universe->elements[i], A->elements[j - 1]) != 0) {
                    printf(" %s", Universe->elements[i]);
                }
            }
        }
    }
    printf("\n");
}

//reflexive R
bool Reflexive(relation *R, universe *Universe) {
    int ref = 0;
    for(int i = 0; i < R->size; i++) {
        if(strcmp(R->elements[i][0], R->elements[i][1]) == 0) {
            ref++;
        }
    }
    return Universe->size == ref;
}

//Symmetric R
bool Symmetric(relation *R) {
    for (int i = 0; i < R->size; ++i) {
        bool found = false;
        if (strcmp(R->elements[i][0], R->elements[i][1]) == 0){
            continue;
        }
        for (int j = 0; j < R->size; ++j) {
            if(strcmp(R->elements[i][0], R->elements[j][1]) == 0 && strcmp(R->elements[i][1], R->elements[j][0]) == 0) {
                found = true;
                break;
            }
        }
        if(!found) {
            return false;
        }
    }
    return true;
}

//Antisymmetric R
bool Antisymmetric(relation *R) {
    int anti = 0;
    for (int i = 0; i < R->size; ++i) {
        for (int j = i+1; j < R->size; ++j) {
            if ((strcmp(R->elements[i][0], R->elements[j][1]) == 0) && (strcmp(R->elements[i][1], R->elements[j][0]) == 0)) {
                anti++;
            }
        }
    }
    if(anti > 0) {
        return false;
    } else {
        return true;
    };
}

//Transitive R
bool Transitive(relation *R) {
    for (int i = 0; i < R->size; ++i) {
        for (int j = 1; j < R->size; ++j) {
            if (strcmp(R->elements[i][1], R->elements[j][0]) == 0) {
                for (int k = 0; k < R->size; ++k) {
                    if ((strcmp(R->elements[i][0], R->elements[k][0]) != 0 || strcmp(R->elements[j][1], R->elements[k][1]) != 0) && (j != R->size - 1)) {
                        continue;
                    }
                    else if (strcmp(R->elements[i][0], R->elements[R->size - 1][0]) != 0 || strcmp(R->elements[j][1], R->elements[R->size - 1][1]) != 0) {
                        return false; //when iterate till the end and have not found needed
                    } else {
                        if (strcmp(R->elements[i][0], R->elements[k][0]) == 0 && strcmp(R->elements[j][1], R->elements[k][1]) == 0) {
                            break;
                        }
                    }
                }
            }
        }
    }
    return true;
}

//function R
bool Function(relation *R) {
    int flag = 0;
    for (int i = 0; i < R->size; ++i) {
        for (int j = i+1; j < R->size; ++j) {
            if (strcmp(R->elements[i][0], R->elements[j][0]) == 0) {
                flag++;
            }
        }
    }
    if(flag > 0) {
        return false;
    } else {
        return true;
    }
}

//Domain R
void Domain(relation *R) {
    printf("S %s ", R->elements[0][0]);
    for (int i = 1; i < R->size; ++i) {
        for (int j = 0; j < i; j++) {
            if (strcmp(R->elements[i][0], R->elements[j][0]) != 0 && (j != i - 1)) {
                continue;
            } else if (strcmp(R->elements[i][0], R->elements[j][0]) != 0) {
                printf("%s ", R->elements[i][0]);
            } else if (strcmp(R->elements[i][0], R->elements[j][0]) == 0) {
                break;
            }
        }
    }
}

//codomain R
void Codomain(relation *R) {
    printf("S %s", R->elements[0][1]);
    for (int i = 1; i < R->size; ++i) {
        for (int j = 0; j < i; j++){
            if (strcmp(R->elements[i][1],R->elements[j][1]) != 0 && (j != i - 1)) {
                continue;
            } else if (strcmp(R->elements[i][1],R->elements[j][1]) != 0) {
                printf(" %s", R->elements[i][1]);
            } else if (strcmp(R->elements[i][1],R->elements[j][1]) == 0) {
                break;
            }
        }
    }
    printf("\n");
}

//injective R, A, B
bool Injective(relation *R, set *A, set *B) {
    int aCheck = 0;
    int bCheck = 0;
    int flagB = 0;
    if (Function(R) == 0) {
        return false;
    } else {
        if (A->size != R->size) {
            return false;
        } else {
            for (int i = 0; i < R->size; i++) {
                for (int j = 0; j < A->size; j++) {
                    if (strcmp(R->elements[i][0], A->elements[j]) == 0) {
                        aCheck++;
                    }
                }
            }
            for (int i = 0; i < R->size; i++) {
                for (int j = 0; j < B->size; j++) {
                    if (strcmp(R->elements[i][1], B->elements[j]) == 0) {
                        bCheck++;
                    }
                }
            }
            for (int i = 0; i < R->size; ++i) {
                for (int j = i+1; j < R->size; ++j) {
                    if (strcmp(R->elements[i][1], R->elements[j][1]) == 0) {
                        flagB++;
                    }
                }
            }
            return (aCheck == R->size && bCheck == R->size && flagB == 0);
        }
    }
}

//surjective R, A, B
bool Surjective(relation *R, set *A, set *B) {
    int aCheck = 0;
    int bCheck = 0;
    if (Function(R) == 0) {
        return false;
    } else {
        if (B->size > R->size) {
            return false;
        } else {
            for (int i = 0; i < R->size; i++) {
                for (int j = 0; j < A->size; j++) {
                    if (strcmp(R->elements[i][0], A->elements[j]) == 0) {
                        aCheck++;
                    }
                }
            }
            for (int i = 0; i < R->size; i++) {
                for (int j = 0; j < B->size; j++) {
                    if (strcmp(R->elements[i][1], B->elements[j]) == 0 ) {
                        bCheck++;
                    }
                }
            }
            return (aCheck == R->size && bCheck == R->size);
        }
    }
}

//bijective R A B
bool Bijective(relation *R, set *A, set *B) {
    return (Injective(R, A, B) == 1 && Surjective(R, A, B) == 1);
}

bool FooControl (int *id, char* c) {
    for (int i = 0; i < 19; i++) {
        if (strcmp(COMMAND_LIST[i], c) == 0) {
            *id = i;
            return true;
        }
    }
    return false;
}

bool commandCheck (char* c) {
    for (int i = 0; i < 19; i++) {
        if (strcmp(COMMAND_LIST[i], c) == 0) {
            return true;
        }
    }
    return false;
}

bool containsOnlyLetters(char* source) {
    for (unsigned i = 0; i < strlen(source); i++) {
        if ((source[i] >= 60 && source[i] <= 90) || (source[i] >= 97 && source[i] <= 122)) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

bool isBanned(char* source) {
    char* bannedWords[6] = {"U", "C", "S", "R", "true", "false"};
    for (int i = 0; i < (int)strlen(source); i++) {
        for (int n = 0; n < 6; n++) {
            if(!strcmp(source, bannedWords[n]) || commandCheck(source) || !containsOnlyLetters(source)) {
                return true;
            }
        }
    }
    return false;
}

bool isLetter(char source) {
    return (source >= 60 && source <= 90) || (source >= 97 && source <= 122);
}

bool isDigit(char source) {
    return (source >= 48 && source <= 57);
}

//Fills an array with elements from array source. Divider of elements is space
int fillArray(char*** array, char* source, int elementsCounter) {
    IS_SET_EMPTY

    (*array) = malloc(sizeof *array * elementsCounter);
    for (int i = 0; i < elementsCounter; i++) {
        (*array)[i] = malloc(sizeof **array * 31);
    }

    char element[31];
    int positionInElement = 0;
    int positionInArray = 0;
    int start = 2;  //Position of start, because source[0] is always identificator, source[1] is ' '
    while (!endOfLine(source[start]) && positionInElement <= MAX_LENGTH) {
        element[positionInElement] = source[start];
        element[positionInElement + 1] = '\0';
        positionInElement++;
        if (endOfLine(source[start + 1]) || source[start + 1] == ' ') {
            if ((source[start] == ' ') && (source[start - 1] == ' ' || endOfLine(source[start + 1]))) {
                fprintf(stderr, "You entered wrong line!\n");
                return 0;
            }
            if(isBanned(element)) {
                fprintf(stderr, "Word %s is banned!\n", element);
                return 0;
            }
            for (int i = 0; i < positionInArray; i++) {
                if (!strcmp(element, (*array)[i])) {
                    fprintf(stderr, "Elements in set cannot repeat!\n");
                    return 0;
                }
            }
            strcpy((*array)[positionInArray], element);
            positionInArray++;                         
            clean(element);
            positionInElement = 0;
            if (endOfLine(source[start + 1])) {
                break;
            }
            if (source[start + 1] == ' ') {
                start++;
                if (endOfLine(source[start + 1])) {
                    fprintf(stderr, "You entered wrong line!\n");
                    return 0;
                }
            }
        }
        start++;
    }
    if (positionInElement > MAX_LENGTH) {
        fprintf(stderr, "Max length of element is 30!\n");
        return 0;
    }
    return 1;
}

/*Fills an array with elements from array source. Final array must be an array of binary relations
(every element of final array is the sequence of each of the two elements in brackets from source array)*/
int fillRelation(char**** array, char* source, int relationsCounter) {
    IS_RELATION_EMPTY

    (*array) = malloc(sizeof *array * relationsCounter);
    for(int i = 0; i < relationsCounter; i++) {
        (*array)[i] = malloc(2 * sizeof **array);
        (*array)[i][0] = malloc(31 * sizeof ***array);
        (*array)[i][1] = malloc(31 * sizeof ***array);
    }
    
    char element[31];
    int positionInElement = 0;
    int numberOfBinaryElement = 0;
    int positionInRelation = -1;
    int start = 2;
    int control;
    while (!endOfLine(source[start]) && positionInElement <= MAX_LENGTH) {
        control = 1;
        if (source[start] == '(') {
            positionInRelation++;
            numberOfBinaryElement = 0;
            control = 0;
        } else if (start == 2 && source[start] != '(') {
            fprintf(stderr, "Wrong symbols in relation!\n");
            return 0;
        } else {
            if (source[start] != '(' && source[start] != ')' && source[start] != ' ') {
                element[positionInElement] = source[start];
                element[positionInElement + 1] = '\0';
                positionInElement++;
            }
        }
        if (numberOfBinaryElement > 2) {
            fprintf(stderr, "Max amount of elements in relation is 2!");
            return 0;
        }
        if ((endOfLine(source[start + 1]) || (source[start + 1] == ' ' &&  source[start + 2] != '(')
        || source[start + 1] == ')') && control) {
            strcpy((*array)[positionInRelation][numberOfBinaryElement], element);
            if (numberOfBinaryElement) {
                int repeat = 0;
                char* check[2] = {(*array)[positionInRelation][numberOfBinaryElement-1], (*array)[positionInRelation][numberOfBinaryElement]};
                for (int i = 0; i < positionInRelation; i++) {
                    repeat = 0;
                    for (int n = 0; n < 2; n++) {
                        if(!strcmp((*array)[i][n], check[n])) {
                            repeat++;
                        }
                        if (repeat == 2) {
                            fprintf(stderr, "Binary relations cannot repeat!\n");
                            return 0;
                        }
                    }
                }
            }
            numberOfBinaryElement++;                         
            clean(element);
            positionInElement = 0;
            if (source[start + 1] == ')' && (endOfLine(source[start + 2]))) {
                break;
            }
        }
        start++;
        if (source[start] == ')') {
            if (source[start + 1] != ' ' || endOfLine(source[start + 1])) {
                fprintf(stderr, "Given relation is wrong!\n");
                return 0;
            } else if (source[start + 1] == ' ' && source[start + 2] != '(') {
                fprintf(stderr, "Given relation is wrong!\n");
                return 0;
            }
        }
    }
    if (positionInElement > MAX_LENGTH) {
        fprintf(stderr, "Max length of element is 30!\n");
        return 0;
    }
    return 1;
}

bool isElementOfArray(universe* uni, char** comparable) {
    for (int i = 0; i < uni->size; i++) {
        if(!strcmp(uni->elements[i], *comparable)) {
            return true;
        }
    }
    return false;
}

void cleanArray(char*** array, int size) {
    if (size == 0 && (*array)[0][0] == '\0') {
        free((*array)[0]);
    } else {
        for (int i = 0; i < size; i++) {
            free((*array)[i]);
        }
    }
}

int FooComplite1 (int i, set A, universe U) {
    if (i == 0) {
        return Empty(&A);
    } else if (i == 1) {
        Card(&A);
        return 2;
    } else {
        Complement(&A, &U);
        return 2;
    }
}

int FooComplite2 (int i, set A, set B) {
    if (i == 3) {
        Union(&A, &B);
        return 2;
    } else if (i == 4) {
        Intersect(&A, &B);
        return 2;
    } else if (i == 5) {
        Minus(&A, &B);
        return 2;
    } else if (i == 6) {
        return Subseteq(&A, &B);
    } else if (i == 7) {
        return Subset(&A, &B);
    } else {
        return Equals(&A, &B);
    }
}

int FooComplite3 (int i, relation R, universe U) {
    if (i == 9) {
        return Reflexive(&R, &U);
    } else if (i == 10) {
        return Symmetric(&R);
    } else if (i == 11) {
        return Antisymmetric(&R);
    } else if (i == 12) {
        return Transitive(&R);
    } else if (i == 13) {
        return Function(&R);
    } else if (i == 14) {
        Domain(&R);
        return 2;
    } else {
        Codomain(&R);
        return 2;
    }
}

int FooComplite4 (int i, set A, set B, relation R) {
    if (i == 16) {
        return Injective(&R, &A, &B);
    } else if (i == 17) {
        return Surjective(&R, &A, &B);
    } else {
        return Bijective(&R, &A, &B);
    }
}

int main(int argc, char **argv) {

    (void) argc;

    if (argc > 2 || argc == 1) {
        fprintf(stderr, "Wrong number of arguments!\n");
        return 1;
    }

    FILE* file;
    if ((file = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Cannot open file!\n");
        return 1;
    }
    
    int bufferSymbol;
    char* bufferLine = malloc(1);
    int symbolsCounter = 0;
    int lineCounter = 1;
    universe uni = {.elements = NULL, .size = 0};
    set* sets = malloc(sizeof(set));
    int setCounter = 0;
    relation* relations = malloc(sizeof(relation));
    int relationCounter = 0;
    int setElementsCounter = 0;
    int relationElementsCounter = 0;
    bool err_detector = false;
    int operationsCounter = 0;
    int result = -2;
    int symbolsCounterBuffer = 0;


    while((bufferSymbol = fgetc(file)) != EOF) {
        char* checkBuffer = realloc(bufferLine, (symbolsCounter+2));
        if (checkBuffer == NULL) {
            fprintf(stderr, "Cannot realloc bufferLine!\n");
            err_detector = true;
            break;
        } else {
            bufferLine = checkBuffer;
        }
        if (!endOfLine(bufferSymbol)) {
            bufferLine[symbolsCounter] = (char)bufferSymbol;
            bufferLine[symbolsCounter + 1] = '\0';
            symbolsCounter++;
            if (bufferLine[0] == 'U' || bufferLine[0] == 'S') {
                if (bufferSymbol == ' ') {
                    setElementsCounter++;
                }
            } else if (bufferLine[0] == 'R') {
                if (bufferSymbol == '(') {
                    relationElementsCounter++;
                }
            }
            symbolsCounterBuffer = symbolsCounter;
        } else {
            symbolsCounter = 0;
            if (lineCounter == 1) {
                if (bufferLine[0] == 'U') {
                    if (operationsCounter != 0 || setCounter != 0 || relationCounter != 0) {
                        fprintf(stderr, "Wrong subsequence of lines!\n");
                        err_detector = true;
                        goto err_detected;
                    }

                    if (setElementsCounter == 1 && bufferLine[1] == ' ' && bufferLine[2] == '\0') {
                        setElementsCounter--;
                    }
                    uni.size = setElementsCounter;
                    if (!fillArray(&uni.elements, bufferLine, setElementsCounter)) {
                        fprintf(stderr, "Cannot fill univerzum!\n");
                        err_detector = true;
                    goto err_detected;
                    }
                    setElementsCounter = 0;
                } else {
                    fprintf(stderr, "You didn't set univerzum!\n");
                    err_detector = true;
                    goto err_detected;
                }
            } else if (bufferLine[0] == 'S') {
                if (operationsCounter != 0) {
                    fprintf(stderr, "Wrong subsequence of lines!\n");
                    err_detector = true;
                    goto err_detected;
                }
                
                if (setElementsCounter == 1 && bufferLine[1] == ' ' && bufferLine[2] == '\0') {
                        setElementsCounter--;
                }
                sets[setCounter].size = setElementsCounter;
                if (!fillArray(&sets[setCounter].elements, bufferLine, setElementsCounter)) {
                    setCounter++;
                    err_detector = true;
                    goto err_detected;
                }
                setElementsCounter = 0;
                if (sets[setCounter].size != 0) {
                    for (int i = 0; i < sets[setCounter].size; i++) {
                        if (!isElementOfArray(&uni, &sets[setCounter].elements[i])) {
                            fprintf(stderr, "Element \"%s\" is not in the univerzum!\n", sets[setCounter].elements[i]);
                            setCounter++;
                            err_detector = true;
                            goto err_detected;
                        }
                    }
                }
                
                sets[setCounter].position = lineCounter;
                setCounter++;
                set* checkSets = realloc(sets, sizeof(set) * (setCounter + 1));
                if (checkSets == NULL) {
                    fprintf(stderr, "Cannot realloc sets!\n");
                    err_detector = true;
                    goto err_detected;
                } else {
                    sets = checkSets;
                }
            } else if (bufferLine[0] == 'R') {
                if (operationsCounter != 0) {
                    fprintf(stderr, "Wrong subsequence of lines!\n");
                    err_detector = true;
                    goto err_detected;
                }

                relations[relationCounter].size = relationElementsCounter;
                if (!fillRelation(&relations[relationCounter].elements, bufferLine, relationElementsCounter)) {
                    relationCounter++;
                    err_detector = true;
                    goto err_detected;
                }
                relations[relationCounter].position = lineCounter;
                relationElementsCounter = 0;
                
                if (relations[relationCounter].size != 0) {
                    for (int i = 0; i < relations[relationCounter].size; i++) {
                        for (int n = 0; n < 2; n++) {
                            if (!isElementOfArray(&uni, &relations[relationCounter].elements[i][n])) {
                                fprintf(stderr, "Element \"%s\" is not in the univerzum!\n", relations[relationCounter].elements[i][n]);
                                relationCounter++;
                                err_detector = true;
                                goto err_detected;
                            }
                        }
                    }
                }

                relationCounter++;
                relation* checkRelations = realloc(relations, sizeof(relation) * (relationCounter + 1));
                if (checkRelations == NULL) {
                    fprintf(stderr, "Cannot realloc relations!\n");
                    err_detector = true;
                    goto err_detected;
                } else {
                    relations = checkRelations;
                }
            } else if (bufferLine[0] == 'C' && bufferLine[1] == ' ') {
                if (setCounter == 0 && relationCounter == 0) {
                    fprintf(stderr, "You must have at least one set or relation!\n");
                    err_detector = true;
                    goto err_detected;
                }

                bool control = false;
                int setA = 0, setB = 0, relationR = 0, commandSymbol = 0, symbolsWithoutCSpace = 2, digitCounter = 0, idCommand = 0;
                char command [14];
                operationsCounter++;

                while (!endOfLine(bufferLine[symbolsWithoutCSpace])) {
                    if (symbolsWithoutCSpace == 2 && !isLetter(bufferLine[symbolsWithoutCSpace])) {
                        fprintf(stderr, "Problem1!\n");
                        err_detector = true;
                        goto err_detected;
                    } else {
                        if (isLetter(bufferLine[symbolsWithoutCSpace]) && commandSymbol < 14) {
                            if (control) {
                                fprintf(stderr, "Problem5!\n");
                                err_detector = true;
                                goto err_detected;
                            }
                            command[commandSymbol] = bufferLine[symbolsWithoutCSpace];
                            command[commandSymbol + 1] = '\0';
                            commandSymbol++;
                            symbolsWithoutCSpace++;
                        } else if (commandSymbol >= 14) {
                            fprintf(stderr, "Problem2!\n");
                            err_detector = true;
                            goto err_detected;
                        } else if (bufferLine[symbolsWithoutCSpace] == ' ' && !endOfLine(bufferLine[symbolsWithoutCSpace + 1])) {
                            if (!FooControl(&idCommand, command)) {
                                fprintf(stderr, "Invalid variable: introduced command doesn't exist.");
                                err_detector = true;
                                goto err_detected;
                            } else {
                                control = true;
                                int count = 0;
                                if (isDigit(bufferLine[symbolsWithoutCSpace + 1])) {
                                    digitCounter++;
                                    symbolsWithoutCSpace++;
                                    while (isDigit(bufferLine[symbolsWithoutCSpace])) {
                                        count++;
                                        symbolsWithoutCSpace++;
                                        if (count > 3) {
                                            fprintf(stderr, "Problem4!\n");
                                            err_detector = true;
                                            goto err_detected;
                                        }
                                    }
                                } else if (digitCounter == 0) {
                                    fprintf(stderr, "Problem6!\n");
                                    err_detector = true;
                                    goto err_detected;
                                } else {
                                    fprintf(stderr, "Problem8!\n");
                                    err_detector = true;
                                    goto err_detected;
                                }
                            }
                        } else {
                            fprintf(stderr, "Problem9!\n");
                            err_detector = true;
                            goto err_detected;
                        }
                    }
                }
                if (idCommand < 3 && digitCounter == 1) {
                    if (setCounter < 1) {
                        fprintf(stderr, "Zadny set\n");
                        err_detector = true;
                        goto err_detected;
                    } else {
                        for (int i = 0; i < setCounter; i++) {
                            if (bufferLine[symbolsCounterBuffer - 1] - '0' == 1) {
                                if (bufferLine[symbolsCounterBuffer - 1] - '0' == 1) {
                                    setA = 0;
                                    break;
                                } else if (bufferLine[symbolsCounterBuffer - 1] - '0' == relations[i].position) {
                                    fprintf(stderr, "Musi byt misto relace mnozina\n");
                                    err_detector = true;
                                    goto err_detected;
                                }
                            } else {
                                if (bufferLine[symbolsCounterBuffer - 1] - '0' == sets[i].position) {
                                    setA = i;
                                    break;
                                } else if (bufferLine[symbolsCounterBuffer - 1] - '0' == relations[i].position) {
                                    fprintf(stderr, "Musi byt misto relace mnozina\n");
                                    err_detector = true;
                                    goto err_detected;
                                }
                            }
                        }
                        result = FooComplite1(idCommand, sets[setA], uni);
                    }
                } else if (idCommand >= 3 && idCommand < 9 && digitCounter == 2) {
                    if (setCounter < 1) {
                        fprintf(stderr, "Zadny set\n");
                        err_detector = true;
                        goto err_detected;
                    }
                    for (int i = 0; i < setCounter; i++) {
                        if (bufferLine[symbolsCounterBuffer - 3] - '0' == sets[i].position) {
                            setA = i;
                            break;
                        } else if (bufferLine[symbolsCounterBuffer - 3] - '0' == relations[i].position) {
                            fprintf(stderr, "Musi byt misto relace mnozina\n");
                            err_detector = true;
                            goto err_detected;
                        }
                    }
                    for (int j = 0; j < setCounter; j++) {
                        if (bufferLine[symbolsCounterBuffer - 1] - '0' == sets[j].position) {
                            setB = j;  
                            break;
                        } else if (bufferLine[symbolsCounterBuffer - 1] - '0' == relations[j].position) {
                            fprintf(stderr, "Musi byt misto relace mnozina\n");
                            err_detector = true;
                            goto err_detected;
                        }
                    }
                    result = FooComplite2(idCommand, sets[setA], sets[setB]);
                } else if (idCommand >= 9 && idCommand < 16 && digitCounter == 1) {
                    if (relationCounter < 1) {
                        fprintf(stderr, "Zadna relace\n");
                        err_detector = true;
                        goto err_detected;
                    }
                    for (int k = 0; k < relationCounter; k++) {
                        if (bufferLine[symbolsCounterBuffer - 1] - '0' == relations[k].position) {
                            relationR = k;
                            break;
                        } else if (bufferLine[symbolsCounterBuffer - 1] - '0' == sets[k].position) {
                            fprintf(stderr, "Musi byt misto mnoziny relace\n");
                            err_detector = true;
                            goto err_detected;
                        } else if (bufferLine[symbolsCounterBuffer - 1] - '0' == 1){
                            fprintf(stderr, "Univerzum nesmi byt ve funkce\n");
                            err_detector = true;
                            goto err_detected;
                        }
                    }
                    result = FooComplite3(idCommand, relations[relationR], uni);                
                } else if (idCommand >= 16 && idCommand < 19 && digitCounter == 3) {

                    for (int i = 0; i < setCounter; i++) {
                        if (bufferLine[symbolsCounterBuffer - 3] - '0' == sets[i].position) {
                            setA = i;
                            break;
                        } else if (bufferLine[symbolsCounterBuffer - 3] - '0' == relations[i].position) {
                            fprintf(stderr, "Musi byt misto relace mnozina\n");
                            err_detector = true;
                            goto err_detected;
                        }
                    }

                    for (int j = 0; j < setCounter; j++) {
                        if (bufferLine[symbolsCounterBuffer - 1] - '0' == sets[j].position) {
                            setB = j;
                            break;
                        } else if (bufferLine[symbolsCounterBuffer - 1] - '0' == relations[j].position) {
                            fprintf(stderr, "Musi byt misto relace mnozina\n");
                            err_detector = true;
                            goto err_detected;
                        }
                    }
                    for (int k = 0; k < relationCounter; k++) {
                        if (bufferLine[symbolsCounterBuffer - 5] - '0' == relations[k].position) {
                            relationR = k;
                            break;
                        } else if (bufferLine[symbolsCounterBuffer - 5] - '0' == sets[k].position) {
                            fprintf(stderr, "Musi byt misto mnoziny relace\n");
                            err_detector = true;
                            goto err_detected;
                        }
                    }
                    result = FooComplite4(idCommand, sets[setA], sets[setB], relations[relationR]);
                } else {
                    fprintf(stderr, "Problem7!\n");
                    err_detector = true;
                    goto err_detected;
                }
            } else {
                fprintf(stderr, "Line %d is not correct!\n", lineCounter);
                err_detector = true;
                goto err_detected;
            }
            if (bufferLine[0] != 'C') {
                printf("%s\n", bufferLine);
            }

            if (result == 0) {
                printf("false\n");
            } else if (result == 1) {
                printf("true\n");
            }

            clean(bufferLine);
            lineCounter++;
        }
        if (lineCounter > 1001) {
            fprintf(stderr, "Maximal amount of lines is 1000!\n");
            err_detector = true;
            goto err_detected;
        }
    }

    if(operationsCounter == 0) {
        fprintf(stderr, "You must have at least one operation!\n");
        err_detector = true;
    } else if (setCounter == 0 && relationCounter == 0) {
        if (uni.size == 0) {
            fprintf(stderr, "You cannot have empty file!\n");
            err_detector = true;
        } else {
            fprintf(stderr, "You cannot have only univerzum!\n");
            err_detector = true;
        }
    }

    err_detected: if (err_detector) {
        MEMORY_CLEAN
        return 1;
    }

    MEMORY_CLEAN

    return 0;
}