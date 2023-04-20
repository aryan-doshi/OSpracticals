#include<iostream>
#include<queue>
using namespace std;

struct Process {
    int pid;
    int bt;
    int rt;
};

void roundRobinScheduling(Process processes[], int n, int quantum) {
    queue<int> readyQueue;
    int t = 0;
    int completed = 0;
    int waitingTime[n];
    
    for (int i = 0; i < n; i++) {
        processes[i].rt = processes[i].bt;
    }
    
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].rt > 0) {
                readyQueue.push(i);
            }
        }
        
        while (!readyQueue.empty()) {
            int i = readyQueue.front();
            readyQueue.pop();
            
            if (processes[i].rt > quantum) {
                t += quantum;
                processes[i].rt -= quantum;
            } else {
                t += processes[i].rt;
                waitingTime[i] = t - processes[i].bt;
                processes[i].rt = 0;
                completed++;
            }
        }
    }
    
    cout << "Waiting time for each process: ";
    for (int i = 0; i < n; i++) {
        cout << waitingTime[i] << " ";
    }
    cout << endl;
}

int main() {
    int n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> quantum;
    
    Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter the burst time for process " << processes[i].pid << ": ";
        cin >> processes[i].bt;
    }
    
    roundRobinScheduling(processes, n, quantum);
    
    return 0;
}
