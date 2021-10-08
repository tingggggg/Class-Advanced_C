#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int binToDec(char *input);
int hexToDec(char *input);
int getIntOfSymbol(char ch);


int main() {
    char input[15];
    int type;
    while (1) {
        printf("Input Number ('b' or 'h' be head): ");
        scanf("%s", &input);

        if (input[0] == 'b' || input[0] == 'h') {
            type = input[0] == 'b' ? 0 : 1;
            int (*func[2])(char* input) = {binToDec, hexToDec};
            printf("Result: %d \n", func[type](input));
        }
        else {
            printf("No such option! \n");
        }
    }
    return 0;
}

int binToDec(char *input) {
    long fact = 1;
    int len = strlen(input);
    int sum = 0;

    for (int i = len - 1; i > 0; --i) {
        sum += fact * getIntOfSymbol(input[i]);
        fact <<= 1;
    }
    return sum;
}

int hexToDec(char *input) {
    long fact = 1;
    int len = strlen(input);
    int sum = 0;
    for (int i = len - 1; i > 0; --i) {
        sum += fact * getIntOfSymbol(input[i]);
        fact <<= 4;
    }
    return sum;
}

int getIntOfSymbol(char ch) {
    if (ch <= '9' && ch >= '0') {
        return ch - '0';
    }
    if (ch >= 'a' && ch <= 'z') {
        return ch - 'a' + 10;
    }
    if (ch >= 'A' && ch <= 'Z') {
        return ch - 'A' + 10;
    }
    return -1;
}