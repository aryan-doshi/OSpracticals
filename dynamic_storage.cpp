#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Block {
    int id;
    int size;
    int status;
};

int getBlockIndexById(vector<Block>& blocks, int id) {
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i].id == id) {
            return i;
        }
    }
    return -1;
}

void printBlocks(vector<Block>& blocks) {
    cout << "ID\tSize\tStatus\n";
    for (Block block : blocks) {
        cout << block.id << "\t" << block.size << "\t" << (block.status == 0 ? "Free" : "Allocated") << endl;
    }
}

void firstFit(vector<Block>& blocks, int processId, int processSize) {
    for (Block& block : blocks) {
        if (block.status == 0 && block.size >= processSize) {
            block.status = 1;
            cout << "Process " << processId << " allocated to block " << block.id << endl;
            return;
        }
    }
    cout << "Process " << processId << " cannot be allocated using First Fit" << endl;
}

void bestFit(vector<Block>& blocks, int processId, int processSize) {
    vector<Block> freeBlocks;
    for (Block& block : blocks) {
        if (block.status == 0 && block.size >= processSize) {
            freeBlocks.push_back(block);
        }
    }
    if (freeBlocks.empty()) {
        cout << "Process " << processId << " cannot be allocated using Best Fit" << endl;
        return;
    }
    auto bestBlock = min_element(freeBlocks.begin(), freeBlocks.end(), [](Block a, Block b) {
        return a.size < b.size;
    });
    bestBlock->status = 1;
    cout << "Process " << processId << " allocated to block " << bestBlock->id << endl;
}

void worstFit(vector<Block>& blocks, int processId, int processSize) {
    vector<Block> freeBlocks;
    for (Block& block : blocks) {
        if (block.status == 0 && block.size >= processSize) {
            freeBlocks.push_back(block);
        }
    }
    if (freeBlocks.empty()) {
        cout << "Process " << processId << " cannot be allocated using Worst Fit" << endl;
        return;
    }
    auto worstBlock = max_element(freeBlocks.begin(), freeBlocks.end(), [](Block a, Block b) {
        return a.size < b.size;
    });
    worstBlock->status = 1;
    cout << "Process " << processId << " allocated to block " << worstBlock->id << endl;
}

int main() {
    vector<Block> blocks = {
        {1, 100, 0},
        {2, 250, 0},
        {3, 50, 0},
        {4, 150, 0},
        {5, 300, 0},
    };

    printBlocks(blocks);

    firstFit(blocks, 1, 200);
    firstFit(blocks, 2, 75);

    bestFit(blocks, 3, 200);
    bestFit(blocks, 4, 75);

    worstFit(blocks, 5, 200);
    worstFit(blocks, 6, 75);

    printBlocks(blocks);

    return 0;
}
