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

INCLUDESDIRS = $(BASEDIR) $(BOARDDIR) $(SQUARESDIR) $(PLAYERDIR) $(GAMEDIR) $(EXTRADIR) $(STRATEGYDIR) $(LOGGERDIR)
INCLUDES     = $(addprefix -I, $(INCLUDESDIRS))

BASESRC      = main.cpp
BASEDEPS     = 

BOARDSRC     = Board.cpp BoardBuilder.cpp BoardFactory.cpp
BOARDDEPS    = Board.hpp BoardBuilder.hpp BoardFactory.hpp

SQUARESSRC   = BaseSquare.cpp CommunitySquare.cpp GoToJailSquare.cpp \
               JailSquare.cpp LuckSquare.cpp ParkingSquare.cpp \
               PropertySquare.cpp StartSquare.cpp
SQUARESDEPS  = BaseSquare.hpp CommunitySquare.hpp GoToJailSquare.hpp \
               JailSquare.hpp LuckSquare.hpp ParkingSquare.hpp \
               PropertySquare.hpp StartSquare.hpp

PLAYERSRC     = Player.cpp
PLAYERDEPS    = Player.hpp

GAMESRC      = Game.cpp GameStatistics.cpp
GAMEDEPS     = Game.hpp GameStatistics.hpp

EXTRASRC     = utils.cpp
EXTRADEPS    = utils.hpp effects.hpp rules.hpp simulationParams.hpp

STRATEGYSRC  = 
STRATEGYDEPS = Strategy.hpp

LOGGERSRC   = 
LOGGERDEPS  = Logger.hpp

SRC          = $(addprefix $(BASEDIR)/,     $(BASESRC)) \
               $(addprefix $(BOARDDIR)/,    $(BOARDSRC)) \
               $(addprefix $(PLAYERDIR)/,   $(PLAYERSRC)) \
               $(addprefix $(SQUARESDIR)/,  $(SQUARESSRC)) \
               $(addprefix $(GAMEDIR)/,     $(GAMESRC)) \
               $(addprefix $(EXTRADIR)/,    $(EXTRASRC)) \
               $(addprefix $(LOGGERDIR)/,   $(LOGGERSRC)) \
               $(addprefix $(STRATEGYDIR)/, $(STRATEGYSRC)) \

DEPS         = $(addprefix $(BASEDIR)/,     $(BASEDEPS)) \
               $(addprefix $(BOARDDIR)/,    $(BOARDDEPS)) \
               $(addprefix $(PLAYERDIR)/,   $(PLAYERDEPS)) \
               $(addprefix $(SQUARESDIR)/,  $(SQUARESDEPS)) \
               $(addprefix $(GAMEDIR)/,     $(GAMEDEPS)) \
               $(addprefix $(EXTRADIR)/,    $(EXTRADEPS)) \
               $(addprefix $(LOGGERDIR)/,   $(LOGGERDEPS)) \
               $(addprefix $(STRATEGYDIR)/, $(STRATEGYDEPS)) \

# Mapea cualquier src/archivo.cpp a obj/src/archivo.o de forma limpia
OBJ          = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo "${MODULE_NAME} compiled successfully!"

# 2. Regla genérica que captura archivos en subcarpetas
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