CXX = g++
FLAGS = -std=c++14
INCLUDE = -Iinclude
WARNING = -Wall -Wextra

SRC := $(wildcard src/*)
HPP := $(wildcard include/*)
OBJ := $(patsubst src/%.cpp, obj/%.o, $(SRC))
DEP := $(patsubst src/%.cpp, dep/%.d, $(SRC))

# SFML Graphics. TODO later.
# LSFML := -lsfml-graphics -lsfml-window -lsfml-system

all: main $(OBJ)

main: $(OBJ) main.cpp
	@echo Creating $@...
	@$(CXX) $(FLAGS) $^ -o $@ $(INCLUDE) $(LSFML) $(WARNING)

obj/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	@echo Creating $@...
	@$(CXX) $(FLAGS) -c $< -o $@ $(INCLUDE) $(WARNING)

dep/%.d: src/%.cpp $(HPP)
	@mkdir -p $(dir $@)
	@$(CXX) $(FLAGS) $< -MM -MG -MP -MF$@ -MT$@ -MT$(@:dep/%.d=obj/%.o) $(INCLUDE)

-include $(DEP)

.PHONY: clear

clear:
	@rm main
	@rm -rf dep
	@rm -rf obj
