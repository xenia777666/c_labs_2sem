#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


void start() {
    int task;
    printf("Выберите задание для проверки: ");
    task = correct_choice(task);

    while (1) {
        if (task == 1) {
            task_with_two_oldest_bits();
            break;
        } else if (task == 2) {
            task_about_workers();
            break;
        } else {
            printf("Неверный номер задания. Попробуйте еще раз: ");
            task = correct_choice(task);
        }
    }
}

int main() {
    int n = 2;
    while (1) {
        if (n == 2) {
            start();
            printf("\nЗакрыть программу?\n");
            printf("1-Да\n2-Нет\n");
            n = correct_choice(n);
        }
        if (n == 1) {
            return 0;
        }
        if (n == 2) {
            continue;
        } else {
            printf("Данного варианта ответа не существует. Повторите ввод: ");
            n = correct_choice(n);
        }
    }

    return 0;
}
