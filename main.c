#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAX_SIZE 100

typedef struct
{
    int type;
    int size;
} Vehicle;

typedef struct
{
    Vehicle vehicles[MAX_SIZE];
    int head;
    int tail;
} Queue;

void init(Queue *q)
{
    q->head = 0;
    q->tail = 0;
}

int is_empty(Queue *q)
{
    return q->head == q->tail;
}

int is_full(Queue *q)
{
    return (q->tail + 1) % MAX_SIZE == q->head;
}

void enqueue(Queue *q, Vehicle value)
{
    if (is_full(q))
    {
        printf("error: queue is full\n");
        return;
    }
    q->vehicles[q->tail] = value;
    q->tail = (q->tail + 1) % MAX_SIZE;
}

Vehicle dequeue(Queue *q)
{
    if (is_empty(q))
    {
        printf("error: queue is empty\n");
        return (Vehicle){0, 0};
    }
    Vehicle value = q->vehicles[q->head];
    q->head = (q->head + 1) % MAX_SIZE;
    return value;
}

void add_random_vehicle()
{
    srand(time(NULL));
    Queue q;
    init(&q);
    int x = 0;
    while (1)
    {
        // Add a new vehicle to the queue at a random interval
        if (rand() % 4 == 3 || rand() % 4 == 1)
        {
            int type = rand() % 3;
            int size = rand() % 5 + 1;
            Vehicle v = {type, size};
            enqueue(&q, v);
            printf("Added vehicle: type=%d, size=%d\n", type, size);
        }

        // Remove a vehicle from the queue if the queue is not empty
        if(x == 25){
            
            x = 0;
        }
        if (!is_empty(&q) && x > 20)
        {
            Vehicle v = dequeue(&q);
            printf("Removed vehicle: type=%d, size=%d\n", v.type, v.size);
        }
        // Sleep for a short time before the next iteration
        printf("%d\n", x);
        x++;
        sleep(1);
    }
}

int main()
{
    add_random_vehicle();
    return 0;
}