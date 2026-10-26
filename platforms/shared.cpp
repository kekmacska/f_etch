#include <sstream>
#include <string>
#include <sys/utsname.h>
using namespace std;

string kernelver(){
    struct utsname uname_data;
    if(uname(&uname_data)!=0)return "unknown"; // if it returns with non-zero, it couldn't get the kernel version
    stringstream ss; ss << uname_data.release << " " << uname_data.machine << " " << uname_data.version; // C and C++ strings cannot be directly concatenated apperently
    return ss.str();
}