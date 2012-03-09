/**
@file Server.cpp

Contiene la implementaci�n de la clase CServer, Singleton que se encarga de
la gesti�n de los scripts del juego.

@see ScriptManager::CServer

@author Alberto Plaza
@date Marzo, 2012
*/

#include "Server.h"

// Inclu�mos las cabedceras de Lua.
// Como es c�digo C (no C++), hay que indicarselo al
// compilador para que asuma el convenio de nombres
// de C en el c�digo objeto.
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>  // Para inicializar la librer�a base de Lua
}

#pragma warning( disable: 4251 )
#include <luabind\luabind.hpp>

#include <cassert>
#include <stdio.h>
#include <iostream>
#include <sstream>

namespace ScriptManager {

	CServer* CServer::_instance = 0;

	//--------------------------------------------------------

	CServer::CServer()
	{
		_instance = this;
		_lua = NULL;

	} // CServer

	//--------------------------------------------------------

	CServer::~CServer()
	{
		_instance = 0;

	} // ~CServer
	
	//--------------------------------------------------------

	bool CServer::Init()
	{
		assert(!_instance && "Segunda inicializaci�n de ScriptManager::CServer no permitida!");

		new CServer();

		if (!_instance->open())
		{
			Release();
			return false;
		}

		return true;

	} // Init

	//--------------------------------------------------------

	void CServer::Release()
	{
		assert(_instance && "ScriptManager::CServer no est� inicializado!");

		if(_instance)
		{
			_instance->close();
			delete _instance;
		}

	} // Release

	//--------------------------------------------------------

	bool CServer::open()
	{
		// Obtengo el estado de lua (inicializaci�n de lua)
		_lua = luaL_newstate();

		if (!_lua)
			return false;

		// Abro las librer�as de lua (segunda parte de la inicializaci�n)
		luaL_openlibs(_lua);

		// Abrimos la librer�a base para hacer disponible
		// print() en Lua.
		luaopen_base(_lua);

		// Activamos luabind en el int�rprete
		luabind::open(_lua);

		return true;

	} // open

	//--------------------------------------------------------

	void CServer::close() 
	{
		if (_lua)
			lua_close(_lua);

	} // close

	//---------------------------------------------------------

	bool CServer::loadExeScript(const char *script)
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Busco si el script ya lo he cargado anteriormente.
		bool exists = false;

		for (TScriptList::iterator it = _scriptList.begin(); it != _scriptList.end(); it++)
			exists = exists || (script == it._Ptr->_Myval);

		// Si ya lo he cargado muestro un mensaje de error, salgo y devuelvo false.
		if (exists)
		{
			std::cout << "ERROR DE LUA! - Error al cargar el fichero de script \"" << script << "\". Este fichero ya se ha cargado anteriormente." << std::endl;

			return false;
		}

		// Cargo el script. Si la carga ha ido bien, me lo guardo.
		if (loadScript(script, false))
			_scriptList.push_back(script);
		else
			return false;

		// Ejecuto el script
		if (!executeLastLoadScript(script))
			return false;

