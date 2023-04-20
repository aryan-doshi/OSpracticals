#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    int num_frames, num_pages, page_faults = 0, curr_time = 0;
    cout << "Enter the number of frames: ";
    cin >> num_frames;
    cout << "Enter the number of pages: ";
    cin >> num_pages;
    vector<int> pages(num_pages);
    cout << "Enter the sequence of pages: ";
    for (int i = 0; i < num_pages; i++) {
        cin >> pages[i];
    }

    unordered_map<int, int> frame_table;
    vector<int> frames(num_frames, -1);

    for (int i = 0; i < num_pages; i++) {
        int page_num = pages[i];
        if (frame_table.find(page_num) != frame_table.end()) {
            int frame_num = frame_table[page_num];
            frames[frame_num] = curr_time;
        }
        else {
            int min_time = INT_MAX, min_index = 0;
            bool empty_frame_found = false;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    frames[j] = curr_time;
                    frame_table[page_num] = j;
                    empty_frame_found = true;
                    break;
                }
                else if (frames[j] < min_time) {
                    min_time = frames[j];
                    min_index = j;
                }
            }
            if (!empty_frame_found) {
                int page_to_replace = -1;
                for (auto it = frame_table.begin(); it != frame_table.end(); it++) {
                    if (it->second == min_index) {
                        page_to_replace = it->first;
                        break;
                    }
                }
                frame_table.erase(page_to_replace);
                frame_table[page_num] = min_index;
            }
            page_faults++;
        }
        curr_time++;
    }

    cout << "Number of page faults: " << page_faults << endl;

    return 0;
}
