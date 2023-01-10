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

Queue lane1;
Queue lane2;
Queue lane3;
Queue lane4;

typedef struct
{
    int lane1_light;
    int lane2_light;
    int lane3_light;
    int lane4_light;

} TrafficLights;

TrafficLights lights;

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

void initAll()
{
    init(&lane1);
    init(&lane2);
    init(&lane3);
    init(&lane4);

    lights.lane1_light = 0;
    lights.lane2_light = 0;
    lights.lane3_light = 0;
    lights.lane4_light = 0;
}

void add_vehicle(int lane)
{
    // Checking if the traffic light is green for the lane
    if (lane == 1)
    {
        int type = rand() % 3;
        int size = rand() % 5 + 1;
        Vehicle v = {type, size};
        enqueue(&lane1, v);
        printf("Added vehicle to lane 1: type=%d, size=%d\n", type, size);
    }
    else if (lane == 2)
    {
        int type = rand() % 3;
        int size = rand() % 5 + 1;
        Vehicle v = {type, size};
        enqueue(&lane2, v);
        printf("Added vehicle to lane 2: type=%d, size=%d\n", type, size);
    }
    else if (lane == 3)
    {
        int type = rand() % 3;
        int size = rand() % 5 + 1;
        Vehicle v = {type, size};
        enqueue(&lane3, v);
        printf("Added vehicle to lane 3: type=%d, size=%d\n", type, size);
    }
    else if (lane == 4)
    {
        int type = rand() % 3;
        int size = rand() % 5 + 1;
        Vehicle v = {type, size};
        enqueue(&lane4, v);
        printf("Added vehicle to lane 4: type=%d, size=%d\n", type, size);
    }
}

void remove_vehicle()
{
    if (lights.lane1_light == 1)
    {
        if (!is_empty(&lane1))
        {
            Vehicle v = dequeue(&lane1);
            printf("Removed vehicle from lane 1: type=%d, size=%d\n", v.type, v.size);
        }
    }
    else if (lights.lane2_light == 1)
    {
        if (!is_empty(&lane2))
        {
            Vehicle v = dequeue(&lane2);
            printf("Removed vehicle from lane 2: type=%d, size=%d\n", v.type, v.size);
        }
    }
    else if (lights.lane3_light == 1)
    {
        if (!is_empty(&lane3))
        {
            Vehicle v = dequeue(&lane3);
            printf("Removed vehicle from lane 3: type=%d, size=%d\n", v.type, v.size);
        }
    }
    else if (lights.lane4_light == 1)
    {
        if (!is_empty(&lane4))
        {
            Vehicle v = dequeue(&lane4);
            printf("Removed vehicle from lane 4: type=%d, size=%d\n", v.type, v.size);
        }
    }
}

void switch_traffic_lights(int time)
{
    // switch the lights if time remaining is 0
    if (time >= 5 && time <= 10)
    {
        printf("Green light lane 1\n");
        lights.lane1_light = 1;
    }
    else if (time >= 15 && time <= 20)
    {
        printf("Green light lane 2\n");
        lights.lane1_light = 0;
        lights.lane2_light = 1;
    }
    else if (time >= 25 && time <= 30)
    {
        printf("Green light lane 3\n");
        lights.lane2_light = 0;
        lights.lane3_light = 1;
    }
    else if (time >= 35 && time <= 40)
    {
        printf("Green light lane 4\n");
        lights.lane3_light = 0;
        lights.lane4_light = 1;
    }
    else
    {
        lights.lane1_light = 0;
        lights.lane2_light = 0;
        lights.lane3_light = 0;
        lights.lane4_light = 0;
    }
}

int main()
{
    srand(time(NULL));
    initAll();
    int x = 0;
    while (1)
    {

        if (rand() % 2 == 0)
        {
            int lane = rand() % 4 + 1;
            add_vehicle(lane);
        }

        remove_vehicle();

        // Switching traffic lights every 5 seconds

        switch_traffic_lights(x);

        x = x == 40 ? 0 : x + 1;
        sleep(1);
    }
    return 0;
}