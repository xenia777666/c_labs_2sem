// functions.c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100


typedef struct {
    int data[MAX_SIZE];
    int front, rear;
    int max_size;
} Queue;


typedef struct {
    int data[MAX_SIZE];
    int front, rear;
    int max_size;
} Deque;


typedef struct {
    char *data[MAX_SIZE];
    int front, rear;
    int max_size;
} StringQueue;


int getIntInput();
void initQueue(Queue *q, int size);
int isEmpty(Queue *q);
int isFull(Queue *q);
void enqueue(Queue *q, int value);
void displayQueue(Queue *q);
void initDeque(Deque *d, int size);
int isEmptyDeque(Deque *d);
int isFullDeque(Deque *d);
void enqueueRight(Deque *d, int value);
void enqueueLeft(Deque *d, int value);
void displayDeque(Deque *d);
void initStringQueue(StringQueue *q, int size);
int isEmptyStringQueue(StringQueue *q);
int isFullStringQueue(StringQueue *q);
void enqueueString(StringQueue *q, char *word);
void displayStringQueue(StringQueue *q);
void processString();


int getIntInput() {
    int value;
    while (scanf("%d", &value) != 1) {
        printf("Ошибка ввода. Пожалуйста, введите целое число: ");
        while (getchar() != '\n'); // Очистка буфера
    }
    return value;
}

void initQueue(Queue *q, int size) {
    q->front = -1;
    q->rear = -1;
    q->max_size = size;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int isFull(Queue *q) {
    return (q->rear + 1) % q->max_size == q->front;
}

void enqueue(Queue *q, int value) {
    if (value >= 0) {
        printf("Только отрицательные числа могут быть добавлены!\n");
        return;
    }
    if (isFull(q)) {
        printf("Очередь переполнена!\n");
        return;
    }
    if (isEmpty(q)) q->front = 0;
    q->rear = (q->rear + 1) % q->max_size;
    q->data[q->rear] = value;
}

void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Очередь пуста!\n");
        return;
    }
    int i = q->front;
    while (i != q->rear) {
        printf("%d ", q->data[i]);
        i = (i + 1) % q->max_size;
    }
    printf("%d\n", q->data[q->rear]);
}

void initDeque(Deque *d, int size) {
    d->front = -1;
    d->rear = -1;
    d->max_size = size;
}

int isEmptyDeque(Deque *d) {
    return d->front == -1;
}

int isFullDeque(Deque *d) {
    return (d->rear + 1) % d->max_size == d->front;
}

void enqueueRight(Deque *d, int value) {
    if (value >= 0) {
        printf("Только отрицательные числа могут быть добавлены!\n");
        return;
    }
    if (isFullDeque(d)) {
        printf("Дек переполнен!\n");
        return;
    }
    if (isEmptyDeque(d)) d->front = 0;
    d->rear = (d->rear + 1) % d->max_size;
    d->data[d->rear] = value;
}

void enqueueLeft(Deque *d, int value) {
    if (value >= 0) {
        printf("Только отрицательные числа могут быть добавлены!\n");
        return;
    }
    if (isFullDeque(d)) {
        printf("Дек переполнен!\n");
        return;
    }
    if (isEmptyDeque(d)) {
        d->front = 0;
        d->rear = 0;
    } else {
        d->front = (d->front - 1 + d->max_size) % d->max_size;
    }
    d->data[d->front] = value;
}

void displayDeque(Deque *d) {
    if (isEmptyDeque(d)) {
        printf("Дек пуст!\n");
        return;
    }
    int i = d->front;
    while (i != d->rear) {
        printf("%d ", d->data[i]);
        i = (i + 1) % d->max_size;
    }
    printf("%d\n", d->data[d->rear]);
}

void initStringQueue(StringQueue *q, int size) {
    q->front = -1;
    q->rear = -1;
    q->max_size = size;
}

int isEmptyStringQueue(StringQueue *q) {
    return q->front == -1;
}

int isFullStringQueue(StringQueue *q) {
    return (q->rear + 1) % q->max_size == q->front;
}

void enqueueString(StringQueue *q, char *word) {
    if (isFullStringQueue(q)) {
        printf("Очередь переполнена!\n");
        return;
    }
    if (isEmptyStringQueue(q)) q->front = 0;
    q->rear = (q->rear + 1) % q->max_size;
    q->data[q->rear] = strdup(word);  // Копируем слово в очередь
}

void displayStringQueue(StringQueue *q) {
    if (isEmptyStringQueue(q)) {
        printf("Очередь пуста!\n");
        return;
    }
    int i = q->front;
    while (i != q->rear) {
        printf("%s\n", q->data[i]);
        i = (i + 1) % q->max_size;
    }
    printf("%s\n", q->data[q->rear]);
}

void processString() {
    char str[256];
    StringQueue q;
    initStringQueue(&q, MAX_SIZE);
    printf("Введите строку: ");
    getchar();
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;
    char *word = strtok(str, " ");
    while (word) {
        if (isupper(word[0])) {
            enqueueString(&q, word);
        }
        word = strtok(NULL, " ");
    }
    printf("Слова с заглавной буквы в очереди:\n");
    displayStringQueue(&q);
    printf("Количество элементов в очереди: %d\n", (q.rear - q.front +1) % q.max_size);
}