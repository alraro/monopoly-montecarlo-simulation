CXX          = c++
WARNFLAGS    = -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion -Wold-style-cast
CXXFLAGS     = -std=c++23 -MMD -MP $(WARNFLAGS)
LDFLAGS      = -lglfw -lGL -ldl -lpthread
MAKEFLAGS    = -j$(shell nproc)

ifeq ($(MODE), release)
    CXXFLAGS += -O3 -march=native -flto=auto -fno-exceptions -DNDEBUG
    LDFLAGS  += -flto=auto
else
    SANFLAGS := -fsanitize=address,undefined
    CXXFLAGS += -O0 -g $(SANFLAGS)
    LDFLAGS  += $(SANFLAGS)
endif

NAME         = monopoly
MODULE_NAME  = monopoly

OBJDIR       = obj
BASEDIR      = src

BOARDDIR        = $(BASEDIR)/board
SQUARESDIR      = $(BASEDIR)/squares
PLAYERDIR       = $(BASEDIR)/player
GAMEDIR         = $(BASEDIR)/game
EXTRADIR        = $(BASEDIR)/extra
STRATEGYDIR     = $(BASEDIR)/strategy
LOGGERDIR       = $(BASEDIR)/logger
SIMULATIONDIR   = $(BASEDIR)/simulation

INTERFACEDIR    = $(BASEDIR)/interface
IMGUIWRAPPERDIR = $(INTERFACEDIR)/ImGuiWrapper

LIBRARIESDIR    = $(BASEDIR)/libraries
IMGUIDIR        = $(LIBRARIESDIR)/imgui
IMGUIBACKENDDIR = $(IMGUIDIR)/backends

OWN_INC_DIRS = $(BASEDIR) $(BOARDDIR) $(SQUARESDIR) $(PLAYERDIR) $(GAMEDIR) \
               $(EXTRADIR) $(STRATEGYDIR) $(LOGGERDIR) $(SIMULATIONDIR) \
               $(INTERFACEDIR) $(IMGUIWRAPPERDIR)

EXTERNAL_INC_DIRS = $(LIBRARIESDIR) $(IMGUIDIR) $(IMGUIBACKENDDIR)

# 3. Aplicar las banderas correctas a cada grupo
INCLUDES = $(addprefix -I, $(OWN_INC_DIRS)) $(addprefix -isystem , $(EXTERNAL_INC_DIRS))

BASESRC       = main.cpp
BOARDSRC      =
SQUARESSRC    =
PLAYERSRC     =
GAMESRC       = Game.cpp
EXTRASRC      =
STRATEGYSRC   = BasicStrategy.cpp
LOGGERSRC     =
SIMULATIONSRC = Simulation.cpp ConfigParser.cpp
IMGUIWRAPPERSRC = ImGuiMainWindow.cpp

# Fuentes de ImGui corregidas (wildcard entrega ruta completa)
IMGUISRC        = $(wildcard $(IMGUIDIR)/*.cpp)
IMGUIBACKENDSRC = $(IMGUIBACKENDDIR)/imgui_impl_glfw.cpp \
                  $(IMGUIBACKENDDIR)/imgui_impl_opengl3.cpp

SRC          = $(strip \
               $(addprefix $(BASEDIR)/, $(BASESRC)) \
               $(addprefix $(BOARDDIR)/, $(BOARDSRC)) \
               $(addprefix $(PLAYERDIR)/, $(PLAYERSRC)) \
               $(addprefix $(SQUARESDIR)/, $(SQUARESSRC)) \
               $(addprefix $(GAMEDIR)/, $(GAMESRC)) \
               $(addprefix $(EXTRADIR)/, $(EXTRASRC)) \
               $(addprefix $(LOGGERDIR)/, $(LOGGERSRC)) \
               $(addprefix $(STRATEGYDIR)/, $(STRATEGYSRC)) \
               $(addprefix $(SIMULATIONDIR)/, $(SIMULATIONSRC)) \
               $(addprefix $(IMGUIWRAPPERDIR)/, $(IMGUIWRAPPERSRC)) \
               $(IMGUISRC) \
               $(IMGUIBACKENDSRC))

OBJ          = $(SRC:%.cpp=$(OBJDIR)/%.o)
DEP_FILES    = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "${MODULE_NAME} compiled successfully!"

$(OBJDIR)/$(LIBRARIESDIR)/%.o: $(LIBRARIESDIR)/%.cpp
	@mkdir -p $(dir $@)
	@printf "Compiling external %s\n" "$<"
	@$(CXX) -std=c++23 -MMD -MP $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@printf "Compiling ${MODULE_NAME} %s\n" "$<"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEP_FILES)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean
	@$(MAKE) all

bear: fclean
	@bear -- $(MAKE)

release:
	@$(MAKE) MODE=release re

deps:
	@sudo apt-get install bear libglfw3-dev libgl1-mesa-dev

.PHONY: all clean fclean re bear release