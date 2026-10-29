#include <cstdint>
#include <linux/sysinfo.h>
#include <sstream>
#include <string>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

using namespace std;

string kernelver() {
    struct utsname uname_data;
    if(uname(&uname_data)!=0)return "unknown"; // if it returns with non-zero, it couldn't get the kernel version
    stringstream ss; ss << uname_data.release << " " << uname_data.machine << " " << uname_data.version; // C and C++ strings cannot be directly concatenated apperently
    return ss.str();
}

string uptime() {
    struct sysinfo sysinfo_data;
    if(sysinfo(&sysinfo_data)!=0)return "unknown";
    uint64_t uptimes = sysinfo_data.uptime;

    const uint32_t divs[4] = {86'400,3'600,60,1};
    const char* labels[4] = {" days", " hours", " minutes", " seconds"}; 

    string result;
    result.reserve(16); // reserve 16 bytes
    bool hasvalue = false;

    for(uint8_t i=0;i<4;i++) {
        if(uptimes>=divs[i]) {
            uint64_t value=uptimes/divs[i];
            uptimes%=divs[i];

            if(hasvalue)result+=", ";

            result+=to_string(value);
            result+=labels[i];
            hasvalue=true;
        }
    }

    return hasvalue?result:"unknown";
}