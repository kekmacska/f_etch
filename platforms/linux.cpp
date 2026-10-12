#include <string>
#include <utility>
#include <fstream>

using namespace std;

pair<string, string> read_os_release() {
    ifstream os_release("/etc/os-release");
    string line;
    string family = "Linux (generic)";
    string distro = "Linux (generic)";

    while (getline(os_release, line)) {
        if (line.find("ID_LIKE") != string::npos) {
            line.erase(0, 8);
            line[0] -= 32;
            family = line + " Linux";
        }
        if (line.find("PRETTY_NAME") != string::npos) {
            line.erase(0, 13).erase(7);
            distro = line; // +" Linux" if you really want
        }
    }

    return {family, distro};
}

string distro_family() {
    static auto info = read_os_release();
    return info.first;
}

string distro() {
    static auto info = read_os_release();
    return info.second;
}

string linux_cpu() {
    ifstream cpuinfo("/proc/cpuinfo");
    string line;
    while(getline(cpuinfo,line)) {
        if(line.find("model name") != string::npos) {
            return line.erase(0,line.find(':')+1)
                        .erase(0,line.find_first_not_of(" \t\n\r"))
                        .erase(line.find_last_not_of(" \t\n\r")+1);
        }
    }
    return "unknown";
}