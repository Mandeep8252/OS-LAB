
#include <stdio.h>
#define max 10
struct process {
int at;
int bt;
int wt;
int tat;
int ct;
int done;
};
void SJF(struct process p[], int n)
{
int completed = 0;
int t = 0;
float total_wt = 0, total_tat = 0;
while (completed < n)
{
int idx = -1;
int min_bt = 9999;
for (int i = 0; i < n; i++)
{
if (p[i].at <= t && p[i].done == 0)
{
if (p[i].bt < min_bt)
{
min_bt = p[i].bt;
idx = i;
}
else if (p[i].bt == min_bt)
{
if (p[i].at < p[idx].at)
{
idx = i;
}
}
}
}
if (idx != -1)
{
p[idx].wt = t - p[idx].at;
p[idx].ct = t + p[idx].bt;
p[idx].tat = p[idx].ct - p[idx].at;
total_wt += p[idx].wt;
total_tat += p[idx].tat;
p[idx].done = 1;
completed++;
t = p[idx].ct;
}
else {
t++;
}
}
printf("\nID\tAT\tBT\tCT\tWT\tTAT\n");
for (int i = 0; i < n; i++)
{
printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, p[i].at, p[i].bt, p[i].ct,
p[i].wt, p[i].tat);
}
printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main()
{
int n;
struct process p[max];
printf("Enter number of processes: ");
scanf("%d", &n);
for (int i = 0; i < n; i++)
{
printf("Enter arrival time for process %d: ", i);
scanf("%d", &p[i].at);
printf("Enter burst time for process %d: ", i);
scanf("%d", &p[i].bt);
p[i].done = 0; // Initialize all as not done
}
SJF(p, n);
return 0;
}
