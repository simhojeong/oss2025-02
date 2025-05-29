#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <string>
using namespace std;

int simulateFIFO(const vector<int>& pages, int frameSize) {
    queue<int> q;
    unordered_set<int> frames;
    int faults = 0;
    for (int page : pages) {
        if (frames.find(page) == frames.end()) {
            faults++;
            if (frames.size() == frameSize) {
                frames.erase(q.front());
                q.pop();
            }
            frames.insert(page);
            q.push(page);
        }
    }
    return faults;
}

int simulateLRU(const vector<int>& pages, int frameSize) {
    list<int> lru;
    unordered_map<int, list<int>::iterator> pageMap;
    int faults = 0;
    for (int page : pages) {
        if (pageMap.find(page) == pageMap.end()) {
            faults++;
            if ((int)lru.size() == frameSize) {
                int old = lru.back();
                lru.pop_back();
                pageMap.erase(old);
            }
        }
        else {
            lru.erase(pageMap[page]);
        }
        lru.push_front(page);
        pageMap[page] = lru.begin();
    }
    return faults;
}

int simulateOPT(const vector<int>& pages, int frameSize) {
    unordered_set<int> frames;
    int faults = 0;
    for (int i = 0; i < pages.size(); ++i) {
        int page = pages[i];
        if (frames.find(page) == frames.end()) {
            faults++;
            if ((int)frames.size() == frameSize) {
                int victim = -1, farthest = -1;
                for (int f : frames) {
                    int j;
                    for (j = i + 1; j < pages.size(); ++j) {
                        if (pages[j] == f) break;
                    }
                    if (j == pages.size()) {
                        victim = f;
                        break;
                    }
                    if (j > farthest) {
                        farthest = j;
                        victim = f;
                    }
                }
                frames.erase(victim);
            }
            frames.insert(page);
        }
    }
    return faults;
}

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;

    string base = argv[1];
    ifstream fin(base + ".inp");
    ofstream fout(base + ".out");

    int frameSize, page;
    fin >> frameSize;
    vector<int> pages;
    while (fin >> page && page != -1) {
        pages.push_back(page);
    }

    fout << "FIFO: " << simulateFIFO(pages, frameSize) << endl;
    fout << "LRU: " << simulateLRU(pages, frameSize) << endl;
    fout << "OPT: " << simulateOPT(pages, frameSize) << endl;

    fin.close();
    fout.close();
    return 0;
}
