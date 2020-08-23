CC = gcc
CC_FLAGS = -fno-builtin-printf -std=gnu99 -g --short-enums -Wall -fmax-errors=1 -Wfatal-errors
LNK_FLAGS = -lm

WebCC = webcc
WebCC_FLAGS = 

# Final binary
BIN = Globals

# Put all auto generated stuff to this build dir.
BUILD_DIR = ./build

SOURCE_DIR = ..

WCExtList=wc png pdf css js apng bmp gif svg webp wav avi bin doc docx gz jar json jsonld \
	mp3 mpeg odp ods odt oga ogv otf ppt pptx rar rtf swf tar ttf txt vsd woff woff2 xls \
	xlsx zip 7z tiff tif ico cur jpg jpeg jfif pjpeg pjp

# List of all the source files.
SOURCE = Common/main.c \
	Common/BittyHTTP/src/SocketsCon.c \
	Common/BittyHTTP/src/WebServer.c \
	Common/WCWebAPI.c \
	Common/FileServer.c \
	Globals/Globals.wc \

INCLUDES = src . ../Common

.PHONY: PreBuild

# All .o files go to build dir.
OBJ = $(SOURCE:%.c=$(BUILD_DIR)/%.o)
$(foreach ext,$(WCExtList),$(eval OBJ := $(OBJ:%.$(ext)=$(BUILD_DIR)/%_$(ext).o)))

WCC = $(filter-out %.c,$(SOURCE))
$(foreach ext,$(WCExtList),$(eval WCC := $(WCC:%.$(ext)=$(BUILD_DIR)/%_$(ext).c)))

# Gcc/Clang will create these .d files containing dependencies.
DEP = $(OBJ:%.o=%.d)
# Include paths with a -I in front of them
CC_INCLUDE = $(INCLUDES:%= -I %)

# Default target named after the binary.
$(BIN) : $(BUILD_DIR)/$(BIN)

# Actual target of the binary - depends on all .o files.
$(BUILD_DIR)/$(BIN) : $(WCC) $(OBJ)
	echo Linking...
	# Create build directories - same structure as sources.
	mkdir -p $(@D)
	# Just link all the object files.
	$(CC) $(CC_FLAGS) $(OBJ) $(LNK_FLAGS) -o $(BIN)

# Include all .d files
-include $(DEP)

# Build target for every single object file.
# The potential dependency on header files is covered
# by calling `-include $(DEP)`.
$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.c
	echo Compiling $(notdir $<)
	mkdir -p $(@D)
	# The -MMD flags additionaly creates a .d file with
	# the same name as the .o file.
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) -MMD -c $< -o $@

$(BUILD_DIR)/%.o : $(BUILD_DIR)/%.c
	echo Compiling $(notdir $<)
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) -MMD -c $< -o $@

define WebCCompile
$(patsubst %.$(1),$(BUILD_DIR)/%_$(1).c,$(filter %.$(1),$(SOURCE))): $(BUILD_DIR)/%_$(1).c: $(SOURCE_DIR)/%.$(1)
	echo WebCompiling "$$(notdir $$<)"
	mkdir -p $$(@D)
	$$(WebCC) $$(WebCC_FLAGS) $$< -o $$@
endef

$(foreach ext,$(WCExtList),$(eval $(call WebCCompile,$(ext))))

#.PHONY : clean
clean :
	# This should remove all generated files.
	-rm $(BIN) $(OBJ) $(DEP) $(WCC)