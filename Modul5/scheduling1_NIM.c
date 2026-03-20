#include <stdio.h>
#include <string.h>

int main() {
    // banyak proses, AT= arrival time, WT=waiting time, TAT=turn around time, time=total time
    // b=burst time, TotWT=total waiting time, TotTA=total turn around time
    // name= process name, AvWT=average waiting time, AvTA=average turn around time
    int n, AT[100], b[100], i, j, tmp, WT[100], TAT[100], time[100];
    int TotWT = 0, TotTA = 0;
    float AvWT, AvTA;
    char name[20][20], tmpName[20];

    printf("\tAlgoritma CPU Scheduling FCFS\n\n");
    printf("Jumlah Proses: ");
    scanf("%d", &n);
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("Nama Proses %d: ", i + 1);
        scanf("%s", name[i]);
        printf("Arrival time %d: ", i + 1);
        scanf("%d", &AT[i]);
        printf("Burst time %d: ", i + 1);
        scanf("%d", &b[i]);
        printf("\n");
    }

    // Sorting berdasarkan Arrival Time (FCFS)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (AT[i] > AT[j]) {
                //tukar name
                strcpy(tmpName, name[i]);
                strcpy(name[i], name[j]);
                strcpy(name[j], tmpName);
                // tukar arrival time
                tmp = AT[i];
                AT[i] = AT[j];
                AT[j] = tmp;
                // tukar burst time
                tmp = b[i];
                b[i] = b[j];
                b[j] = tmp;
            }
        }
    }

    time[0] = AT[0];
    puts("\nTabel Proses");
    puts("=================================================");
    printf("| No | Proses\t | Time Arrival\t | Burst \t|\n");
    puts("=================================================");
    for (i = 0; i < n; i++) {
        printf("| %2d | %s\t | \t%d\t | %d\t\t|\n", i + 1, name[i], AT[i], b[i]);
        time[i + 1] = time[i] + b[i]; // menghitung total time untuk gantt chart
        WT[i] = time[i] - AT[i];
        TAT[i] = time[i + 1] - AT[i];
        TotWT += WT[i];
        TotTA += TAT[i];
    }
    puts("=================================================");

    printf("\nTotal waiting time\t: %d\n", TotWT);
    printf("Total turn around time\t: %d\n", TotTA);

    puts("\nTabel Waktu Proses:");
    puts("=================================================");
    printf("| No | Proses\t | Waiting Time\t | Turn Around\t|\n");
    puts("=================================================");
    for (i = 0; i < n; i++) {
        printf("| %2d | %s\t | \t%d\t | \t%d\t|\n", i + 1, name[i], WT[i], TAT[i]);
    }
    puts("=================================================");
    // Untuk Gantt Chart
    puts("\nGantt Chart:");
    for (i = 0; i < n; i++) {
        printf("   %s\t", name[i]);
    }
    printf("\n");
    for(i = 0; i < n; i++){
        printf("========");
    }
    printf("\n");
    for (i = 0; i <= n; i++) {
        printf("%d\t", time[i]);
    }

    // Menghitung Rata-rata
    printf("\n\n// Diperolah dari penjumlahan Burst Time\n");
    AvWT = (float)TotWT / n;
    AvTA = (float)TotTA / n;
    printf("\nAverage Waiting Time\t: %.2f\n", AvWT);
    printf("Average Turn Around Time\t: %.2f\n", AvTA);

    return 0;
}