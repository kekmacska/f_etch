# Compiler and Linker
CXX = clang++
LD = lld

# Output binary
TARGET = f_etch

# Source files
SRCS = fetch.cpp

# Optimization & Architecture Flags
OPT_FLAGS = -O3 -march=native -mtune=native
ALIGN_FLAGS = -falign-functions=32 -falign-loops=32
MATH_FLAGS = -fno-math-errno -fno-trapping-math
SECURITY_FLAGS = -fno-semantic-interposition -fomit-frame-pointer -fno-plt
STDLIB_FLAGS = -fstrict-aliasing -fno-rtti -fno-exceptions
LINKER_OPT = -fmerge-all-constants -ffunction-sections -fdata-sections -fvisibility=hidden -fstrict-vtable-pointers
DEBUG_STRIP = -fno-asynchronous-unwind-tables

# Combined CXX Flags
CXXFLAGS = $(OPT_FLAGS) $(ALIGN_FLAGS) $(MATH_FLAGS) $(SECURITY_FLAGS) \
           -pipe -flto -Wall -Wno-unused $(STDLIB_FLAGS) $(LINKER_OPT) $(DEBUG_STRIP)

# Linker Flags
LDFLAGS = -fuse-ld=$(LD) -Wl,--icf=safe -Wl,--gc-sections -Wl,-O3 -flto -fno-plt

# Default target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)
	@printf "\nBuilt $(TARGET)\n"

# Clean target
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean