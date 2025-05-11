#include <bits/stdc++.h>
using namespace std;

struct Proc {
    int id, arrival, idx, remaining, ready_time, completion;
    vector<int> bursts;
};

struct ReadyCmp {
    bool operator()(Proc* a, Proc* b) const {
        if (a->remaining != b->remaining)
            return a->remaining > b->remaining;
        if (a->ready_time != b->ready_time)
            return a->ready_time > b->ready_time;
        return a->id > b->id;
    }
};

struct IoEvt {
    int time;
    Proc* p;
};
struct IoCmp {
    bool operator()(const IoEvt& a, const IoEvt& b) const {
        return a.time > b.time;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<Proc> procs(N);
    for (int i = 0; i < N; i++) {
        int arr; cin >> arr;
        procs[i].id = i;
        procs[i].arrival = arr;
        procs[i].idx = 0;
        procs[i].ready_time = arr;
        vector<int> bs;
        while (true) {
            int t; cin >> t;
            if (t == -1) break;
            bs.push_back(t);
        }
        procs[i].bursts = move(bs);
        procs[i].remaining = procs[i].bursts.empty() ? 0 : procs[i].bursts[0];
    }

    // arrival 순 정렬
    vector<Proc*> waitList(N);
    for (int i = 0; i < N; i++) waitList[i] = &procs[i];
    sort(waitList.begin(), waitList.end(),
        [](Proc* a, Proc* b) { return a->arrival < b->arrival; });

    priority_queue<Proc*, vector<Proc*>, ReadyCmp> readyQ;
    priority_queue<IoEvt, vector<IoEvt>, IoCmp> ioQ;

    int nextArr = 0, finished = 0;
    long long idle = 0;
    int time = 0;

    while (finished < N) {
        // arrival → ready
        while (nextArr < N && waitList[nextArr]->arrival <= time) {
            readyQ.push(waitList[nextArr++]);
        }
        // IO complete → ready or finish
        while (!ioQ.empty() && ioQ.top().time <= time) {
            auto ev = ioQ.top(); ioQ.pop();
            Proc* p = ev.p;
            p->idx++;
            if (p->idx < (int)p->bursts.size()) {
                p->remaining = p->bursts[p->idx];
                p->ready_time = ev.time;
                readyQ.push(p);
            }
            else {
                p->completion = ev.time;
                finished++;
            }
        }
        if (readyQ.empty()) {
            int nxt = INT_MAX;
            if (nextArr < N) nxt = min(nxt, waitList[nextArr]->arrival);
            if (!ioQ.empty()) nxt = min(nxt, ioQ.top().time);
            idle += (nxt - time);
            time = nxt;
            continue;
        }
        // 실행 1단위
        Proc* cur = readyQ.top(); readyQ.pop();
        cur->remaining--; time++;
        // 선점 지점에서 재입력
        while (nextArr < N && waitList[nextArr]->arrival <= time)
            readyQ.push(waitList[nextArr++]);
        while (!ioQ.empty() && ioQ.top().time <= time) {
            auto ev = ioQ.top(); ioQ.pop();
            Proc* p = ev.p;
            p->idx++;
            if (p->idx < (int)p->bursts.size()) {
                p->remaining = p->bursts[p->idx];
                p->ready_time = ev.time;
                readyQ.push(p);
            }
            else {
                p->completion = ev.time;
                finished++;
            }
        }
        if (cur->remaining > 0) {
            cur->ready_time = time;
            readyQ.push(cur);
        }
        else {
            cur->idx++;
            if (cur->idx < (int)cur->bursts.size()) {
                int ioEnd = time + cur->bursts[cur->idx];
                ioQ.push({ ioEnd, cur });
            }
            else {
                cur->completion = time;
                finished++;
            }
        }
    }

    cout << idle << "\n";
    for (int i = 0; i < N; i++)
        cout << procs[i].completion << "\n";

    return 0;
}
