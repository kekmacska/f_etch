#include <string>
#include <string_view>
#if defined(__has_include)
    #if __has_include(<print>)
        #include <print>
        #define USE_STD_PRINT
    #endif
#endif

using namespace std;

#if defined(__linux__) && !defined(__ANDROID__)
    #define IS_NON_ANDROID_LINUX 1
#endif

#ifdef IS_NON_ANDROID_LINUX
    #include "platforms/linux.cpp"
    #include "distros/arch.hpp"
#endif

#ifdef __ANDROID__
    #include "platforms/android.cpp"
    #include "distros/android.hpp"
#endif

string_view logo_for_distro() { // customize the return values. see definitions in distros/*.hpp
    #ifdef IS_NON_ANDROID_LINUX
        if(distro_family()=="Arch Linux") {
            return archlogo_fullblock;
        }
    #endif

    #ifdef __ANDROID__
        return androidlogo_dot;
    #endif

    return string_view("");
}

string cpu() {
    #ifdef __ANDROID__
        return android_cpu();
    #endif

    #ifdef IS_NON_ANDROID_LINUX
        return linux_cpu();
    #endif
    // else
    return "unknown";
}

// customize these as you wish. empty string is terminal default, usually white
#define DISTRO_FAMILY_COLOR "\x1b[38;2;0;215;255m"   // cyan
#define DISTRO_COLOR        "\x1b[38;2;255;95;175m"  // pink
#define CPU_COLOR           "\x1b[38;2;255;175;0m"   // amber
#define RESET "\x1b[0m"

int main() {
#ifdef USE_STD_PRINT
    // C++26
    print("{}\n", logo_for_distro()); // this is colored already, see distros/*.hpp
    print("{}{}{}\n", DISTRO_FAMILY_COLOR, distro_family(), RESET);
    print("{}{}{}\n", DISTRO_COLOR, distro(), RESET);
    print("{}{}{}\n", CPU_COLOR, cpu(), RESET);
#else
    // Fallback for older compilers/stdlibs (Android/Older Linux)
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << logo_for_distro() << "\n"; // this is colored already, see distros/*.hpp
    std::cout << DISTRO_FAMILY_COLOR << distro_family() << RESET << "\n";
    std::cout << DISTRO_COLOR << distro() << RESET << "\n";
    std::cout << CPU_COLOR << cpu() << RESET << "\n";
#endif
    
    return 0;
}