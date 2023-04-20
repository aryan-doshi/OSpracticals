#include <iostream>
#include <vector>
using namespace std;

const int MAX_PROCESSES = 10;
const int MAX_RESOURCES = 5;

int main() {
    int num_processes, num_resources;
    int available[MAX_RESOURCES];
    int allocated[MAX_PROCESSES][MAX_RESOURCES];
    int max_required[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];

    cout << "Enter the number of processes: ";
    cin >> num_processes;

    cout << "Enter the number of resources: ";
    cin >> num_resources;

    cout << "Enter the available resources: ";
    for (int i = 0; i < num_resources; i++) {
        cin >> available[i];
    }

    cout << "Enter the allocation matrix:\n";
    for (int i = 0; i < num_processes; i++) {
        cout << "Process " << i << ":\n";
        for (int j = 0; j < num_resources; j++) {
            cin >> allocated[i][j];
        }
    }

    cout << "Enter the maximum required matrix:\n";
    for (int i = 0; i < num_processes; i++) {
        cout << "Process " << i << ":\n";
        for (int j = 0; j < num_resources; j++) {
            cin >> max_required[i][j];
            need[i][j] = max_required[i][j] - allocated[i][j];
        }
    }

    // Initialize the Finish array to false for all processes
    bool finish[num_processes];
    for (int i = 0; i < num_processes; i++) {
        finish[i] = false;
    }

    // Initialize the Work array to the available resources
    int work[MAX_RESOURCES];
    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    // Find a process that can finish
    bool found;
    do {
        found = false;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                bool can_finish = true;
                for (int j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_finish = false;
                        break;
                    }
                }
                if (can_finish) {
                    found = true;
                    for (int j = 0; j < num_resources; j++) {
                        work[j] += allocated[i][j];
                    }
                    finish[i] = true;
                }
            }
        }
    } while (found);

    // Check if all processes are finished
    bool all_finished = true;
    for (int i = 0; i < num_processes; i++) {
        if (!finish[i]) {
            all_finished = false;
            break;
        }
    }

    if (all_finished) {
        cout << "The system is in a safe state.\n";
    } else {
        cout << "The system is not in a safe state.\n";
    }

    return 0;
}
