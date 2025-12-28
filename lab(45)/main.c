/*
Задание:
 1. Создать стек для целых чисел. Максимальный размер стека вводится с экрана. Найти сумму до минимального элемента стека.
 2. Создать два стека для целых чисел. Первый стек – организовать ввод по убыванию, второй cтек – организовать ввод по возрастанию. Без сортировок и переворачивания исходных стеков сформировать третий стек упорядоченный по убыванию

Студент: Кошель Ксения
Дата: 25.04.2025
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "stack.h"
#include <string.h>


#define MAX_SIZE 100
#define MAX_EXPR_LEN 256



void task1() {
    printf("\nЗадание 1\n");
    int capacity;
    printf("Введите размер стека: ");
    capacity = correct_choice(capacity);

    IntStack s;
    initIntStack(&s, capacity);

    printf("Введите элементы стека (целые числа):\n");
    for (int i = 0; i < capacity; i++) {
        int num;
        num = correct_choice(num);
        pushInt(&s, num);
    }

    int sum = findSumAfterMin(&s);
    printf("Сумма элементов до минимального: %d\n", sum);

    freeIntStack(&s);
}


void task2() {
    printf("\nЗадание 2\n");
    int capacity;
    printf("Введите размер стеков: ");
    scanf("%d", &capacity);

    IntStack s1, s2, s3;
    initIntStack(&s1, capacity);
    initIntStack(&s2, capacity);
    initIntStack(&s3, capacity * 2);

    printf("\nЗаполните первый стек (СТРОГО ВОЗРАСТАЮЩИЙ ПОРЯДОК):\n");
    fillStack(&s1, capacity, "desc");

    printf("\nЗаполните второй стек (СТРОГО ВОЗРАСТАЮЩИЙ ПОРЯДОК):\n");
    fillStack(&s2, capacity, "asc");

    mergeStacks(&s1, &s2, &s3);

    printf("\nРезультат (по возрастанию): \n");
    while (!isIntStackEmpty(&s3)) {
        printf("%d ", popInt(&s3));
    }
    printf("\n");

    freeIntStack(&s1);
    freeIntStack(&s2);
    freeIntStack(&s3);
}

void task3() {
    FILE* fin = fopen("input.txt", "r");
    FILE* fout = fopen("output.txt", "w");

    if (!fin || !fout) {
        printf("Ошибка открытия файлов.\n");
        return;
    }

    char line[MAX_EXPR_LEN];
    int lineNum = 1;

    fprintf(fout, "// Задание 3: Вычисление выражений из файла\n");
    fprintf(fout, "// Выполнил: Фамилия И.О. | Дата: 29.04.2025\n\n");

    while (fgets(line, sizeof(line), fin)) {
        // удаляем \n
        line[strcspn(line, "\n")] = '\0';

        double result;
        int errorPos = -1;

        if (strlen(line) == 0) {
            lineNum++;
            continue;
        }

        if (evaluateExpression(line, &result, &errorPos)) {
            fprintf(fout, "Результат строки %d: %.2lf\n", lineNum, result);
        } else {
            fprintf(fout, "Ошибка в строке %d, позиция %d: %s\n", lineNum, errorPos + 1, line);
        }

        lineNum++;
    }

    fclose(fin);
    fclose(fout);
    printf("Результаты записаны в output.txt\n");
}


int main() {
    int choice;
    do {
        printf("\n=================== Меню ===================\n");
        printf("1| Задание 1 (Сумма до минимума в стеке)\n");
        printf("2| Задание 2 (Объединение двух стеков)\n");
        printf("3| Задание 3 \n");
        printf("4| Выход\n");
        printf("Выберите задание: ");
        choice = correct_choice(choice);

        switch (choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: printf("Выход...\n"); break;
            default: printf("Неверный выбор!\n");
        }
    } while (choice != 3);

    return 0;
}

//   gcc "main.c" -o lab4
//  ./lab4
