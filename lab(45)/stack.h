
#define MAX_EXPR_LEN 256
#define MAX_STACK_SIZE 1000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
// Структуры данных
typedef struct {
    int *data;
    int top;
    int capacity;
} IntStack;


// Общие функции для стеков
int correct_choice(int task);

void initIntStack(IntStack *s, int capacity) {
    s->data = (int*)malloc(capacity * sizeof(int));
    if (!s->data) exit(1);
    s->top = -1;
    s->capacity = capacity;
}


bool isIntStackFull(IntStack *s) { return s->top == s->capacity - 1; }
bool isIntStackEmpty(IntStack *s) { return s->top == -1; }

void pushInt(IntStack *s, int value) {
    if (isIntStackFull(s)) return;
    s->data[++s->top] = value;
}

int popInt(IntStack *s) {
    if (isIntStackEmpty(s)) return -1;
    return s->data[s->top--];
}

int peekInt(IntStack *s) {
    if (isIntStackEmpty(s)) return -1;
    return s->data[s->top];
}


void freeIntStack(IntStack *s) {
    free(s->data);
    s->top = -1;
    s->capacity = 0;
}




int strcmp(const char *s1, const char *s2) {
    if (s1 == NULL && s2 == NULL) return 0;
    if (s1 == NULL) return -1; // NULL считается меньше любой строки
    if (s2 == NULL) return 1;  // Любая строка считается больше NULL

    // Идем по строкам, пока символы совпадают и не достигнут конец одной из строк
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    // Возвращаем разницу кодов первых несовпадающих символов (или 0, если строки равны).
    // Важно использовать unsigned char для корректного сравнения кодов > 127.
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}


// Задание 1
int findSumAfterMin(IntStack *s) {
    if (isIntStackEmpty(s)) {
        printf("Стек пуст!\n");
        return 0;
    }

    int min_val = s->data[0];
    int min_pos = 0;

    for (int i = 1; i <= s->top; i++) {
        if (s->data[i] < min_val) {
            min_val = s->data[i];
            min_pos = i;
        }
    }

    if (min_pos == s->top) return 0;

    int sum = 0;
    for (int i = min_pos + 1; i <= s->top; i++) {
        sum += s->data[i];
    }

    return sum;
}

// Задание 2
void fillStack(IntStack *s, int capacity, const char *order) {
    int value;
    for (int i = 0; i < capacity; i++) {
        printf("Введите элемент %d: ", i + 1);
        value = correct_choice(value);

        if (strcmp(order, "desc") == 0) {
            // Проверка возрастающего порядка
            if (i > 0 && value <= peekInt(s)) {
                printf("Ошибка: элементы должны быть в строго возрастающем порядке!\n");
                i--;
                continue;
            }
        } else if (strcmp(order, "asc") == 0) {
            // Проверка возрастающего порядка
            if (i > 0 && value <= peekInt(s)) {
                printf("Ошибка: элементы должны быть в строго возрастающем порядке!\n");
                i--;
                continue;
            }
        }
        pushInt(s, value);
    }
}

void mergeStacks(IntStack *s1, IntStack *s2, IntStack *result) {


    while (!isIntStackEmpty(s2) && !isIntStackEmpty(s1)) {
        int peek1 = peekInt(s2);
        int peekAux = peekInt(s1);

        if (peek1 >= peekAux) {
            pushInt(result, popInt(s2)); // Берем меньший из s1
        } else {
            pushInt(result, popInt(s1)); // Берем меньший из auxStack
        }
    }
    while (!isIntStackEmpty(s2)) {
        pushInt(result, popInt(s2));
    }
    while (!isIntStackEmpty(s1)) {
        pushInt(result, popInt(s1));
    }


}

// Функция для проверки корректности ввода
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

typedef struct {
    double data[MAX_STACK_SIZE];
    int top;
} DoubleStack;

void pushD(DoubleStack* s, double val) { s->data[++s->top] = val; }
double popD(DoubleStack* s) { return s->data[s->top--]; }


int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : NAN;
        default: return NAN;
    }
}

int evaluateExpression(const char* expr, double* result, int* errorPos) {
    DoubleStack values = {.top = -1};
    char ops[MAX_STACK_SIZE];
    int opsTop = -1;

    int i = 0;
    while (expr[i]) {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        if (isdigit(expr[i]) || expr[i] == '.') {
            char number[64];
            int idx = 0;
            while (isdigit(expr[i]) || expr[i] == '.') {
                number[idx++] = expr[i++];
            }
            number[idx] = '\0';
            pushD(&values, atof(number));
            continue;
        }

        if (expr[i] == '(') {
            ops[++opsTop] = expr[i];
        } else if (expr[i] == ')') {
            while (opsTop >= 0 && ops[opsTop] != '(') {
                if (values.top < 1) {
                    *errorPos = i;
                    return 0;
                }
                double b = popD(&values), a = popD(&values);
                char op = ops[opsTop--];
                if (op == '/' && b == 0) {
                    *errorPos = i;
                    return 0;
                }
                pushD(&values, applyOp(a, b, op));
            }
            if (opsTop < 0 || ops[opsTop] != '(') {
                *errorPos = i;
                return 0;
            }
            opsTop--; // убираем '('
        } else if (strchr("+-*/", expr[i])) {
            while (opsTop >= 0 && precedence(ops[opsTop]) >= precedence(expr[i])) {
                if (values.top < 1) {
                    *errorPos = i;
                    return 0;
                }
                double b = popD(&values), a = popD(&values);
                char op = ops[opsTop--];
                if (op == '/' && b == 0) {
                    *errorPos = i;
                    return 0;
                }
                pushD(&values, applyOp(a, b, op));
            }
            ops[++opsTop] = expr[i];
        } else {
            *errorPos = i;
            return 0;
        }
        i++;
    }

    while (opsTop >= 0) {
        if (values.top < 1) {
            *errorPos = i;
            return 0;
        }
        double b = popD(&values), a = popD(&values);
        char op = ops[opsTop--];
        if (op == '/' && b == 0) {
            *errorPos = i;
            return 0;
        }
        pushD(&values, applyOp(a, b, op));
    }

    if (values.top != 0) {
        *errorPos = i;
        return 0;
    }

    *result = popD(&values);
    return 1;
}