		return true;

	} // loadExeScript

	//---------------------------------------------------------

	bool CServer::executeScript(const char *script)
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Cargo el script en modo inmediato.
		if (!loadScript(script, true))
			return false;

		// Ejecuto el script
		if (!executeLastLoadScript(script))
			return false;

		return true;
	
	} // executeScript

	//---------------------------------------------------------

	void CServer::reloadScripts()
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		for (TScriptList::iterator it = _scriptList.begin(); it != _scriptList.end(); it++)
		{
			if (loadScript(it._Ptr->_Myval, false))
				if (executeLastLoadScript(it._Ptr->_Myval))
				{
					std::cout << std::endl;
					std::cout << "Fichero \"" << it._Ptr->_Myval << "\" cargado y ejecutado correctamente" << std::endl;
					std::cout << std::endl;
				}
		}
	
	} // reloadScripts

	//---------------------------------------------------------

	int CServer::getGlobal(const char *name, int defaultValue)
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Obtengo la variable global por el nombre.
		luabind::object obj = luabind::globals(_lua)[name];

		// Hago gesti�n de errores para asegurarme de que la variable existe y es del tipo correcto.
		if (!obj.is_valid() || (luabind::type(obj) != LUA_TNUMBER))
		{
			std::cout << "ERROR DE LUA! - La variable num�rica \"" << name << "\" a la que se est� intentando acceder no existe en ning�n script de lua o no es de tipo num�rico." << std::endl;

			return defaultValue;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++.
		return luabind::object_cast<int>(obj);

	} // getGlobal(int)

	//---------------------------------------------------------

	bool CServer::getGlobal(const char *name, bool &error)
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Obtengo la variable global por el nombre.
		luabind::object obj = luabind::globals(_lua)[name];

		// Hago gesti�n de errores para asegurarme de que la variable existe y es del tipo correcto.
		if (!obj.is_valid() || (luabind::type(obj) != LUA_TBOOLEAN))
		{
			std::cout << "ERROR DE LUA! - La variable booleana \"" << name << "\" a la que se est� intentando acceder no existe en ning�n script de lua o no es de tipo booleana." << std::endl;

			error = true;
			return false;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++. Y actualizo la variable de error.
		error = false;
		return luabind::object_cast<bool>(obj);
		
	} // getGlobal(bool)

	//---------------------------------------------------------

	const char *CServer::getGlobal(const char *name, const char *defaultValue)
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Obtengo la variable global por el nombre.
		luabind::object obj = luabind::globals(_lua)[name];

		// Hago gesti�n de errores para asegurarme de que la variable existe y es del tipo correcto.
		if (!obj.is_valid() || (luabind::type(obj) != LUA_TSTRING))
		{
			std::cout << "ERROR DE LUA! - La variable de tipo cadena \"" << name << "\" a la que se est� intentando acceder no existe en ning�n script de lua o no es de tipo cadena." << std::endl;

			return defaultValue;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++.
		return luabind::object_cast<const char*>(obj);
		
	} // getGlobal(char*)

	//---------------------------------------------------------

	int CServer::getField(const char *table, const char *field, int defaultValue)
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Obtengo la tabla.
		luabind::object tabla = luabind::globals(_lua)[table];

		// Compruebo que la tabla existe y es del tipo correcto.
		if (!tabla.is_valid() || (luabind::type(tabla) != LUA_TTABLE))
		{
			std::cout << "ERROR DE LUA! - La tabla \"" << table << "\" a la que se est� intentando acceder no existe o no es de tipo tabla." << std::endl;
			
			return defaultValue;
		}

		// Obtengo el campo de la tabla.
		luabind::object valor = tabla[field];

		// Compruebo que el campo de la tabla existe y es del tipo correcto.
		if (!valor.is_valid() || (luabind::type(valor) != LUA_TNUMBER))
		{
			std::cout << "ERROR DE LUA! - No existe ning�n campo \"" << field << "\" en la tabla \"" << table << "\" o no es de tipo entero." << std::endl;
			
			return defaultValue;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++.
		return luabind::object_cast<int>(valor);
		
	} // getField(int)

	//---------------------------------------------------------

	bool CServer::getField(const char *table, const char *field, bool &error)
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Obtengo la tabla.
		luabind::object tabla = luabind::globals(_lua)[table];

		// Compruebo que la tabla existe y es del tipo correcto.
		if (!tabla.is_valid() || (luabind::type(tabla) != LUA_TTABLE))
		{
			std::cout << "ERROR DE LUA! - La tabla \"" << table << "\" a la que se est� intentando acceder no existe o no es de tipo tabla." << std::endl;
			
			error = true;
			return false;
		}

		// Obtengo el campo de la tabla.
		luabind::object valor = tabla[field];

		// Compruebo que el campo de la tabla existe y es del tipo correcto.
		if (!valor.is_valid() || (luabind::type(valor) != LUA_TBOOLEAN))
		{
			std::cout << "ERROR DE LUA! - No existe ning�n campo \"" << field << "\" en la tabla \"" << table << "\" o no es de tipo booleano." << std::endl;
			
			error = true;
			return false;;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++.
		error = false;
		return luabind::object_cast<bool>(valor);
		
	} // getField(bool)

	//---------------------------------------------------------

	const char *CServer::getField(const char *table, const char *field, const char *defaultValue)
	{
		assert(_lua && "No se ha hecho la inicializaci�n de lua");

		// Obtengo la tabla.
		luabind::object tabla = luabind::globals(_lua)[table];

		// Compruebo que la tabla existe y es del tipo correcto.
		if (!tabla.is_valid() || (luabind::type(tabla) != LUA_TTABLE))
		{
			std::cout << "ERROR DE LUA! - La tabla \"" << table << "\" a la que se est� intentando acceder no existe o no es de tipo tabla." << std::endl;
			
			return defaultValue;
		}

		// Obtengo el campo de la tabla.
		luabind::object valor = tabla[field];

		// Compruebo que el campo de la tabla existe y es del tipo correcto.
		if (!valor.is_valid() || (luabind::type(valor) != LUA_TSTRING))
		{
			std::cout << "ERROR DE LUA! - No existe ning�n campo \"" << field << "\" en la tabla \"" << table << "\" o no es de tipo cadena." << std::endl;
			
			return defaultValue;
		}

		// Devuelvo la variable haciendo casting de tipo para adecuar la variable de lua a nuestro C++.
		return luabind::object_cast<const char*>(valor);
		
	} //getField(char*)

	//---------------------------------------------------------

	bool CServer::loadScript(const char *script, bool inmediate)
	{
		// Completo la ruta del script.
		std::stringstream filename;
		filename << "media\\scripts\\" << script << ".lua";

		// Cargo el fichero de script dependiendo del par�metro booleano.
		int errorType = 0;

		if (inmediate)
			errorType = luaL_loadstring(_lua, script);
		else
			errorType = luaL_loadfile(_lua, filename.str().c_str());

		// Error al cargar el fichero de script
		if (errorType == LUA_ERRFILE)
		{
			std::cout << "ERROR DE LUA! - Error al cargar el fichero de script \"" << script << "\". Comprueba que est� bien escrito el nombre y que el fichero existe." << std::endl;

			return false;
		}
		// Error de sintaxis de lua
		else if (errorType == LUA_ERRSYNTAX)
		{
			std::cout << "ERROR DE LUA! - Error de sintaxis de lua al cargar el script \"" << script << "\". Comprueba que no hay errores en el fichero de script." << std::endl;

			return false;
		}
		// Memory allocation error
		else if (errorType == LUA_ERRMEM)
		{
			std::cout << "ERROR DE LUA! - Error chungo de lua al cargar el script \"" << script << "\" : Memory allocation error." << std::endl;

			return false;
		}
		// Error chungo de no se qu� de metamethod
		else if (errorType == LUA_ERRGCMM)
		{
			std::cout << "ERROR DE LUA! - Error chungo de lua al cargar el script \"" << script << "\" : Error chungo de no se qu� de metamethod." << std::endl;

			return false;
		}

		return true;
		
	} // loadScript

	//---------------------------------------------------------

	bool CServer::executeLastLoadScript(const char *script)
	{
		// Ejecuto el script y hago el manejo de errores.
		int msgHandler = 0;
		int errorType = lua_pcall(_lua, 0, 0, msgHandler);

		// Si es un runtime error, accedo al tipo de error guardado en la pila y lo muestro por consola
		if (errorType == LUA_ERRRUN)
		{
			// Si el handler es distinto de cero, el mensaje de error se encuentra en la pila. Lo recupero y lo muestro.
			if (msgHandler != 0)
			{
				const char* error = lua_tostring(_lua, msgHandler);
				std::cout << "ERROR DE LUA! - Error de runtime de lua al ejecutar el script \"" << script << "\": " << error << std::endl;
			}
			else
				// En teor�a esta situaci�n no deber�a darse nunca, pero no est� de m�s hacer la comprobaci�n.
				std::cout << "ERROR DE LUA! - Error desconocido de runtime de lua al ejecutar el script \"" << script << "\"" << std::endl;

			return false;
		}
		// Memory allocation error
		else if (errorType == LUA_ERRMEM)
		{
			std::cout << "ERROR DE LUA! - Error chungo de lua al ejecutar el script \"" << script << "\" : Memory allocation error." << std::endl;

			return false;
		}
		// Error ejecutando el message handler
		else if (errorType == LUA_ERRERR)
		{
			std::cout << "ERROR DE LUA! - Error chungo de lua al ejecutar el script \"" << script << "\" : Error ejecutando el message handler." << std::endl;

			return false;
		}
		// Error chungo de no se qu� de metamethod
		else if (errorType == LUA_ERRGCMM)
		{
			std::cout << "ERROR DE LUA! - Error chungo de lua al ejecutar el script \"" << script << "\" : Error chungo de no se qu� de metamethod." << std::endl;

			return false;
		}

		return true;

	} // executeLastLoadScript

	//---------------------------------------------------------

} // namespace ScriptManager
