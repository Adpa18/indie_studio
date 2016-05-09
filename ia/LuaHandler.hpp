//
// Created by gaspar_q on 5/6/16.
//

#ifndef CPP_INDIE_STUDIO_LUAHANDLER_HPP
#define CPP_INDIE_STUDIO_LUAHANDLER_HPP

# include <string>
#include <stdexcept>

extern "C"
{
#include "lua-5.3.2/src/lua.h"
#include "lua-5.3.2/src/lualib.h"
#include "lua-5.3.2/src/lauxlib.h"
}

namespace Lua
{
    class LuaException : std::runtime_error
    {
    public:
        LuaException(std::string const &err) :
                std::runtime_error(err)
        {
        }
        virtual ~LuaException() throw()
        {

        }
    };

    class LuaHandler
    {
    public:
        LuaHandler(std::string const &script = "") :
                scriptname(script)
        {
            state = luaL_newstate();
            luaL_openlibs(state);
            luaL_dofile(state, scriptname.c_str());
        }
        LuaHandler(LuaHandler const &ref)
        {
            *this = ref;
        }
        LuaHandler  &operator=(LuaHandler const &)
        {
            return (*this);
        }
        ~LuaHandler()
        {

        }

    public:
        LuaHandler  &operator[](const std::string &methodname)
        {
            lua_getglobal(state, methodname.c_str());
            return (*this);
        }
        template <typename ... Types>
        int     operator()(Types ... args)
        {
            int result;
            int dum[sizeof...(Types)] = { (pushArgs(args))... };

            lua_call(state, sizeof...(Types), 1);
            result = lua_tointeger(state, -1);
            lua_pop(state, 1);
            return result;
        }

    private:
        int    pushArgs(void)
        {
            return 0;
        }
        int    pushArgs(int topush)
        {
            lua_pushnumber(state, topush);
            return 0;
        }
        int pushArgs(double topush)
        {
            lua_pushnumber(state, topush);
            return 0;
        }
        int pushArgs(bool topush)
        {
            lua_pushboolean(state, topush);
            return 0;
        };
        int pushArgs(const char *topush)
        {
            lua_pushstring(state, topush);
            return 0;
        }

    private:
        int         nbofargs;
        lua_State   *state;
        std::string scriptname;
    };
}

#endif //CPP_INDIE_STUDIO_LUAHANDLER_HPP
