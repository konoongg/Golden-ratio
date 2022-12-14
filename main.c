#include <stdlib.h>
#include <stdio.h>

void PrintFed(int* firstNum, int* secondNum, size_t* firstCount, size_t* secondCount ) {
    for (size_t i = *secondCount; i > 0; --i) {
       printf("%d", secondNum[i - 1]);
    }

    printf("\n");
    for (size_t i = *firstCount; i > 0; --i) {
        printf("%d", firstNum[i-1]);
    }

    printf("\n \n");
}


void PlusMemory(int* firstNum, int* secondNum, size_t* longNum, size_t* firstCount) {
    *longNum += 100;
    firstNum = (int*)realloc(firstNum, sizeof(int) * (*longNum));
    secondNum = (int*)realloc(firstNum, sizeof(int) * (*longNum));
    for (int i = *firstCount; i < *firstCount + 100; ++i) {
        firstNum[i] = 0;
        secondNum[i] = 0;
    }
}


void CheckBorders(int* firstNum, size_t* firstCount,int index) {
    if (firstNum[index] > 9) {
        firstNum[index + 1] += firstNum[index] / 10;
        firstNum[index] %= 10;
        if (*firstCount <= index + 1) {
            //printf("\n  bilo %d  stalo %d index %d\n", *firstCount, (*firstCount) + 1, index + 1);
            ++(*firstCount);
        }

    }
    if (index + 1 > *firstCount && firstNum[index] != 0) {
        ++(*firstCount);
    }
}


void FibPlus(int* firstNum, int* secondNum, size_t* firstCount, size_t* secondCount, size_t* longNum, size_t* countFibNum) {
    if (*secondCount + 10 >= *longNum) {
        PlusMemory(firstNum, secondNum, longNum, firstCount);
    }
    for (size_t i = 0; i < *secondCount; ++i) {
        firstNum[i] += secondNum[i];
        CheckBorders(firstNum, firstCount,i);
    }
}


int Fibonacci(int* firstNum, int*secondNum, size_t* countFibNum, size_t* firstCount, size_t* secondCount, size_t* longNum) {
    if (*countFibNum >= 500000) {
        return 0;
    }
    ++(*countFibNum);
    FibPlus(firstNum, secondNum, firstCount, secondCount, longNum, countFibNum);
    return 1;
}


int NotNull(int* secondNum, size_t index, size_t* secondCount) {
    for (int i = index + 1; i < secondCount; ++i) {
        if (secondNum[i] != 0) {
            return i;
        }
        else {
            secondNum[i] = 9;
        }
    }
}


int WhoMore(int* firstNum, int* secondNum, size_t* firstCount, size_t* secondCount) {
    for (size_t i = *secondCount; i > 0; --i) {
        //printf(" srav s - %d f - %d winner - ", secondNum[i - 1], firstNum[i + 1]);
        if (secondNum[i - 1] > firstNum[ i - 1]) {
           // printf(" second \n");
            return 1;
        }
        else if (secondNum[i - 1] < firstNum[i - 1]) {
            //printf(" first \n");
            return 0;
        }
        //printf("no \n");
    }
    return 1;
}

//secondNum[*secondCount - 1] > firstNum[*firstCount - 1]
void FibMinus(int* firstNum, int* secondNum, size_t* firstCount, size_t* secondCount) {
    int countMinus = 0;
    while (*secondCount > *firstCount || (*secondCount == *firstCount && WhoMore(firstNum, secondNum, firstCount, secondCount) == 1 )) {
       // PrintFed(firstNum, secondNum, firstCount, secondCount);
        for (size_t i = 0; i < *secondCount; ++i) {
            //printf("do %d %d \n", secondNum[i], firstNum[i]);
            if (secondNum[i] >= firstNum[i]) {
                secondNum[i] -= firstNum[i];
            }
            else {
                secondNum[i] += 10 - firstNum[i];
                int index = NotNull(secondNum, i, secondCount);
                secondNum[index] -= 1;
            }
           // printf("posle %d \n", secondNum[i]);
        }
        while (secondNum[*secondCount - 1] == 0) {
            --(*secondCount);
        }
        ++countMinus;
        //printf(" cm %d \n", countMinus);
    }
    printf("%d", countMinus);
}


void FibPow(int* secondNum, size_t* secondCount) {
    ++(*secondCount);
    for (size_t i = *secondCount - 1; i > 0; --i) {
        secondNum[i] = secondNum[i - 1];
    }
    secondNum[0] = 0;
}

void GoldenRatio(int* firstNum, int* secondNum, size_t* firstCount, size_t* secondCount) {
    int counter = 0;
    FibMinus(firstNum, secondNum, firstCount, secondCount);
    printf(".");
    FibPow(secondNum, secondCount);
    while (counter < 10000) {
        FibMinus(firstNum, secondNum, firstCount, secondCount);
        FibPow(secondNum, secondCount);
        ++counter;
    }
}


int main() {
    size_t longNum = 120000;
    int* firstNum = (int*)calloc(longNum,sizeof(int));
    int* secondNum = (int*)calloc(longNum, sizeof(int));
    size_t firstCount = 1;
    size_t secondCount = 1;
    size_t countFibNum = 2;
    int checkEndFib = 1;
    firstNum[0] = 1;
    secondNum[0] = 1;
    int minNum = 0;

    
    while (checkEndFib != 0) {
        if (minNum == 0) {
            checkEndFib = Fibonacci(firstNum, secondNum, &countFibNum, &firstCount, &secondCount, &longNum);
            minNum = 1;
        }
        else {
            checkEndFib = Fibonacci(secondNum, firstNum, &countFibNum, &secondCount, &firstCount, &longNum);
            minNum = 0;
        }
    }
    GoldenRatio(firstNum, secondNum, &firstCount, &secondCount);
    return 0;
}