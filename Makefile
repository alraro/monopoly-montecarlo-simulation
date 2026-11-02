CXX          := c++
WARNFLAGS    := -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion -Wold-style-cast
CXXFLAGS     := -std=c++23 -MMD -MP $(WARNFLAGS)
LDFLAGS      := -lglfw -lGL -ldl -lpthread
MAKEFLAGS    += -j$(shell nproc)

# Configuración según el modo de compilación
ifeq ($(MODE), release)
    CXXFLAGS += -O3 -march=native -flto=auto -fno-exceptions -DNDEBUG
    LDFLAGS  += -flto=auto
else
    SANFLAGS := -fsanitize=address,undefined
    CXXFLAGS += -O0 -g $(SANFLAGS)
    LDFLAGS  += $(SANFLAGS)
endif

# Nombre del ejecutable
NAME         := monopoly

# Directorios de salida
BUILD_DIR    := build
OBJ_DIR      := $(BUILD_DIR)/obj
BIN_DIR      := $(BUILD_DIR)/bin

# Rutas de inclusión
INCLUDES     := -I. -isystem vendor/imgui -isystem vendor/imgui/backends

# Listado explícito de fuentes del proyecto
MONOPOLY_SRC := \
    monopoly/main.cpp \
    monopoly/game/Game.cpp \
    monopoly/simulation/Simulation.cpp \
    monopoly/simulation/ConfigParser.cpp \
    monopoly/strategy/BasicStrategy.cpp \
    monopoly/interface/imgui/ImGuiMainWindow.cpp

# Fuentes de terceros (estáticas e inmutables)
VENDOR_SRC   := \
    $(wildcard vendor/imgui/*.cpp) \
    vendor/imgui/backends/imgui_impl_glfw.cpp \
    vendor/imgui/backends/imgui_impl_opengl3.cpp

# Conversión a objetos (.o)
MONOPOLY_OBJ := $(MONOPOLY_SRC:%.cpp=$(OBJ_DIR)/%.o)
VENDOR_OBJ   := $(VENDOR_SRC:%.cpp=$(OBJ_DIR)/%.o)

ALL_OBJ      := $(MONOPOLY_OBJ) $(VENDOR_OBJ)
DEPS         := $(ALL_OBJ:.o=.d)

# Regla principal
all: $(BIN_DIR)/$(NAME)

# Ejecutable principal (GUI)
$(BIN_DIR)/$(NAME): $(ALL_OBJ)
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(ALL_OBJ) -o $@ $(LDFLAGS)
	@echo "Construido ejecutable principal: $@"

# Regla de compilación para CÓDIGO PROPIO (aplica advertencias estrictas)
$(OBJ_DIR)/monopoly/%.o: monopoly/%.cpp
	@mkdir -p $(dir $@)
	@printf "Compilando monopoly %s\n" "$<"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Regla de compilación para TERCEROS (silencia advertencias en ImGui)
$(OBJ_DIR)/vendor/%.o: vendor/%.cpp
	@mkdir -p $(dir $@)
	@printf "Compilando vendor %s\n" "$<"
	@$(CXX) -std=c++23 -MMD -MP -w $(INCLUDES) -c $< -o $@

# Reglas utilitarias
clean:
	@rm -rf $(OBJ_DIR)
	@echo "Objetos eliminados."

fclean: clean
	@rm -rf $(BUILD_DIR)
	@echo "Directorio de build eliminado."

re: fclean all

release:
	@$(MAKE) MODE=release re

bear: fclean
	@bear -- $(MAKE) MODE=release all

-include $(DEPS)

.PHONY: all clean fclean re release bear