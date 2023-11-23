CC = clang
CFLAGS = -std=c18 -D_POSIX_C_SOURCE=200809L
DEBUG_FLAGS = -g -O0 -DDEBUG -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-omit-frame-pointer -W -Wall -Wextra -Werror -Wfatal-errors -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-result -rdynamic
OBJ_DIR = obj
BIN_DIR = bin
SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/verify_my_vote
DEBUG_EXECUTABLE = $(BIN_DIR)/verify_my_vote_debug

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	@echo "\033[1;34mCreating directory for the executable...\033[0m"
	@mkdir -p $(BIN_DIR)
	@echo "\033[1;32mLinking all object files...\033[0m"
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "\033[1;32mExecutable created successfully!\033[0m"

$(DEBUG_EXECUTABLE): $(OBJ)
	@echo "\033[1;34mCreating directory for the debug executable...\033[0m"
	@mkdir -p $(BIN_DIR)
	@echo "\033[1;32mLinking all object files with debug flags...\033[0m"
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $^ -o $@
	@echo "\033[1;32mDebug executable created successfully!\033[0m"

$(OBJ_DIR)/%.o: %.c
	@echo "\033[1;34mCreating directory for object files...\033[0m"
	@mkdir -p $(OBJ_DIR)
	@echo "\033[1;32mCompiling $<...\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(DEBUG_EXECUTABLE)

doc:
	@echo "\033[1;32mGenerating documentation...\033[0m"
	@doxygen Doxyfile
	@echo "\033[1;32mDocumentation generated successfully!\033[0m"

deliver:
	@echo "\033[1;32mCreating delivery zip...\033[0m"
	@zip Daoud_LAMALMI_$(shell date +%F_%H-%M-%S).zip *.c *.h Makefile Doxyfile
	@echo "\033[1;32mDelivery zip created successfully!\033[0m"

clean:
	@echo "\033[1;31mCleaning up object files, executables, documentation, and zip files...\033[0m"
	@rm -rf $(OBJ_DIR) $(BIN_DIR) doc deliver
	@rm -f *.zip
	@echo "\033[1;31mCleanup complete!\033[0m"

.PHONY: all debug doc deliver clean

nothing:
	@echo "\033[1;33mEverything is up to date!\033[0m"
