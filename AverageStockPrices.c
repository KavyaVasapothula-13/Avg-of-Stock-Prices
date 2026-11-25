#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Define the circular queue structure
typedef struct {
    float prices[MAX];
    int front, rear, size;
    int capacity;
    float sum;
} MovingAverageQueue;

// Initialize the queue
void initQueue(MovingAverageQueue *q, int k) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = k;
    q->sum = 0.0;
}

// Enqueue new stock price
void enqueue(MovingAverageQueue *q, float price) {
    if (q->size == q->capacity) {
        // Remove the oldest price
        q->sum -= q->prices[q->front];
        q->front = (q->front + 1) % MAX;
        q->size--;
    }

    // Add new price
    q->rear = (q->rear + 1) % MAX;
    q->prices[q->rear] = price;
    q->sum += price;
    q->size++;
}

// Calculate moving average
float getMovingAverage(MovingAverageQueue *q) {
    if (q->size == 0) return 0.0;
    return q->sum / q->size;
}

// Main function
int main() {
    int k;
    float price;
    char choice;

    printf("=== Moving Average Stock Price Calculator ===\n");
    printf("Enter the window size (k): ");
    scanf("%d", &k);

    if (k > MAX) {
        printf("Error: Window size exceeds maximum limit of %d.\n", MAX);
        return 1;
    }

    MovingAverageQueue queue;
    initQueue(&queue, k);

    do {
        printf("\nEnter stock price: ");
        scanf("%f", &price);

        enqueue(&queue, price);
        printf("Current Moving Average of last %d prices: %.2f\n", k, getMovingAverage(&queue));

        printf("Do you want to enter another price? (y/n): ");
        scanf(" %c", &choice);  // space before %c to catch newline
    } while (choice == 'y' || choice == 'Y');

    printf("Thank you for using the Moving Average Calculator.\n");
    return 0;
}
