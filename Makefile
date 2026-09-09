CXX          = c++
WARNFLAGS    = -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion -Wold-style-cast
CXXFLAGS     = -std=c++23 -MMD -MP $(WARNFLAGS)
LDFLAGS      = -lglfw -lGL -ldl -lpthread
MAKEFLAGS    = -j$(shell nproc)

ifeq ($(MODE), release)
    CXXFLAGS += -O3 -march=native -flto -fno-exceptions -DNDEBUG
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

LIBRARIESDIR    = $(BASEDIR)/libraries
IMGUIDIR        = $(LIBRARIESDIR)/imgui
IMGUIBACKENDDIR = $(IMGUIDIR)/backends

INCLUDESDIRS = $(BASEDIR) $(BOARDDIR) $(SQUARESDIR) $(PLAYERDIR) $(GAMEDIR) \
               $(EXTRADIR) $(STRATEGYDIR) $(LOGGERDIR) $(SIMULATIONDIR) \
               $(LIBRARIESDIR) $(IMGUIDIR) $(IMGUIBACKENDDIR) $(INTERFACEDIR)
INCLUDES     = $(addprefix -I, $(INCLUDESDIRS))

BASESRC       = main.cpp
BOARDSRC      =
SQUARESSRC    =
PLAYERSRC     =
GAMESRC       = Game.cpp
EXTRASRC      =
STRATEGYSRC   = BasicStrategy.cpp
LOGGERSRC     =
SIMULATIONSRC = Simulation.cpp ConfigParser.cpp

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

.PHONY: all clean fclean re bear release