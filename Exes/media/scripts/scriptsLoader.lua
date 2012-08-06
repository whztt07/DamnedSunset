function loadScripts()
	SManager:loadScript("parametersLoader")
	SManager:loadScript("utils")

	-- Scripts de la m�quina de estados de la IA de los personajes
	SManager:loadScript("playerIAScript")
	SManager:loadScript("playerSecondaryIAScript")
	SManager:loadScript("habilities")

	-- Scripts de la m�quina de estados de la IA de los enemigos.
	SManager:loadScript("enemyIdleState")
	SManager:loadScript("enemyAttackState")
	SManager:loadScript("enemyMoveState")
	SManager:loadScript("enemyRunState")
	SManager:loadScript("enemyPauseState")
	SManager:loadScript("enemyScript")

	-- Scripts de la maquina de estados de God
	SManager:loadScript("godIdleState")
	SManager:loadScript("godSelectedState")
	SManager:loadScript("godSkillState")
	SManager:loadScript("godScript")

	-- Scripts de la m�quina de estados de la IA de la supermente.
	SManager:loadScript("enemyMindNightState")
	SManager:loadScript("enemyMindDayState")
	SManager:loadScript("enemyMindScript")

	-- Interfaz
	SManager:loadScript("interfaz/interfazControles")
	SManager:loadScript("interfaz/interfazNoche")
	SManager:loadScript("interfaz/interfazPrincipal")
	SManager:loadScript("interfaz/interfazDia")

	-- Scripts de misi�n.
	SManager:loadScript("mission1StagesConfiguration")
	SManager:loadScript("mission1Behaviour")

	-- Scipt del panel solar
	SManager:loadScript("panelSolar")
	
	-- Script para inicializar las variables
	-- Debe ser el ultimo script cargado
	SManager:loadScript("mission1Parameters")
end
