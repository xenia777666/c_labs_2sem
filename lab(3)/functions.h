#include <ctype.h>
typedef struct {
    char startDate[11];; // Дата приема (строка фиксированной длины)
} StartDate;


typedef struct {
    int sum;       // Оклад
    char *name;
    StartDate startDate;        // Дата приема (вложенная структура)
    int cipher;
} Workers;



int correct_choice(int task);
void print_two_oldest_bits();
void input_workers(Workers *workers);
void print_workers(const Workers *workers);
void find_workers_by_name(Workers *workers, int count, const char *name);
void delete_workers_by_sum(Workers *workers, int *count, int min_sum);
int isValidDateFormat(const char* startDate);
void task_with_two_oldest_bits();
void task_about_workers();
void start();
int main();


int correct_choice(int task) {
    while (1) {
        char b;
        if (scanf("%d%c", &task, &b) == 2 && b == '\n') {
            break;
        } else {
            printf("Некорректный ввод. Повторите еще раз: ");
            while (getchar() != '\n');
        }
    }
    return task;
}


void print_two_oldest_bits() {
    int num;
    printf("Введите число: ");
    num = correct_choice(num);
    struct BitField {
        unsigned int high_bit : 1;   // Старший бит
        unsigned int second_bit : 1; // Второй старший бит
        unsigned int reserved : 30;   // Остальные 30 бит (неиспользуемые)
    };

    struct BitField bits;
    unsigned int high_bits = num >> (sizeof(num) * 8 - 2);

    // Заполняем битовое поле
    bits.high_bit = (high_bits & 2) >> 1; // Старший бит
    bits.second_bit = high_bits & 1;      // Второй старший бит

    printf("Два старших бита: %d%d\n", bits.high_bit, bits.second_bit);
}



void input_workers(Workers *workers) {
    printf("Введите оклад сотрудника: ");
    (*workers).sum = correct_choice((*workers).sum);

    printf("Введите фамилию сотрудника: ");
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Удаление символа новой строки
    workers->name = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
    if (workers->name == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    strcpy(workers->name, buffer);

    printf("Введите дату приема на работу: ");
    fgets(workers->startDate.startDate, sizeof(workers->startDate.startDate), stdin);
    if (isValidDateFormat(workers->startDate.startDate)) {
    }
    else {
        printf("Неверный формат, введите DD.MM.YYYY.\n");
    }
    workers->startDate.startDate[strcspn(workers->startDate.startDate, "\n")] = '\0'; // Удаление символа новой строки
    printf("Введите шифр отдела: ");
    workers->cipher = correct_choice(workers->cipher);
}

int isValidDateFormat(const char* startDate) {
    if (strlen(startDate) != 10) return 0;
    if (startDate[2] != '.' || startDate[5] != '.') return 0;
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(startDate[i])) return 0;
    }
    return 1;
}

void print_workers(const Workers *workers) {
    printf("Фамилия: %s\n", workers->name);
    printf("Оклад: %d\n", workers->sum);
    printf("Дату приема на работу: %s\n", workers->startDate.startDate);
    printf("Шифр отдела: %d\n", workers->cipher);
}


void find_workers_by_name(Workers *workers, int count, const char *name) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(workers[i].name, name) == 0) {
            printf("Найден сотрудник:\n");
            print_workers(&workers[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Сотрудники с фамилией '%s' не найдены.\n", name);
    }
}


void delete_workers_by_sum(Workers *workers, int *count, int min_sum) {
    int deleted = 0;
    for (int i = 0; i < *count; i++) {
        if (workers[i].sum < min_sum) {
            free(workers[i].name); // Освобождаем память, выделенную под название
            for (int j = i; j < *count - 1; j++) {
                workers[j] = workers[j + 1];
            }
            (*count)--;
            i--;
            deleted++;
        }
    }
    printf("Удалено %d сотрудников.\n", deleted);
}

void task_with_two_oldest_bits() {
    print_two_oldest_bits();
}

void task_about_workers() {
    int count;
    printf("Введите количество сотрудников: ");
    count = correct_choice(count);

    Workers *workers = (Workers *)malloc(count * sizeof(Workers));
    if (workers == NULL) {
        printf("Ошибка выделения памяти!\n");
        return;
    }


    for (int i = 0; i < count; i++) {
        printf("\nВвод данных сотрудника %d:\n", i + 1);
        input_workers(&workers[i]);
    }


    int action;
    while (action != 4){
        printf("\nМеню:\n");
        printf("1. Вывести всех сотрудников\n");
        printf("2. Найти сотрудника по фамилии\n");
        printf("3. Удалить сотрудника с окладом меньше заданного\n");
        printf("4. Выйти\n");
        printf("Выберите действие: ");
        action = correct_choice(action);

        switch (action) {
            case 1: {
                for (int i = 0; i < count; i++) {
                    printf("\nДанные о сотруднике %d:\n", i + 1);
                    print_workers(&workers[i]);
                }
                break;
            }
            case 2: {
                char name[100];
                printf("Введите фамилию сотрудника для поиска: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; // Удаление символа новой строки
                find_workers_by_name(workers, count, name);
                break;
            }
            case 3: {
                int min_sum;
                printf("Введите минимальный оклад для удаления: ");
                min_sum = correct_choice(min_sum);
                delete_workers_by_sum(workers, &count, min_sum);
                break;
            }
            case 4: {
                printf("Выход из программы.\n");
                break;
            }
            default: {
                printf("Неверный выбор. Попробуйте снова.\n");
                break;
            }
        }
    };

    // Освобождение памяти
    for (int i = 0; i < count; i++) {
        free(workers[i].name);
    }
    free(workers);
}
