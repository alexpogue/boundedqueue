// Copyright [2014] Alex Pogue

#include <stdio.h>
#include <string.h>
#include "BoundedQueue.h"

int promptSize(int* size);
int promptInt(int* output);
int stringToInt(char* str, int* output);
int promptString(char* str, int size);
void printQueue(const BoundedQueue& q);

int main(void) {
    int size;
    int validInput = 0;

    printf("BoundedQueue:\n\n");

    while (!validInput) {
        printf("Enter desired queue size: ");

        validInput = promptSize(&size);
        if (!validInput) {
            printf("invalid size\n");
        }
    }

    BoundedQueue bq(size);

    char cmd[3]; /* to hold "x\n\0" where x = command letter */
    while (cmd[0] != 'q') {
        printf("Enter command - (e)nqueue, (d)equeue, or (q)uit: ");
        validInput = promptString(cmd, 3);
        if (!validInput) {
            printf("invalid\n");
            continue;
        }
        int element;
        if (cmd[0] == 'e') {
            printf("Enter integer to enqueue: ");
            promptInt(&element);
            bq.enqueue(element);
            if (size <= 25) {
                printQueue(bq);
                printf("\n");
            }
        }
        else if (cmd[0] == 'd') {
            printf("Dequeued integer: %d\n", bq.dequeue());
            if (size <= 25) {
                printQueue(bq);
                printf("\n");
            }
        }
    }


    return 0;
}

int promptSize(int* size) {
    int success = promptInt(size);
    if (*size < 0) {
        success = 0;
    }

    return success;
}

int promptInt(int* output) {
    char str[13];
    if (!promptString(str, 13) || !stringToInt(str, output)) {
        return 0;
    }
    return 1;
}

int stringToInt(char* str, int* output) {
    int res;
    int numChars;
    int numTokens = sscanf(str, "%d%n", &res, &numChars);

    int convertSuccess = numTokens > 0 && numTokens != EOF;
    int validInput = numChars > 0 && str[numChars] == '\0';
    if (!convertSuccess || !validInput) {
        return 0;
    }

    *output = res;
    return 1;
}

int promptString(char* str, int size) {
    // inspired by Allan Chandler: http://powerfield-software.com/?p=65
    size_t len;
    int ch;

    if (fgets(str, size, stdin) == NULL) {
        // read only eof or error occurred
        return 0;
    }

    len = strlen(str);
    if (str[len-1] != '\n') {
        while ((ch = getchar()) != '\n') {
            if (ch == EOF) break;
        }
    }
    else {
        str[len-1] = '\0';
    }

    return 1;
}

void printQueue(const BoundedQueue& q) {
    BoundedQueue qCopy(q);
    int numElements = qCopy.getSize();
    int numEmpty = qCopy.getCapacity() - numElements;
    printf("|");
    while (--numElements >= 0) {
        printf("%d|", qCopy.dequeue());
    }
    while (--numEmpty >= 0) {
        printf(" |");
    }
    printf("\n");
}
