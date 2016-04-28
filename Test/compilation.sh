#!/bin/bash

g++ *.cpp ../src/Collider.cpp ../src/ACharacter.cpp ../src/AGameObject.cpp ../src/EventGame.cpp ../src/IrrlichtController.cpp ../src/Player.cpp -I ../include -I ../Irrlicht/irrlicht-1.8.3/include -I /usr/X11R6/include -L ../Irrlicht/irrlicht-1.8.3/lib/Linux -lIrrlicht -L /usr/X11R6/lib64 -lGL -lXxf86vm -lXext -lX11 -lXcursor -std=c++11
