#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, head, total = 0, prev;
    cout << "Enter number of disk requests: ";
    cin >> n;

    int requests[n];
    cout << "Enter the requests: ";
    for(int i = 0; i < n; i++)
        cin >> requests[i];

    cout << "Enter initial head position: ";
    cin >> head;

    cout << "Enter previous head position: ";
    cin >> prev;

    sort(requests, requests + n);

    int index = 0;
    for(int i = 0; i < n; i++) {
        if(requests[i] >= head) {
            index = i;
            break;
        }
    }

    cout << "Order of disk access: ";
    
    for(int i = index; i < n; i++) {
        cout << requests[i] << " ";
        total += abs(head - requests[i]);
        head = requests[i];
    }

    if(prev < head) {
        for(int i = index - 1; i >= 0; i--) {
            cout << requests[i] << " ";
            total += abs(head - requests[i]);
            head = requests[i];
        }
    }

    else {
        for(int i = index - 1; i >= 0; i--) {
            cout << requests[i] << " ";
            total += abs(head - requests[i]);
            head = requests[i];
        }
    }

    cout << "\nTotal head movement: " << total << endl;

    return 0;
}
