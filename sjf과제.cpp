#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    vector<int> bursts;
    int index = 0;
    int finish_time = 0;
};

int main() {
    ifstream fin("sjf.inp");
    ofstream fout("sjf.out");

    int n;
    fin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        int arrival;
        fin >> arrival;
        processes[i].pid = i;
        processes[i].arrival_time = arrival;
        int t;
        while (fin >> t && t != -1) {
            processes[i].bursts.push_back(t);
        }
    }

    int time = 0;
    int idle_time = 0;

    vector<Process*> ready_queue;
    vector<pair<Process*, int>> io_waiting;
    vector<Process*> not_arrived;
    for (auto& p : processes) not_arrived.push_back(&p);

    while (!ready_queue.empty() || !not_arrived.empty() || !io_waiting.empty()) {
        // I/O 작업 완료된 프로세스
        for (auto it = io_waiting.begin(); it != io_waiting.end();) {
            if (it->second <= time) {
                it->first->arrival_time = it->second;
                ready_queue.push_back(it->first);
                it = io_waiting.erase(it);
            }
            else ++it;
        }

        // 도착한 프로세스
        for (auto it = not_arrived.begin(); it != not_arrived.end();) {
            if ((*it)->arrival_time <= time) {
                ready_queue.push_back(*it);
                it = not_arrived.erase(it);
            }
            else ++it;
        }

        if (ready_queue.empty()) {
            time++;
            idle_time++;
            continue;
        }

        // SJF 선택
        auto selected = min_element(ready_queue.begin(), ready_queue.end(), [](Process* a, Process* b) {
            if (a->bursts[a->index] != b->bursts[b->index])
                return a->bursts[a->index] < b->bursts[b->index];
            return a->pid < b->pid;
            });

        Process* current = *selected;
        ready_queue.erase(selected);

        int cpu_time = current->bursts[current->index];
        time += cpu_time;
        current->index++;

        if (current->index < current->bursts.size()) {
            int io_time = current->bursts[current->index];
            current->index++;
            io_waiting.push_back({ current, time + io_time });
        }
        else {
            current->finish_time = time;
        }
    }

    fout << idle_time << '\n';
    for (auto& p : processes) {
        fout << p.finish_time << '\n';
    }

    return 0;
}
