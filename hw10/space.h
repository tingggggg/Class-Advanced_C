#include<stdio.h>
#include<stdlib.h>
#define N 5

typedef struct Score {
    int score;
    int loc;
    int used;
} tTypeScore;

void getScoreSpace(tTypeScore **ppScore);

void returnScoreSpace(int location);
