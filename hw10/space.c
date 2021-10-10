#include "space.h"

tTypeScore scoreBuf[N];

void getScoreSpace(tTypeScore **ppScore) {
    for (int i = 0; i < N; ++i) {
        if (scoreBuf[i].used == 0) {
            printf("\tgetScoreSpace(): giving space numbered[%d] \n", i);
            scoreBuf[i].loc = i;
            scoreBuf[i].used = 1;
            *ppScore = &scoreBuf[i];
            break;
        }
    }
    return;
}

void returnScoreSpace (int loc)
{
    printf("\treturnScoreSpace(): return space numbered %d\n", loc);
}