# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Iinclude -I/usr/include/taglib -I/usr/include/ # Include header files from the include directory
LDFLAGS = -ltag -lSDL2 -lSDL2_mixer

# Directories
TARGET_DIR = build
SRC_DIR = src
INCLUDE_DIR = include

# Executable name
TARGET = $(TARGET_DIR)/my_program

# OS-specific settings
ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXEC = $(TARGET)
    MKDIR = if not exist $(TARGET_DIR) mkdir $(TARGET_DIR)
else
    RM = rm -f
    EXEC = $(TARGET)
    MKDIR = mkdir -p $(TARGET_DIR)
endif

# Find all .cpp files in src/ and create a list of .o files in $(TARGET_DIR)
SRCS = $(shell find $(SRC_DIR) -name "*.cpp")
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(TARGET_DIR)/%.o,$(SRCS))

# List of directories that need to be created under build/
BUILD_DIRS = $(sort $(dir $(OBJS)))

# Default rule to build the project
all: check_dir $(TARGET)

# Create necessary directories under $(TARGET_DIR)
check_dir:
	@mkdir -p $(BUILD_DIRS)

# Link object files to create the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

# Rule to compile .cpp files into .o files
$(TARGET_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the program
run:
	$(EXEC)

# Clean up object files and the executable
clean:
	$(RM) $(TARGET_DIR)/*.o $(TARGET)

# Phony targets to avoid conflicts with files named "clean" or "all"
.PHONY: all clean run check_dir
