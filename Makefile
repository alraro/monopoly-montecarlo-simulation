CXX          = c++
CXXFLAGS     = -Wall -Wextra -Werror -std=c++23
MAKEFLAGS    = -j$(shell nproc)

NAME         = monopoly
MODULE_NAME  = monopoly

OBJDIR       = obj

BASEDIR      = src
BOARDDIR     = $(BASEDIR)/board
SQUARESDIR   = $(BASEDIR)/squares
PLAYERDIR    = $(BASEDIR)/player
GAMEDIR      = $(BASEDIR)/game
EXTRADIR     = $(BASEDIR)/extra
STRATEGYDIR  = $(BASEDIR)/strategy
LOGGERDIR    = $(BASEDIR)/logger
SIMULATIONDIR = $(BASEDIR)/simulation

INCLUDESDIRS = $(BASEDIR) $(BOARDDIR) $(SQUARESDIR) $(PLAYERDIR) $(GAMEDIR) $(EXTRADIR) $(STRATEGYDIR) $(LOGGERDIR) $(SIMULATIONDIR)
INCLUDES     = $(addprefix -I, $(INCLUDESDIRS))

BASESRC      = main.cpp
BASEDEPS     = 

BOARDSRC     =
BOARDDEPS    = Board.hpp

SQUARESSRC   = 
SQUARESDEPS  = SquareInfo.hpp Squares.hpp

PLAYERSRC     =
PLAYERDEPS    = Player.hpp PlayerInfo.hpp

GAMESRC      = Game.cpp
GAMEDEPS     = Game.hpp GameStatistics.hpp

EXTRASRC     =
EXTRADEPS    = Dice.hpp Types.hpp effects.hpp rules.hpp simulationParams.hpp

STRATEGYSRC  = BasicStrategy.cpp
STRATEGYDEPS = Strategy.hpp BasicStrategy.hpp

LOGGERSRC   = 
LOGGERDEPS  = Logger.hpp

SIMULATIONSRC  = Simulation.cpp
SIMULATIONDEPS = Simulation.hpp SimulationRules.hpp

SRC          = $(addprefix $(BASEDIR)/,     $(BASESRC)) \
               $(addprefix $(BOARDDIR)/,    $(BOARDSRC)) \
               $(addprefix $(PLAYERDIR)/,   $(PLAYERSRC)) \
               $(addprefix $(SQUARESDIR)/,  $(SQUARESSRC)) \
               $(addprefix $(GAMEDIR)/,     $(GAMESRC)) \
               $(addprefix $(EXTRADIR)/,    $(EXTRASRC)) \
               $(addprefix $(LOGGERDIR)/,   $(LOGGERSRC)) \
               $(addprefix $(STRATEGYDIR)/, $(STRATEGYSRC)) \
               $(addprefix $(SIMULATIONDIR)/, $(SIMULATIONSRC))

DEPS         = $(addprefix $(BASEDIR)/,     $(BASEDEPS)) \
               $(addprefix $(BOARDDIR)/,    $(BOARDDEPS)) \
               $(addprefix $(PLAYERDIR)/,   $(PLAYERDEPS)) \
               $(addprefix $(SQUARESDIR)/,  $(SQUARESDEPS)) \
               $(addprefix $(GAMEDIR)/,     $(GAMEDEPS)) \
               $(addprefix $(EXTRADIR)/,    $(EXTRADEPS)) \
               $(addprefix $(LOGGERDIR)/,   $(LOGGERDEPS)) \
               $(addprefix $(STRATEGYDIR)/, $(STRATEGYDEPS)) \
               $(addprefix $(SIMULATIONDIR)/, $(SIMULATIONDEPS))

OBJ          = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo "${MODULE_NAME} compiled successfully!"

$(OBJDIR)/%.o: %.cpp $(DEPS)
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	@printf "Compiling ${MODULE_NAME} %s\n" "$<"

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean .WAIT all

.PHONY: all clean fclean re