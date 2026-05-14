#include <stdio.h>
#include <stdbool.h>
#define MAX 10
int main()
{
 int n, m; // n = processes, m = resources
 int allocation[MAX][MAX], request[MAX][MAX], available[MAX];
 bool finish[MAX] = {false};
 printf("Enter number of processes: ");
 scanf("%d", &n);
 printf("Enter number of resources: ");
 scanf("%d", &m);
 printf("Enter Allocation Matrix:\n");
 for (int i = 0; i < n; i++)
 for (int j = 0; j < m; j++)
 scanf("%d", &allocation[i][j]);
 printf("Enter Request Matrix:\n");
 for (int i = 0; i < n; i++)
 for (int j = 0; j < m; j++)
 scanf("%d", &request[i][j]);
 printf("Enter Available Resources:\n");
 for (int i = 0; i < m; i++)
 scanf("%d", &available[i]);
 int count = 0;
 while (count < n)
 {
 bool found = false; for (int i = 0; i < n; i++)
 {
 if (!finish[i])
 {
 bool canFinish = true;
 for (int j = 0; j < m; j++)
 {
 if (request[i][j] > available[j]) //Alternatively <=
 {
 canFinish = false;
 break;
 }
 }
 if (canFinish)
 {
 for (int j = 0; j < m; j++)
 available[j] += allocation[i][j];
 finish[i] = true;
 found = true;
 count++;
 }
 }
 }
 if (!found) break;
 }
 bool deadlock = false;
 printf("\nProcesses in Deadlock:\n");
 for (int i = 0; i < n; i++)
 {
 if (!finish[i])
 {
 printf("P%d ", i);
 deadlock = true;
 }
 } if (!deadlock)
 printf("No deadlock detected. All processes can finish.\n");
 else
 printf("\nDeadlock detected among above processes.\n");
return 0;
}