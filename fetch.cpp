#include <string_view>
#include "platforms/shared.cpp"

using namespace std;

#if defined(__linux__) && !defined(__ANDROID__)
    #define IS_NON_ANDROID_LINUX 1
#endif

#ifdef IS_NON_ANDROID_LINUX
    #include <string>
    #include "platforms/linux.cpp"
    #include "ascii/linux.hpp"
    #include "ascii/arch.hpp"
    #include "ascii/debian.hpp"
#endif

#ifdef __ANDROID__
    #include <print>
    #include "platforms/android.cpp"
    #include "ascii/android.hpp"
#endif

struct LogoRule {
    initializer_list<string_view> distros;
    string_view logo;
};

// customize the return values. see definitions in ascii/*.hpp
string_view logo_for_distro() {
#ifdef IS_NON_ANDROID_LINUX
    static const LogoRule LOGO_RULES[] = {
        {{"Arch"}, archlogo_fullblock},
        {{"Debian", "Ubuntu", "Mint", "Pop"}, debianlogo_swirl},
        // {{"Fedora", "Red Hat", "CentOS", "Rocky", "Alma"}, redhat_logo},
        // {{"SUSE"}, suse_logo},
        // {{"Gentoo"}, gentoo_logo},
    };
    const string family = distro_family();
    const string name = distro();

    for (const LogoRule& rule : LOGO_RULES) {
        for (string_view pattern : rule.distros) {
            if (family.find(pattern) != string::npos ||
                name.find(pattern) != string::npos) {
                return rule.logo;
            }
        }
    }

    // generic linux mascot
    return linuxlogo_tux_official;
#endif

#ifdef __ANDROID__
    return androidlogo_dot;
#endif

    return "";
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
#define KERNEL_COLOR        "\x1b[38;2;175;95;255m"  // purple
#define UPTIME_COLOR        "\x1b[38;2;0;255;127m"  // Spring Green
#define RESET "\x1b[0m"

int main() {
    #ifdef __ANDROID__
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);

        // print on android doesn't work with -march=native
        cout << logo_for_distro() << "\n"
            << DISTRO_FAMILY_COLOR << distro_family() << RESET << "\n"
            << DISTRO_COLOR << distro() << RESET << "\n"
            << CPU_COLOR << cpu() << RESET << "\n"
            << KERNEL_COLOR << kernelver() << RESET << "\n"
            << UPTIME_COLOR << uptime() << RESET << "\n";
    #endif

    #ifdef IS_NON_ANDROID_LINUX
        print(
            "{}{}\n"
            "{}{}{}\n"
            "{}{}{}\n"
            "{}{}{}\n"
            "{}{}{}\n"
            "{}{}{}\n",
            logo_for_distro(), RESET,
            DISTRO_FAMILY_COLOR, distro_family(), RESET,
            DISTRO_COLOR, distro(), RESET,
            CPU_COLOR, cpu(), RESET,
            KERNEL_COLOR, kernelver(), RESET,
            UPTIME_COLOR, uptime(), RESET
        );
    #endif

    return 0;
}