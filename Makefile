CC		=	g++

RM		= 	rm -rf

SRC_DIR	=	src/

IrrlichtHome	=	Irrlicht/irrlicht-1.8.3

SRC		=	$(SRC_DIR)main.cpp					\
			$(SRC_DIR)IrrlichtController.cpp	\
			$(SRC_DIR)AGameObject.cpp			\
			$(SRC_DIR)Player.cpp				\
			$(SRC_DIR)ACharacter.cpp			\
			$(SRC_DIR)Wall.cpp					\
			$(SRC_DIR)BomberMap.cpp				\
			$(SRC_DIR)EventGame.cpp				\
			$(SRC_DIR)ABomb.cpp				    \
			$(SRC_DIR)AController.cpp			\
			$(SRC_DIR)MotionController.cpp		\
			$(SRC_DIR)KeysController.cpp		\
			$(SRC_DIR)FireBomb.cpp			    \
			$(SRC_DIR)BombContainer.cpp		    \

OBJ			=	$(SRC:%cpp=%o)

NAME		=	bomberman

BinPath 	=	./

DESTPATH 	=	$(BinPath)/$(NAME)$(SUF)

CPPFLAGS	=	-W -Wall -Wextra -Werror -std=c++11 -pthread -g

CPPFLAGS	+=	 -Wno-unused-parameter -Wno-unused-variable

CPPFLAGS	+=	-I$(IrrlichtHome)/include -I./include

#-I/usr/X11R6/include

CPPFLAGS	+=	-O3 -ffast-math

LDFLAGS 	= -lpthread -L$(IrrlichtHome)/lib/$(SYSTEM) -lIrrlicht

%.o : %.cpp
	@echo -e "Compiling $<"
	@$(CC) -c $(CPPFLAGS) $< -o $@

$(NAME)	:	$(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $(DESTPATH)
	@echo -e "\033[0;33m${NAME} Compiled\033[0;00m"

all	:	$(NAME)

clean 	:
	@echo -e "\033[0;31mRemoving Objects\033[0;00m"
	@$(RM) $(OBJ)

fclean	:	clean
	@echo -e "\033[0;31mRemoving ${NAME}\033[0;00m"
	@$(RM) $(NAME)

re		: fclean all

.PHONY	: all clean fclean re

ifeq ($(OS),Windows_NT)
SYSTEM=Win32-gcc
SUF=.exe
CPPFLAGS += -D_IRR_STATIC_LIB_
LDFLAGS += -lgdi32 -lwinspool -lcomdlg32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32 -lopengl32
LDFLAGS += -lopengl32 -lm -static-libstdc++
else
LDFLAGS += -L/usr/X11R6/lib$(LIBSELECT) -lGL -lXxf86vm -lXext -lX11 -lXcursor
SYSTEM=Linux
endif

ifeq ($(HOSTTYPE), x86_64)
LIBSELECT=64
endif
