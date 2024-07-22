# Compiler and linker
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Microcontroller specific settings
MCU = atmega328pb
F_CPU = 16000000UL

# Programmer settings
PROGRAMMER = xplainedmini

# Define the target executable name and build directory
TARGET_NAME = target
BUILD_DIR = build
TARGET = $(BUILD_DIR)/${TARGET_NAME}.elf
HEX = $(BUILD_DIR)/${TARGET_NAME}.hex

# Define the source directory
SRC_DIRS ?= \
	src \
	lib/EmbeddedCommon/src

# Find all source files in the source directory and subdirectories
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Include directories for headers
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Compiler flags
CFLAGS += -mmcu=$(MCU) -DF_CPU=$(F_CPU)
CPPFLAGS += $(INC_FLAGS) -MMD -MP -Wall -Wextra -Wcast-qual -Werror
LDFLAGS := -mmcu=$(MCU)
#LDLIBS := -lstdc++ -lCppUTest -lCppUTestExt -lm
LDLIBS :=

# Build dependencies
BUILD_DEPS += $(MAKEFILE_LIST)

# Main target
.PHONY: all 

all: $(HEX)

# Run target
.PHONY: run
run: all
	@echo Running $(TARGET)...
	@$(TARGET)

# Linking target
$(TARGET): $(OBJS)
	@echo Linking $@...
	@mkdir -p $(dir $@)
	@$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

# Convert ELF to HEX
$(HEX): $(TARGET)
	@$(OBJCOPY) -O ihex $< $@
	@echo "Generating $@"

# Compiling C source files
$(BUILD_DIR)/%.c.o: %.c $(BUILD_DEPS)
	@echo Compiling $<...
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Flash target to program the microcontroller
.PHONY: flash
flash: $(HEX)
	@echo "Flashing $(HEX) to device"
	@$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -U flash:w:$(HEX)

# Clean target
.PHONY: clean
clean:
	@echo Cleaning...
	@rm -rf $(BUILD_DIR)

# Include dependency files
-include $(DEPS)
