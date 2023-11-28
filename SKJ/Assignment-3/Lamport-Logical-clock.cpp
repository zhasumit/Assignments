#include <stdio.h>
struct Event
{
    int process_id;
    int logical_clock;
};


void incrementLogicalClock(int *logical_clock)
{
    (*logical_clock)++;
}


int compareEvents(struct Event event1, struct Event event2)
{
    if (event1.logical_clock < event2.logical_clock)
        return -1;


    else if (event1.logical_clock > event2.logical_clock)
        return 1;


    else
    {
        if (event1.process_id < event2.process_id)
            return -1;
        else if (event1.process_id > event2.process_id)
            return 1;
        else
            return 0;
    }
}


int main()
{
    struct Event eventA, eventB;


    int logicalClockA = 0;
    int logicalClockB = 0;
    eventA.process_id = 1;
    eventA.logical_clock = logicalClockA;
    incrementLogicalClock(&logicalClockA);


    eventB.process_id = 2;
    eventB.logical_clock = logicalClockB;
    incrementLogicalClock(&logicalClockB);
   
    int result = compareEvents(eventA, eventB);
    if (result < 0)
        printf("Event A happened before Event B.\n");


    else if (result > 0)
        printf("Event B happened before Event A.\n");


    else
        printf("Event A and Event B are concurrent.\n");
    return 0;
}
