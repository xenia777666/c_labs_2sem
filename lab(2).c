#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void fillFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Не удалось открыть файл");
        return;
    }

    int num;
    printf("Введите числа (отрицательное число для завершения):\n");
    while (true) {
        if (scanf("%d", &num) != 1) {
            printf("Ошибка ввода. Пожалуйста, введите целое число.\n");
            while (getchar() != '\n');
            continue;
        }
        if (num < 0) break;
        fprintf(file, "%d\n", num);
    }
    fclose(file);
}

void readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Не удалось открыть файл");
        return;
    }

    int num;
    printf("Содержимое файла:\n");
    while (fscanf(file, "%d", &num) != EOF) {
        printf("%d\n", num);
    }
    fclose(file);
}

void findMaxInFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Не удалось открыть файл");
        return;
    }

    int num, max = -1;
    int count = 0;
    int *maxNumbers = malloc(100 * sizeof(int)); //массив для хранения макс чисел

    while (fscanf(file, "%d", &num) != EOF) {
        if (num > max) {
            max = num;
            count = 0; //сбрас счетчик
            maxNumbers[count++] = num; //добавляем нов макс
        } else if (num == max) {
            maxNumbers[count++] = num; // добавляем еще одно макс
        }
    }

    if (count > 0) {
        printf("Максимальное число: %d\n", max);
        printf("Все максимальные числа:\n");
        for (int i = 0; i < count; i++) {
            printf("%d\n", maxNumbers[i]);
        }
    } else {
        printf("Файл пуст.\n");
    }

    free(maxNumbers);
    fclose(file);
}

void reverseNumber(const char *filename, int index) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        perror("Не удалось открыть файл");
        return;
    }

    int num;
    int currentIndex = 0;
    long position;

    while (fscanf(file, "%d", &num) != EOF) {
        if (currentIndex == index) {
            position = ftell(file); // сохраняем позицию
            fseek(file, position - (long)sizeof(num), SEEK_SET); // возвращаемся на размер числа назад

            // переворачиваем число
            int reversed = 0;
            int temp = num; // временная переменная для переворота
            while (temp > 0) {
                reversed = reversed * 10 + temp % 10;
                temp /= 10;
            }
            fprintf(file, "%d\n", reversed);
            break;
        }
        currentIndex++;
    }

    fclose(file);
};



int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    fillFile(filename);
    readFile(filename);
    findMaxInFile(filename);

    int index;
    printf("Введите номер числа для переворота: ");
    while (true) {
        if (scanf("%d", &index) != 1) { // Проверка ввода
            printf("Ошибка ввода. Пожалуйста, введите целое число.\n");
            while (getchar() != '\n'); // Очистка буфера
            continue;
        };

        reverseNumber(filename, index-1);

        printf("Обновленное содержимое файла:\n");
        readFile(filename);
        return 0;
    }
}

//   gcc "lab(2).c" -o lab2
//  ./lab2 data.txt