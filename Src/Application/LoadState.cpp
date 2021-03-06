//---------------------------------------------------------------------------
// LoadState.cpp
//---------------------------------------------------------------------------

/**
@file LoadState.h

Contiene la declaraci�n del estado en el que se cargan los recursos

@see Application::CApplicationState
@see Application::CGameState

@author Alberto Ortega
@date Abril, 2012
*/

#include "LoadState.h"

#include "Logic/Server.h"
#include "Logic/Maps/EntityFactory.h"
#include "Logic/Maps/Map.h"

#include "GUI/Server.h"
#include "GUI/PlayerController.h"
#include "GUI/CameraController.h"
#include "GUI/InterfazController.h"

#include "Physics/Server.h"
#include "ScriptManager/Server.h"

#include "GUI/Server.h"
#include <CEGUISystem.h>
#include <CEGUIWindowManager.h>
#include <CEGUIWindow.h>
#include <elements/CEGUIPushButton.h>

namespace GUI 
{
	class CInterfazController;
}

namespace Application {
	bool CLoadState::init() 
	{
		CApplicationState::init();

		// Cargamos la ventana que muestra una pantalla de carga
		CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("Loading.layout");
		
		_window = CEGUI::WindowManager::getSingleton().getWindow("Loading");
		
		return true;

	} // init

	//--------------------------------------------------------

	void CLoadState::release() 
	{
		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CLoadState::activate() 
	{
		CApplicationState::activate();

		// Activamos la ventana que nos muestra el men� y activamos el rat�n.
		CEGUI::System::getSingletonPtr()->setGUISheet(_window);
		_window->setVisible(true);
		_window->activate();
		CEGUI::MouseCursor::getSingleton().hide();

	} // activate

	//--------------------------------------------------------

	void CLoadState::deactivate() 
	{
		//Cargar el nivel
		LoadLevel();

		// Activamos el mapa que ha sido cargado para la partida.
		Logic::CServer::getSingletonPtr()->activateMap();

		// Queremos que el GUI maneje al jugador y la c�mara.
		GUI::CServer::getSingletonPtr()->getPlayerController()->activate();
		GUI::CServer::getSingletonPtr()->getCameraController()->activate();
		
		/*
		// Mostramos el rat�n
		CEGUI::MouseCursor::getSingleton().show();
		
		// El siguiente c�digo es para sincronizar el rat�n de CEGUI con el de OIS.
		const OIS::MouseState state = GUI::CInputManager::getSingletonPtr()->getMouseState();
		CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();  
		CEGUI::System::getSingleton().injectMouseMove(state.X.abs-mousePos.d_x,state.Y.abs-mousePos.d_y);*/

		CApplicationState::deactivate();

	} // deactivate

	//--------------------------------------------------------

	void CLoadState::tick(unsigned int msecs) 
	{
		CApplicationState::tick(msecs);

		//Incializar el estado de d�a del juego
		//para hacer pruebas, esperar a pulsar la tecla esc para inicializar el juego
		_app->setState("day");

	} // tick

	//--------------------------------------------------------

	bool CLoadState::keyPressed(GUI::TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CLoadState::keyReleased(GUI::TKey key)
	{

		switch(key.keyId)
		{
		case GUI::Key::RETURN:
			break;

		default:
			return false;
		}
		return true;


	} // keyReleased

	//--------------------------------------------------------
	
	bool CLoadState::mouseMoved(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CLoadState::mousePressed(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------

	bool CLoadState::mouseReleased(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

	//--------------------------------------------------------

	bool CLoadState::LoadLevel()
	{
		// Crear la escena f�sica.
		Physics::CServer::getSingletonPtr()->createScene();

		// Cargamos el archivo con las definiciones de las entidades del nivel.
		if (!Logic::CEntityFactory::getSingletonPtr()->loadBluePrints("blueprints.txt"))
			return false;

		// Cargamos el nivel y los arquetipos a partir de los nombres de los ficheros de script. 
		if (!Logic::CServer::getSingletonPtr()->loadLevel("map", "archetype"))
			return false;

		//ScriptManager::CServer::getSingletonPtr()->loadExeScript("mission1Parameters");

		return true;
	}


} // namespace Application
