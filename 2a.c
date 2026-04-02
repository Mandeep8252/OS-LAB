#include <stdio.h>
#define MAX 100

struct Process {
    int id, at, bt, ct, wt, tat, type;
};


void sort(struct Process p[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (p[j].at > p[j+1].at) {
                struct Process t = p[j];
                p[j] = p[j+1];
                p[j+1] = t;
            }
}


void fcfs(struct Process p[], int n, int *time) {
    for (int i = 0; i < n; i++) {
        if (*time < p[i].at) {
            printf("| Idle ");
            *time = p[i].at;
        }

        printf("| P%d ", p[i].id);

        p[i].wt = *time - p[i].at;
        p[i].ct = *time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;

        *time = p[i].ct;
    }
}

int main() {
    int n, sc = 0, uc = 0, time = 0;
    struct Process sys[MAX], usr[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        struct Process p;
        p.id = i;

        printf("\nP%d\nAT: ", i);
        scanf("%d", &p.at);
        printf("BT: ");
        scanf("%d", &p.bt);
        printf("Type (0=System,1=User): ");
        scanf("%d", &p.type);

        if (p.type == 0) sys[sc++] = p;
        else usr[uc++] = p;
    }

    sort(sys, sc);
    sort(usr, uc);

    printf("\nGantt Chart:\n");

    fcfs(sys, sc, &time);
    fcfs(usr, uc, &time);

    printf("|\n0");


    int t = 0;
    for (int i = 0; i < sc; i++) {
        if (t < sys[i].at) t = sys[i].at;
        t += sys[i].bt;
        printf(" %d", t);
    }
    for (int i = 0; i < uc; i++) {
        if (t < usr[i].at) t = usr[i].at;
        t += usr[i].bt;
        printf(" %d", t);
    }


    printf("\n\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");
    float twt = 0, ttat = 0;

    for (int i = 0; i < sc; i++) {
        printf("%d\tSystem\t%d\t%d\t%d\t%d\t%d\n",
            sys[i].id, sys[i].at, sys[i].bt,
            sys[i].ct, sys[i].wt, sys[i].tat);
        twt += sys[i].wt; ttat += sys[i].tat;
    }

    for (int i = 0; i < uc; i++) {
        printf("%d\tUser\t%d\t%d\t%d\t%d\t%d\n",
            usr[i].id, usr[i].at, usr[i].bt,
            usr[i].ct, usr[i].wt, usr[i].tat);
        twt += usr[i].wt; ttat += usr[i].tat;
    }

    printf("\nAvg WT = %.2f", twt / n);
    printf("\nAvg TAT = %.2f\n", ttat / n);

    return 0;
}
