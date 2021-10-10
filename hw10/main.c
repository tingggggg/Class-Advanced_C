#include "stack.h"

int main() {

    tStack *stack = createStack();
    int choose;

    while (1) {
        printf("\n(1) push or (2) pop a item to/from stack: ");
        scanf("%d", &choose);

        if (choose == 1) {
            pushOperation(stack);
            printStackConetent(stack);
        }
        else if (choose == 2) {
            popOperation(stack);
            printStackConetent(stack);
        }
        else {
            printf("No such option\n");
        }
    }

    return 0;
}