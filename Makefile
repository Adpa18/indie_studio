CC		=	g++

RM		= 	rm -rf

SRC_DIR	=	src/

IrrlichtHome	=	Irrlicht/irrlicht-1.8.3

SRC		=	$(SRC_DIR)main.cpp					\
			$(SRC_DIR)IrrlichtController.cpp	\
			$(SRC_DIR)AGameObject.cpp			\
			$(SRC_DIR)ACharacter.cpp			\

OBJ			=	$(SRC:%cpp=%o)

NAME		=	bomberman

BinPath 	=	./

DESTPATH 	=	$(BinPath)/$(NAME)$(SUF)

CPPFLAGS	=	-W -Wall -Wextra -Werror -std=c++11

CPPFLAGS	=	-I$(IrrlichtHome)/include -I/usr/X11R6/include

CPPFLAGS	+=	-O3 -ffast-math

LDFLAGS 	+= -L$(IrrlichtHome)/lib/$(SYSTEM) -lIrrlicht

%.o : %.cpp
	@echo -e "Compiling $<"
	@$(CC) -c $(CPPFLAGS) $< -o $@

$(NAME)	:	$(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $(DESTPATH)
	@echo -e "\e[33m${NAME} Compiled\e[00m"

all	:	$(NAME)

clean 	:
	@echo -e "\e[31mRemoving Objects\e[00m"
	@$(RM) $(OBJ)

fclean	:	clean
	@echo -e "\e[31mRemoving ${NAME}\e[00m"
	@$(RM) $(NAME)

re		: fclean all

.PHONY	: all clean fclean re

ifeq ($(OS),Windows_NT)
SYSTEM=Win32-gcc
SUF=.exe
CPPFLAGS += -D_IRR_STATIC_LIB_ #static
LDFLAGS += -lgdi32 -lwinspool -lcomdlg32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32 -lopengl32 #static
LDFLAGS += -lopengl32 -lm
else
LDFLAGS += -L/usr/X11R6/lib$(LIBSELECT) -lGL -lXxf86vm -lXext -lX11 -lXcursor
SYSTEM=Linux
endif

ifeq ($(HOSTTYPE), x86_64)
LIBSELECT=64
endif
