#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

struct Process {
    vector<int> tasks;
};

int main() {
    ifstream inputFile("batch.inp");
    ofstream outputFile("batch.out");

    if (!inputFile || !outputFile) {
        cerr << "파일을 열 수 없습니다." << endl;
        return 1;
    }

    int N;
    inputFile >> N;

    queue<Process> processes;
    for (int i = 0; i < N; i++) {
        Process p;
        int task;
        while (inputFile >> task && task != -1) {
            p.tasks.push_back(task);
        }
        processes.push(p);
    }

    int cpuIdleTime = 0;
    int totalProcessingTime = 0;
    queue<int> ioQueue;

    while (!processes.empty() || !ioQueue.empty()) {
        if (!processes.empty()) {
            Process current = processes.front();
            processes.pop();
            for (int t : current.tasks) {
                if (t > 0) {
                    totalProcessingTime += t;
                }
                else {
                    ioQueue.push(-t);
                }
            }
        }
        if (!ioQueue.empty()) {
            cpuIdleTime += ioQueue.front();
            ioQueue.pop();
        }
    }

    outputFile << cpuIdleTime << " " << totalProcessingTime << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
