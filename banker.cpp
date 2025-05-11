#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main() {
    ifstream fin("banker.inp");
    ofstream fout("banker.out");
    int n, m;
    fin >> n >> m;
    vector<int> total(m), available(m);
    for (int i = 0; i < m; i++) fin >> total[i];
    vector<vector<int>> max(n, vector<int>(m)), allocation(n, vector<int>(m)), need(n, vector<int>(m));
    string line;
    getline(fin, line);
    getline(fin, line);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fin >> max[i][j];
    getline(fin, line);
    getline(fin, line);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            fin >> allocation[i][j];
            need[i][j] = max[i][j] - allocation[i][j];
            available[j] += allocation[i][j];
        }
    for (int j = 0; j < m; j++)
        available[j] = total[j] - available[j];

    while (getline(fin, line)) {
        istringstream iss(line);
        string cmd;
        iss >> cmd;
        if (cmd == "quit") break;
        int pid;
        iss >> pid;
        vector<int> req(m);
        for (int i = 0; i < m; i++) iss >> req[i];
        if (cmd == "request") {
            bool invalid = false;
            for (int i = 0; i < m; i++)
                if (req[i] > need[pid][i]) {
                    invalid = true;
                    break;
                }
            if (!invalid) {
                bool enough = true;
                for (int i = 0; i < m; i++)
                    if (req[i] > available[i]) {
                        enough = false;
                        break;
                    }
                if (enough) {
                    for (int i = 0; i < m; i++) {
                        available[i] -= req[i];
                        allocation[pid][i] += req[i];
                        need[pid][i] -= req[i];
                    }
                    vector<bool> finish(n, false);
                    vector<int> work = available;
                    while (true) {
                        bool done = false;
                        for (int i = 0; i < n; i++) {
                            if (!finish[i]) {
                                bool canFinish = true;
                                for (int j = 0; j < m; j++)
                                    if (need[i][j] > work[j]) {
                                        canFinish = false;
                                        break;
                                    }
                                if (canFinish) {
                                    for (int j = 0; j < m; j++)
                                        work[j] += allocation[i][j];
                                    finish[i] = true;
                                    done = true;
                                }
                            }
                        }
                        if (!done) break;
                    }
                    for (bool f : finish)
                        if (!f) {
                            for (int i = 0; i < m; i++) {
                                available[i] += req[i];
                                allocation[pid][i] -= req[i];
                                need[pid][i] += req[i];
                            }
                            break;
                        }
                }
            }
        }
        else if (cmd == "release") {
            for (int i = 0; i < m; i++) {
                allocation[pid][i] -= req[i];
                need[pid][i] += req[i];
                available[i] += req[i];
            }
        }
        for (int i = 0; i < m; i++) fout << available[i] << (i == m - 1 ? '\n' : ' ');
    }
    return 0;
}
