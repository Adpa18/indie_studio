//
// Created by gaspar_q on 6/4/16.
//

#include "LuaScript.hpp"

Lua::LuaScript::LuaScript()
{
    state = luaL_newstate();
}

Lua::LuaScript::LuaScript(const Lua::LuaScript &script)
{
    *this = script;
}

Lua::LuaScript::~LuaScript()
{
    lua_close(state);
}

Lua::LuaScript &Lua::LuaScript::operator=(const Lua::LuaScript &script)
{
    state = script.state;
    return *this;
}

lua_State *Lua::LuaScript::operator*(void)
{
    return state;
}
