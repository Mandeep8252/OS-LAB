#include <stdio.h>

#define max 100

struct process
{
    int at, bt, rt, wt, tat, ct;
};

void RoundRobin(struct process p[], int n, int tq)
{
    int t = 0, completed = 0;
    int queue[max], front = 0, rear = 0, visited[max] = {0};

    // Initialize remaining time
    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    // Find first arriving process
    int first = 0;
    for (int i = 1; i < n; i++)
        if (p[i].at < p[first].at)
            first = i;

    t = p[first].at;
    queue[rear++] = first;
    visited[first] = 1;

    while (completed < n)
    {
        if (front == rear)
        {
            // CPU idle case
            for (int i = 0; i < n; i++)
            {
                if (!visited[i])
                {
                    t = p[i].at > t ? p[i].at : t;
                    queue[rear++] = i;
                    visited[i] = 1;
                    break;
                }
            }
            continue;
        }

        int idx = queue[front++];

        if (p[idx].rt > 0)
        {
            if (p[idx].rt > tq)
            {
                t += tq;
                p[idx].rt -= tq;
            }
            else
            {
                t += p[idx].rt;
                p[idx].rt = 0;

                p[idx].ct = t;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                completed++;
            }

            // Add newly arrived processes
            for (int i = 0; i < n; i++)
            {
                if (!visited[i] && p[i].at <= t)
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }

            // Re-add current process if not finished
            if (p[idx].rt > 0)
                queue[rear++] = idx;
        }
    }

    printf("\nID\tAT\tBT\tCT\tWT\tTAT\n");
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               i, p[i].at, p[i].bt,
               p[i].ct, p[i].wt, p[i].tat);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main()
{
    int n, tq;
    struct process p[max];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time for process %d: ", i);
        scanf("%d", &p[i].at);

        printf("Enter burst time for process %d: ", i);
        scanf("%d", &p[i].bt);
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    RoundRobin(p, n, tq);

    return 0;
}
