#ifndef __Logic_DetonadorGranada_H
#define __Logic_DetonadorGranada_H

#include "Logic/Entity/Component.h"
#include "BaseSubsystems/ClockListener.h"

// Los componentes pertenecen al namespace Logic
namespace Logic 
{

	class CDetonadorGranada: public IComponent, public BaseSubsystems::IClockListener
	{
		DEC_FACTORY(CDetonadorGranada);
	public:

		/**
		Constructor por defecto.
		*/
		CDetonadorGranada();
		~CDetonadorGranada();
		

		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);
		virtual bool accept(IMessage *message);
		virtual void process(IMessage *message);
		virtual bool activate();

		/**
		M�todo heredado de la interfaz IClockListener que ser� llamado
		por el temporizador cuando se acabe el tiempo de espera
		especificado.
		*/
		virtual void timeElapsed(); // @TEMPORIZADOR Declaraci�n del m�todo de la interfaz que va a ser llamado cuando se acabe el tiempo.
	protected:

	};

	REG_FACTORY(CDetonadorGranada);

}

#endif