//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------

#ifndef DATA_H
#define DATA_H

#include "MugenEngine.h"

#include <json.hpp> // Library JSON Manipulation !
using json = nlohmann::json;

extern "C" // Standard LUA Library
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <selene.h> // Wrapper C++ LUA !


class Data
{
    public:
        Data();
        virtual ~Data();

        // --- JSON File Manager !
        json loadJsonFile(std::string const filename);
        void saveJsonFile(std::string const filename, nlohmann::json data);

        // --- LUA method !
        void PrintTable(lua_State *L);

    protected:

    private:
};

#endif // DATA_H
