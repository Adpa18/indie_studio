CC		=	g++

RM		= 	rm -rf

SRC_DIR	=	src/

SRC_INTERFACE_DIR=	Interface/

SRC_IA  =   ia/

LUA_DIRECTORY   =   $(SRC_IA)lua-5.3.2/src

IrrKlangHome	=	IrrKlang/

SRC_VIDEO_DIR=	Video/

IrrlichtHome	=	Irrlicht/irrlicht-1.8.3

SRC		=	$(SRC_DIR)main.cpp						\
			$(SRC_DIR)IrrlichtController.cpp				\
			$(SRC_DIR)AGameObject.cpp					\
			$(SRC_DIR)Player.cpp						\
			$(SRC_DIR)ACharacter.cpp					\
			$(SRC_DIR)Wall.cpp						\
			$(SRC_DIR)BomberMap.cpp						\
			$(SRC_DIR)EventGame.cpp						\
			$(SRC_DIR)ABomb.cpp						\
			$(SRC_DIR)AController.cpp					\
			$(SRC_DIR)MotionController.cpp					\
			$(SRC_DIR)KeysController.cpp					\
			$(SRC_DIR)FireBomb.cpp						\
			$(SRC_DIR)BombContainer.cpp					\
			$(SRC_DIR)GameManager.cpp					\
			$(SRC_DIR)BonusSpeed.cpp					\
			$(SRC_DIR)ABonus.cpp						\
			$(SRC_DIR)BonusPower.cpp					\
			$(SRC_DIR)BonusFireBomb.cpp					\
			$(SRC_DIR)AItem.cpp						\
			$(SRC_DIR)ItemThrow.cpp						\
			$(SRC_DIR)Explosion.cpp						\
			$(SRC_DIR)Texture.cpp						\
			$(SRC_DIR)GameObjectTimeContainer.cpp				\
			$(SRC_DIR)BonusBombPass.cpp					\
			$(SRC_DIR)BonusBiggestMan.cpp					\
			$(SRC_DIR)BonusSmallestMan.cpp					\
			$(SRC_DIR)BonusInvincible.cpp					\
			$(SRC_DIR)TrackerBomb.cpp					\
			$(SRC_DIR)Props.cpp						\
			$(SRC_DIR)Color.cpp						\
			$(SRC_DIR)AtomicBomb.cpp					\
			$(SRC_DIR)FragBomb.cpp						\
			$(SRC_DIR)MiniBomb.cpp						\
			$(SRC_DIR)BonusFragBomb.cpp					\
			$(SRC_DIR)BonusAtomicBomb.cpp					\
			$(SRC_DIR)BonusTrackerBomb.cpp					\
			$(SRC_DIR)MineBomb.cpp						\
			$(SRC_DIR)ItemMineBomb.cpp					\
			$(SRC_DIR)SaveMap.cpp						\
			$(SRC_INTERFACE_DIR)PlayerSelectionBox.cpp 			\
			$(SRC_INTERFACE_DIR)UIEventReceiver.cpp 			\
			$(SRC_INTERFACE_DIR)UIManager.cpp				\
			$(SRC_INTERFACE_DIR)PlayerSelectionBoxContainer.cpp		\
			$(SRC_INTERFACE_DIR)PlayerInfo.cpp				\
			$(SRC_IA)IAPlayer.cpp   					\
			$(SRC_IA)LuaFunctions.cpp					\
			$(SRC_VIDEO_DIR)Video.cpp

OBJ			=	$(SRC:%cpp=%o)

NAME		=	bomberman

BinPath 	=	./

DESTPATH 	=	$(BinPath)/$(NAME)$(SUF)

CPPFLAGS	=	-W -Wall -Wextra -Werror -std=c++11 -pthread -g

CPPFLAGS	+=	 -Wno-unused-parameter -Wno-unused-variable

CPPFLAGS	+=	-I$(IrrlichtHome)/include -I./include -I ./$(SRC_INTERFACE_DIR) -I ./$(IrrKlangHome) -I$(SRC_IA)

#-I/usr/X11R6/include

CPPFLAGS	+=	-O3 -ffast-math

LDFLAGS 	= -lpthread -L $(IrrlichtHome)/lib/$(SYSTEM) -lIrrlicht -L $(IrrKlangHome)linux -L $(LUA_DIRECTORY) -llua -ldl

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
#LDFLAGS += $(IrrKlangHome)Windows/irrKlang.dll
else
LDFLAGS += -L/usr/X11R6/lib$(LIBSELECT) -lGL -lXxf86vm -lXext -lX11 -lXcursor
LDFLAGS += $(IrrKlangHome)linux/libIrrKlang.so
SYSTEM=Linux
endif

ifeq ($(HOSTTYPE), x86_64)
LIBSELECT=64
endif
