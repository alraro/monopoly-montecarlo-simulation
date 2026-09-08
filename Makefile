CXX          = c++
CXXFLAGS     = -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion -Wold-style-cast -std=c++23 -MMD -MP
MAKEFLAGS    = -j$(shell nproc)

ifeq ($(MODE), release)
    # Flags de máximo rendimiento
    CXXFLAGS += -O3 -march=native -flto -fno-exceptions -DNDEBUG
else
    # Flags de desarrollo por defecto
    CXXFLAGS += -O0 -g -fsanitize=address,undefined
endif

NAME         = monopoly
MODULE_NAME  = monopoly

OBJDIR       = obj
BASEDIR      = src

BOARDDIR      = $(BASEDIR)/board
SQUARESDIR    = $(BASEDIR)/squares
PLAYERDIR     = $(BASEDIR)/player
GAMEDIR       = $(BASEDIR)/game
EXTRADIR      = $(BASEDIR)/extra
STRATEGYDIR   = $(BASEDIR)/strategy
LOGGERDIR     = $(BASEDIR)/logger
SIMULATIONDIR = $(BASEDIR)/simulation

INCLUDESDIRS = $(BASEDIR) $(BOARDDIR) $(SQUARESDIR) $(PLAYERDIR) $(GAMEDIR) $(EXTRADIR) $(STRATEGYDIR) $(LOGGERDIR) $(SIMULATIONDIR)
INCLUDES     = $(addprefix -I, $(INCLUDESDIRS))

BASESRC       = main.cpp
BOARDSRC      =
SQUARESSRC    =
PLAYERSRC     =
GAMESRC       = Game.cpp
EXTRASRC      =
STRATEGYSRC   = BasicStrategy.cpp
LOGGERSRC     =
SIMULATIONSRC = Simulation.cpp

# Se filtran elementos vacíos para evitar rutas inválidas
SRC          = $(strip \
               $(addprefix $(BASEDIR)/, $(BASESRC)) \
               $(addprefix $(BOARDDIR)/, $(BOARDSRC)) \
               $(addprefix $(PLAYERDIR)/, $(PLAYERSRC)) \
               $(addprefix $(SQUARESDIR)/, $(SQUARESSRC)) \
               $(addprefix $(GAMEDIR)/, $(GAMESRC)) \
               $(addprefix $(EXTRADIR)/, $(EXTRASRC)) \
               $(addprefix $(LOGGERDIR)/, $(LOGGERSRC)) \
               $(addprefix $(STRATEGYDIR)/, $(STRATEGYSRC)) \
               $(addprefix $(SIMULATIONDIR)/, $(SIMULATIONSRC)))

OBJ          = $(SRC:%.cpp=$(OBJDIR)/%.o)
DEP_FILES    = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo "${MODULE_NAME} compiled successfully!"

# Regla de compilación corregida
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

.PHONY: all clean fclean re