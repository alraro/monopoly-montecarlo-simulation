CXX          = c++
CXXFLAGS     = -Wall -Wextra -Werror -std=c++23
MAKEFLAGS    = -j$(shell nproc)

NAME         = monopoly
MODULE_NAME  = monopoly

OBJDIR       = obj

BASEDIR      = .
BOARDDIR     = board
SQUARESDIR   = squares

# 1. Declarar los directorios de inclusión DESPUÉS de definir las carpetas
INCLUDESDIRS = $(BASEDIR) $(BOARDDIR) $(SQUARESDIR)
INCLUDES     = $(addprefix -I, $(INCLUDESDIRS))

BASESRC      = main.cpp Game.cpp Player.cpp utils.cpp
BASEDEPS     = utils.hpp Game.hpp Player.hpp effectType.hpp rules.hpp

BOARDSRC     = Board.cpp BoardBuilder.cpp BoardFactory.cpp
BOARDDEPS    = Board.hpp BoardBuilder.hpp BoardFactory.hpp

SQUARESSRC   = BaseSquare.cpp CommunitySquare.cpp GoToJailSquare.cpp \
               JailSquare.cpp LuckSquare.cpp ParkingSquare.cpp \
               PropertySquare.cpp StartSquare.cpp
SQUARESDEPS  = BaseSquare.hpp CommunitySquare.hpp GoToJailSquare.hpp \
               JailSquare.hpp LuckSquare.hpp ParkingSquare.hpp \
               PropertySquare.hpp StartSquare.hpp

SRC          = $(addprefix $(BASEDIR)/, $(BASESRC)) \
               $(addprefix $(BOARDDIR)/, $(BOARDSRC)) \
               $(addprefix $(SQUARESDIR)/, $(SQUARESSRC))

DEPS         = $(addprefix $(BASEDIR)/, $(BASEDEPS)) \
               $(addprefix $(BOARDDIR)/, $(BOARDDEPS)) \
               $(addprefix $(SQUARESDIR)/, $(SQUARESDEPS))

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