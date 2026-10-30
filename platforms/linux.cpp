#include <string>
#include <utility>
#include <fstream>
#include <cstring>

using namespace std;

pair<string, string> read_os_release() {
    ifstream file("/etc/os-release");
    string line;
    string family = "Linux";
    string distro = "Linux (generic)";
    bool have_family = false;
    bool have_distro = false;

    while ((!have_family || !have_distro) && getline(file, line)) {
        // ID_LIKE
        if (!have_family && line.compare(0, 8, "ID_LIKE=") == 0) {
            size_t val_start = 8;
            size_t val_len = line.size() - 8;
            
            if (val_len >= 2 && line[8] == '"' && line.back() == '"') {
                val_start = 9;
                val_len -= 2;
            }
            
            if (val_len > 0) {
                family.assign(line.data() + val_start, val_len);
                if (!family.empty()) family[0] &= ~0x20; // make the first char uppercase if family is not empty, by zeroing the 6th bit from backwards in binary ASCII using AND assignment
                // example: 'A'=0x41, 'a'=0x61 - the hexadecimal difference is 0x20 (bit 6) https://en.wikipedia.org/wiki/ASCII#mwBb4
                family += " Linux";
                have_family = true;
            }
        } 
        // PRETTY_NAME
        else if (!have_distro && line.compare(0, 12, "PRETTY_NAME=") == 0) {
            size_t val_start = 12;
            size_t val_len = line.size() - 12;

            if (val_len >= 2 && line[12] == '"' && line.back() == '"') {
                val_start = 13;
                val_len -= 2;
            }

            if (val_len > 0) {
                distro.assign(line.data() + val_start, val_len);
                have_distro = true;
            }
        }
    }

    return {std::move(family), std::move(distro)};
}

const auto distro_info() { // helper to only call reader function once
    static pair<string, string> info=read_os_release();
    return info;
}

string distro_family() {
    return distro_info().first;
}

string distro() {
    return distro_info().second;
}

string linux_cpu() {
    ifstream cpuinfo("/proc/cpuinfo");
    string line;
    
    while (getline(cpuinfo, line)) {
        // "model name\t: " is 13 chars. 
        if (line.size() > 13 && memcmp(line.data(), "model name", 10) == 0) {
            size_t colon_pos = 10;
            while (colon_pos < line.size() && line[colon_pos] != ':') ++colon_pos;
            
            if (colon_pos < line.size()) {
                size_t start = colon_pos + 1;
                // Skip leading whitespace
                while (start < line.size() && (line[start] == ' ' || line[start] == '\t')) ++start;
                // Find end of string (trim trailing whitespace)
                size_t end = line.size();
                while (end > start && (line[end-1] == ' ' || line[end-1] == '\t' || line[end-1] == '\r')) --end;
                
                return line.substr(start, end - start);
            }
        }
    }
    return "unknown";
}