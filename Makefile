Q ?= @
CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
BUILD_DIR = output
NWLINK = npx --yes -- nwlink@0.0.19

define object_for
$(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(basename $(1))))
endef

src = \
  src/main.cpp \
  src/game.cpp

objs = $(call object_for,$(src))

CFLAGS = -std=c99 -Os -Wall -ggdb $(shell $(NWLINK) eadk-cflags)
CXXFLAGS = -std=c++11 -fno-exceptions -Os -Wall -ggdb $(shell $(NWLINK) eadk-cflags)
LDFLAGS = -Wl,--relocatable -nostartfiles --specs=nano.specs

.PHONY: build
build: $(BUILD_DIR)/app.nwa

$(BUILD_DIR)/app.nwa: $(objs) $(BUILD_DIR)/icon.o
	@echo "LD      $@"
	$(Q) $(CXX) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/icon.o: src/icon.png
	@echo "ICON    $<"
	$(Q) $(NWLINK) png-icon-o $< $@

$(addprefix $(BUILD_DIR)/,%.o): %.cpp
	@echo "CXX     $<"
	@mkdir -p $(dir $@)
	$(Q) $(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(Q) rm -rf $(BUILD_DIR)
