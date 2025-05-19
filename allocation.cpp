#include <bits/stdc++.h>
using namespace std;

struct InputProc { int reqTime, execTime, size; };
struct Segment { int start, size, pid; };

vector<InputProc> inputProcs;

int findHole(const vector<Segment>& mem, int reqSize, int algo) {
    int idx = -1;
    if (algo == 0) {
        for (int i = 0; i < (int)mem.size(); ++i)
            if (mem[i].pid == -1 && mem[i].size >= reqSize)
                return i;
    }
    else if (algo == 1) {
        int bestSize = INT_MAX;
        for (int i = 0; i < (int)mem.size(); ++i) {
            if (mem[i].pid == -1 && mem[i].size >= reqSize && mem[i].size < bestSize) {
                bestSize = mem[i].size;
                idx = i;
            }
        }
    }
    else {
        int worstSize = -1;
        for (int i = 0; i < (int)mem.size(); ++i) {
            if (mem[i].pid == -1 && mem[i].size >= reqSize && mem[i].size > worstSize) {
                worstSize = mem[i].size;
                idx = i;
            }
        }
    }
    return idx;
}

void allocateSegment(vector<Segment>& mem, int pos, int reqSize, int pid) {
    int oldStart = mem[pos].start, oldSize = mem[pos].size;
    mem[pos].size = reqSize;
    mem[pos].pid = pid;
    if (oldSize > reqSize) {
        mem.insert(mem.begin() + pos + 1, { oldStart + reqSize, oldSize - reqSize, -1 });
    }
}

int simulate(int algo) {
    int n = inputProcs.size(), lastPid = n - 1;
    deque<int> waitQ;
    vector<Segment> mem = { {0, 1000, -1} };
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> finishPQ;
    int nextReq = 0, lastStart = -1;

    while (true) {
        int nextReqTime = nextReq < n ? inputProcs[nextReq].reqTime : INT_MAX;
        int nextFinTime = !finishPQ.empty() ? finishPQ.top().first : INT_MAX;
        if (nextReqTime == INT_MAX && nextFinTime == INT_MAX) break;
        int curTime = min(nextReqTime, nextFinTime);

        while (!finishPQ.empty() && finishPQ.top().first == curTime) {
            int pid = finishPQ.top().second;
            finishPQ.pop();
            for (int i = 0; i < (int)mem.size(); ++i) {
                if (mem[i].pid == pid) {
                    mem[i].pid = -1;
                    if (i > 0 && mem[i - 1].pid == -1) {
                        mem[i - 1].size += mem[i].size;
                        mem.erase(mem.begin() + i);
                        --i;
                    }
                    if (i + 1 < (int)mem.size() && mem[i + 1].pid == -1) {
                        mem[i].size += mem[i + 1].size;
                        mem.erase(mem.begin() + i + 1);
                    }
                    break;
                }
            }
        }

        if (!waitQ.empty()) {
            deque<int> newQ;
            while (!waitQ.empty()) {
                int pid = waitQ.front(); waitQ.pop_front();
                int pos = findHole(mem, inputProcs[pid].size, algo);
                if (pos >= 0) {
                    int start = mem[pos].start;
                    allocateSegment(mem, pos, inputProcs[pid].size, pid);
                    finishPQ.push({ curTime + inputProcs[pid].execTime, pid });
                    if (pid == lastPid) lastStart = start;
                }
                else {
                    newQ.push_back(pid);
                }
            }
            waitQ.swap(newQ);
        }

        while (nextReq < n && inputProcs[nextReq].reqTime == curTime) {
            int pid = nextReq++;
            int pos = findHole(mem, inputProcs[pid].size, algo);
            if (pos >= 0) {
                int start = mem[pos].start;
                allocateSegment(mem, pos, inputProcs[pid].size, pid);
                finishPQ.push({ curTime + inputProcs[pid].execTime, pid });
                if (pid == lastPid) lastStart = start;
            }
            else {
                waitQ.push_back(pid);
            }
        }

        if (lastStart != -1) break;
    }

    return lastStart;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    inputProcs.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> inputProcs[i].reqTime >> inputProcs[i].execTime >> inputProcs[i].size;

    cout << simulate(0) << "\n"
        << simulate(1) << "\n"
        << simulate(2) << "\n";

    return 0;
}
