//
// Created by gaspar_q on 5/6/16.
//

#include <iostream>
#include "LuaHandler.hpp"

int main()
{
    Lua::LuaHandler  handler("./iaBehaviour.lua");

    std::cout << handler["computeIA"](2, 3) << std::endl;
    std::cout << handler["testargs"](2, 2.4, true, "On fait des test") << std::endl;
    /*lua_State   *state;

    state = luaL_newstate();
    luaL_openlibs(state);
    luaL_dofile(state, "./iaBehaviour.lua");
    lua_getglobal(state, "computeIA");
    lua_pushnumber(state, 4);
    lua_pushnumber(state, 6);
    lua_call(state, 2, 2);
    std::cout << lua_tointeger(state, -1) << std::endl;
    lua_pop(state, 1);
    std::cout << lua_tointeger(state, -1) << std::endl;
    lua_close(state);*/
    return (0);
}