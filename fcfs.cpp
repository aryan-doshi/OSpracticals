#include <iostream>
using namespace std;

int main() {
    int n, burst_time[10], wait_time[10], turn_around_time[10],
        avg_wait_time = 0, avg_turnaround_time = 0, i;
    cout << "Enter the number of processes: ";
    cin >> n;

    cout << "Enter burst time for each process: ";
    for (i = 0; i < n; i++) {
        cin >> burst_time[i];
    }

    wait_time[0] = 0;
    for (i = 1; i < n; i++) {
        wait_time[i] = wait_time[i - 1] + burst_time[i - 1];
    }
    for (i = 0; i < n; i++) {
        turn_around_time[i] = wait_time[i] + burst_time[i];
    }
    for (i = 0; i < n; i++) {
        avg_wait_time += wait_time[i];
        avg_turnaround_time += turn_around_time[i];
    }

    avg_wait_time /= n;
    avg_turnaround_time /= n;

    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";

    for (i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t" << burst_time[i] << "\t\t" << wait_time[i] << "\t\t" << turn_around_time[i] << endl;
    }

    cout << "Average Waiting Time: " << avg_wait_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;

    return 0;
}
