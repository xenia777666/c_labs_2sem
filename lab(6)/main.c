// main.c
#include <stdio.h>
#include "functions.c"

int main() {
    int choice, size, num;
    Queue q;
    Deque d;

    do {
        printf("\nМеню:\n");
        printf("1. Очередь (только отрицательные числа)\n");
        printf("2. Дек (только отрицательные числа)\n");
        printf("3. Анализ строки\n");
        printf("0. Выход\n");
        printf("Выберите вариант: ");
        choice = getIntInput();

        switch (choice) {
            case 1:
                printf("Введите максимальный размер очереди: ");
                size = getIntInput();
                initQueue(&q, size);
                for (int i = 0; i < 6; i++) {
                    printf("Введите число: ");
                    num = getIntInput();
                    enqueue(&q, num);
                }
                printf("Содержимое очереди:\n");
                displayQueue(&q);
                break;

            case 2:
                printf("Введите максимальный размер дека: ");
                size = getIntInput();
                initDeque(&d, size);
                for (int i = 0; i < 3; i++) {
                    printf("Введите число для добавления справа: ");
                    num = getIntInput();
                    enqueueRight(&d, num);
                }
                for (int i = 0; i < 3; i++) {
                    printf("Введите число для добавления слева: ");
                    num = getIntInput();
                    enqueueLeft(&d, num);
                }
                printf("Содержимое дека:\n");
                displayDeque(&d);
                break;

            case 3:
                processString();
                break;

            case 0:
                printf("Выход из программы.\n");
                break;

            default:
                printf("Некорректный выбор! Попробуйте снова.\n");
        }
    } while (choice != 0);

    return 0;
}