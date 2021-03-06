/**
@file Billboard.h

@see Graphics::CBillboard

@author Isaac
@date febrero, 2012
*/


#ifndef __Graphics_Billboard_H
#define __Graphics_Billboard_H

#include <string>

namespace Logic
{
	class CEntity;
}
namespace Ogre 
{
	class Entity;
	class SceneNode;
	class BillboardSet;
	class Vector3;
}

namespace Graphics 
{
	class CScene;
}

namespace Graphics 
{
	/**

	@ingroup graphicsGroup

	@author Isaac
	@date Febrero, 2012
	*/
	class CBillboard 
	{
	public:

		/**
		Constructor de la clase.
		*/
		CBillboard(Logic::CEntity * entity);
		CBillboard::CBillboard(CScene * scene);
		/**
		Destructor de la aplicación.
		*/
		virtual ~CBillboard();

		void attachEntity(Logic::CEntity * entity);

		void setMaterial(std::string s);
		void setDimensions(float x, float y);
		void setPosition(float x, float y, float z);
		void setPosicionImagen(float x, float x2, float y, float y2);
		void setPerpendicular();
		void setVisible(bool b);
		Ogre::BillboardSet* getBillboarset() {return _billboardset;}

	protected:
		friend class CScene;
		

		Ogre::BillboardSet* _billboardset;
	};

}

#endif
