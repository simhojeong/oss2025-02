#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> total(m), available(m);
    for (int i = 0; i < m; i++)
        cin >> total[i];

    vector<vector<int>> maxReq(n, vector<int>(m));
    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maxReq[i][j];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
            need[i][j] = maxReq[i][j] - allocation[i][j];
            available[j] += allocation[i][j];
        }
    }

    for (int j = 0; j < m; j++)
        available[j] = total[j] - available[j];

    cin.ignore();
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        string cmd;
        iss >> cmd;
        if (cmd == "quit")
            break;
        int pid;
        iss >> pid;
        vector<int> req(m);
        for (int i = 0; i < m; i++)
            iss >> req[i];

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
                    bool progress;
                    do {
                        progress = false;
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
                                    progress = true;
                                }
                            }
                        }
                    } while (progress);
                    for (bool f : finish) {
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
        }
        else if (cmd == "release") {
            for (int i = 0; i < m; i++) {
                allocation[pid][i] -= req[i];
                need[pid][i] += req[i];
                available[i] += req[i];
            }
        }

        for (int i = 0; i < m; i++)
            cout << available[i] << (i == m - 1 ? '\n' : ' ');
    }
    return 0;
}
