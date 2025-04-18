#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    unordered_map<string, string> unixToDos = {
        {"ls", "dir"}, {"mkdir", "md"}, {"rmdir", "rd"}, {"rm", "del"}, {"cp", "copy"}, {"mv", "rename"},
        {"clear", "cls"}, {"pwd", "cd"}, {"cat", "type"}, {"man", "help"}, {"date", "time"}, {"grep", "findstr"},
        {"find", "find"}, {"more", "more"}, {"sort", "sort"}, {"diff", "comp"}, {"ed", "edlin"},
        {"attrib", "lsattr"}, {"pushd", "pushd"}, {"popd", "popd"}, {"ps", "taskmgr"}, {"kill", "taskkill"},
        {"halt", "shutdown"}, {"ifconfig", "ipconfig"}, {"fsck", "chkdsk"}, {"free", "mem"}, {"debugfs", "scandisk"},
        {"lpr", "print"}
    };

    unordered_map<string, string> dosToUnix;
    for (const auto& pair : unixToDos) {
        dosToUnix[pair.second] = pair.first;
    }

    ifstream input("C:/Users/user/Desktop/sampleData2/command.inp");
    ofstream output("C:/Users/user/Desktop/sampleData2/command.out");

    int N;
    input >> N;

    string command;
    for (int i = 0; i < N; ++i) {
        input >> command;

        if (unixToDos.find(command) != unixToDos.end()) {
            output << command << " -> " << unixToDos[command] << endl;
        }
        else if (dosToUnix.find(command) != dosToUnix.end()) {
            output << command << " -> " << dosToUnix[command] << endl;
        }
        else {
            output << command << " -> (no mapping)" << endl;
        }
    }

    input.close();
    output.close();
    return 0;
}
