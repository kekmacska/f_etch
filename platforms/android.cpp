#include <string>
#include <sys/system_properties.h>
#include <android/api-level.h>
#include <cstdint>
#include <string_view>

using namespace std;

constexpr string_view codenames[] = {
  "Base",                "Base11",
  "Cupcake",             "Donut",
  "Eclair",              "Eclair01",
  "EclairMr1",           "Froyo",
  "Gingerbread",         "GingerbreadMr1",
  "Honeycomb",           "HoneycombMr1",
  "HoneycombMr2",        "IceCreamSandwich",
  "IceCreamSandwichMr1", "JellyBean",
  "JellyBeanMr1",        "JellyBeanMr2",
  "Kitkat",              "KitkatWatch",
  "Lollipop",            "LollipopMr1",
  "M",                   "N",
  "NMr1",                "O",
  "OMr1",                "P",
  "Q",                   "R",
  "S",                   "Sv2",
  "Tiramisu",            "UpsideDownCake",
  "VanillaIceCream",     "Baklava",
  "Cinnamon Bun"
}; // from Android 1 to 17

string android_codename() {
#if __ANDROID_API__ >= 26
    if (const prop_info* info = __system_property_find("ro.build.version.codename")) {
        string value;
        // see https://stackoverflow.com/questions/26722040/replacement-for-system-property-get-in-android-l-ndk #1
        __system_property_read_callback(
            info,
            [](void* cookie, const char*, const char* value, uint32_t) {
                *static_cast<string*>(cookie) = value;
            },
            &value
        );

        if (!value.empty()) {
            return value;
        }
    }
#endif

    // else if new API doesn"t work
    char value[PROP_VALUE_MAX] = {};
    uint8_t length = __system_property_get("ro.build.version.codename", value);
    return length > 0 ? string(value, length) : "";
}

string distro_family() {
    return "Android";
}

string distro() {
    const int8_t api = android_get_device_api_level();
    return "Android " + to_string(api) + " " + string(codenames[api - 1]);
}

string android_cpu() {
    char value[PROP_VALUE_MAX] = {};
    uint8_t len = __system_property_get("ro.soc.model", value);
    return len>0 ? string(value, len) : "unknown";
}