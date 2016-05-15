//
// Created by gaspar_q on 5/6/16.
//

#ifndef CPP_INDIE_STUDIO_LUAHANDLER_HPP
#define CPP_INDIE_STUDIO_LUAHANDLER_HPP

# include <string>
#include <stdexcept>
#include <iostream>
#include "LuaClass.hpp"

extern "C"
{
#include "lua-5.3.2/src/lua.h"
#include "lua-5.3.2/src/lualib.h"
#include "lua-5.3.2/src/lauxlib.h"
}

namespace Lua
{
    /**
     * \brief LuaException for lua handler errors
     */
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

    /**
     * \brief LuaHandler that allow the user use functions of a Lua script in C++
     */
    class LuaHandler
    {
    public:
        /**
         * \brief The constructor of the handler
         * \param script The script to execute, if you enter a script it will be executed in this constructor. Use set script if you dont want this happen
         * \param methodName The function to call in the script
         */
        LuaHandler(std::string const &script = "", std::string const &methodName = "") :
                state(acquireState()),
                script(script),
                toCall(methodName)
        {
            setScript(script);
        }
        /**
         * \brief Copy constructor
         */
        LuaHandler(LuaHandler const &ref)
        {
            *this = ref;
        }
        /**
         * \brief Copy operator. Will copy the state, the method to call and the script to execute
         * \param ref The reference to copy
         * \return A Reference on this
         */
        LuaHandler  &operator=(LuaHandler const &ref)
        {
            state = ref.state;
            toCall = ref.toCall;
            setScript(ref.script);
            return (*this);
        }
        /**
         * \brief Handler destructor, if you have any idea, call me
         */
        ~LuaHandler()
        {

        }

    public:
        /**
         * \brief Access operator that will allow you to choose a method to call
         * \param methodname The function name you choose to select
         * \return A reference on this pointer
         */
        LuaHandler  &operator[](const std::string &methodname)
        {
            toCall = methodname;
            return (*this);
        }
        /**
         * \brief Template method for calling the handler choosen function
         * \param args The arguments needed by the method
         * \return An integer corresponding to the lua function return (TODO add more polymorphism)
         */
        template <typename ... Types>
        int     operator()(Types ... args)
        {
            int result;
            lua_getglobal(state, toCall.c_str());
            int dum[sizeof...(Types)] = { (pushArgs(args))... };

            lua_call(state, sizeof...(Types), 1);
            result = lua_tointeger(state, -1);
            lua_pop(state, 1);
            return result;
        }
        /**
         * \brief Set and execute the script represented by scriptname
         * \param scriptname The name of the script to execute
         */
        void setScript(std::string const &scriptname)
        {
            if (!scriptname.empty())
                luaL_dofile(state, scriptname.c_str());
            script = scriptname;
        }
        /**
         * \brief A simple getter on the lua state used by the handler
         * \return The lua state used
         */
        lua_State   *getState(void)
        {
            return state;
        }

        /**
         * \brief Thoses functions are polymorphisms for arguments push on the lua stack before calling a method
         */
    private:
        /**
         * \brief Polymorphism on no argument
         */
        int    pushArgs(void)
        {
            return 0;
        }
        /**
         * \brief Polymorphism on integer argument
         * \param topush The argument to push
         */
        int    pushArgs(int topush)
        {
            lua_pushinteger(state, static_cast<lua_Integer >(topush));
            return 0;
        }
        /**
         * \brief Polymorphism on double argument
         * \param topush The argument to push
         */
        int pushArgs(double topush)
        {
            lua_pushnumber(state, topush);
            return 0;
        }
        /**
         * \brief Polymorphism on boolean argument
         * \param topush The argument to push
         */
        int pushArgs(bool topush)
        {
            lua_pushboolean(state, topush);
            return 0;
        };
        /**
         * \brief Polymorphism on string argument
         * \param topush The argument to push
         */
        int pushArgs(const char *topush)
        {
            lua_pushstring(state, topush);
            return 0;
        }
        /**
         * \brief Polymorphism on user data argument. In that case it is recommended to use LuaClass object '&' operator
         * \param topush The argument to push
         */
        int pushArgs(void *topush)
        {
            lua_pushlightuserdata(state, &topush);
            return 0;
        }

    private:
        lua_State   *state;
        std::string script;
        std::string toCall;
    };
}

#endif //CPP_INDIE_STUDIO_LUAHANDLER_HPP
