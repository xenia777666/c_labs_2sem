#include <stdio.h>
#include <stdlib.h>

void swap_min_max(const char *filename);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <имя_файла>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    FILE *file;
    int number;
    int min = 11, max = -1;
    int sum = 0, count = 0;

    file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return EXIT_FAILURE;
    }

    printf("Введите целые числа от 0 до 10 (введите -1 для выхода):\n");
    while (1) {
        scanf("%d", &number);
        if (number == -1) {
            break;
        }
        if (number < 0 || number > 10) {
            printf("Введите число в диапазоне от 0 до 10.\n");
            continue;
        }
        fwrite(&number, sizeof(int), 1, file);

        // Обновление минимального и максимального значений
        if (number < min) min = number;
        if (number > max) max = number;
    }

    fclose(file);

    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return EXIT_FAILURE;
    }

    while (fread(&number, sizeof(int), 1, file) == 1) {
        if (number == min || number == max) {
            if (number == min) {
                min = -1; // удаляем только один экземпляр
            } else if (number == max) {
                max = -1;
            }
            continue;
        }
        sum += number;
        count++;
    }

    fclose(file);

    if (count > 0) {
        printf("Среднее арифметическое оставшихся чисел: %.2f\n", (double)sum / count);
    } else {
        printf("Нет оставшихся чисел для вычисления среднего арифметического.\n");
    }

    swap_min_max(filename);
    return EXIT_SUCCESS;
}

void swap_min_max(const char *filename) {
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return;
    }

    int number;
    int min = 11, max = -1;
    int min_position = -1, max_position = -1;
    int current_position = 0;

    // Поиск минимального и максимального значений
    while (fread(&number, sizeof(int), 1, file) == 1) {
        if (number < min) {
            min = number;
            min_position = current_position;
        }
        if (number > max) {
            max = number;
            max_position = current_position;
        }
        current_position += sizeof(int);
    }

    if (min_position == -1 || max_position == -1) {
        printf("Не найдены минимальные или максимальные значения.\n");
        fclose(file);
        return;
    }

    // Меняем местами мин и макс
    fseek(file, min_position, SEEK_SET);
    fread(&number, sizeof(int), 1, file);
    int temp_min = number;

    fseek(file, max_position, SEEK_SET);
    fread(&number, sizeof(int), 1, file);
    int temp_max = number;

    // Записываем обратно
    fseek(file, min_position, SEEK_SET);
    fwrite(&temp_max, sizeof(int), 1, file);

    fseek(file, max_position, SEEK_SET);
    fwrite(&temp_min, sizeof(int), 1, file);

    fclose(file);
    printf("Минимальное и максимальное значения успешно поменяны местами.\n");

    // Вывод содержимого файла
    file = fopen(filename, "rb");
    while (fread(&number, sizeof(int), 1, file) == 1) {
        printf("%d ", number);
    }
    printf("\n");

    fclose(file);
}
//   gcc "lab(1).c" -o lab1
//  ./lab1 data.bin
