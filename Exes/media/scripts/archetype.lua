Archetype = {

	World = {
		type = "World",
		
		physic_collision_group = 1,
		billboardMoverMaterial = "circuloSeleccion",
		billboardMoverDimension = 10.0,
		billboardMoverTime = 2.0,
		position = {0, 0, 0},
		orientation = 0,
	},
	
	PlayerGod = {
		type = "PlayerGod",
		mouseDistance = 100,
		cameraDistance = 150,
		cameraVelocity = 500,
		mouseVelocity = 4,
		dayTime = 10000,
		dayTimeAlarm = 1000,
		nightTime = 1000000,
		speed = 0.15,
		safeLimit = 110.0,
		initPoint = { 0, 0, 0 },
	},
	
	Obstacle = {
		type = "Obstacle",
		position = {0, -1, 0},
		physic_entity = "simple",
		physic_type = "static",
		physic_shape = "box",
		physic_dimensions = { 8, 16, 8 },
		physic_collision_group = 1,
	},
	
	Entity = {
		type = "Entity",
		position = {0, 0, 0},
		orientation = 0,
		model = "torreta_pie.mesh",
	},
	
	PhantomTurret = {
		type = "PhantomTurret",
		position = {0, -50, 0},
		orientation = 0,
		building_size = "1 1",
		model = "torreta_pie.mesh",
	},
	
	Turret = {
		type = "Turret",
		position = {0, 0, 0},
		orientation = 0,
		building_size = "1 1",
		model = "torreta_pie.mesh",
		physic_entity = "simple",
		physic_type = "static",
		physic_shape = "box",
		physic_dimensions = { 8, 8, 8 },
		physic_height = 16,
		physic_radius = 16,
		physic_collision_group = 2,
		trigger_shape = "trigger_sphere",
		trigger_type = "trigger_static",
		trigger = true,
		trigger_radius = 25,
		trigger_height = 1,
		trigger_collision_group = 3,
		precision = 0.1,
		damage = 25,
	},
	
	DoorStage2Trigger = {
		type = "DoorStage2Trigger",
		trigger = true,
		trigger_shape = "trigger_box",
		trigger_type = "trigger_static",
		trigger_collision_group = 3,
	},
	
	Barril = {
		type = "Barril",
		position = {0, 1, 0},
		orientation = 0,
		model = "barril.mesh",
		physic_entity = "simple",
		physic_type = "dynamic",
		physic_shape = "box",
		physic_dimensions = { 2.3, 2.5, 2.3 },
		physic_height = 2,
		physic_radius = 0.5,
		physic_mass = 1,
		physic_collision_group = 6,
	},
	
	EnemyMind = {
		type = "EnemyMind",
	},
	
	Enemies = {
		type = "Enemies",
		periodo = 10000,
		automaticSpawn = false,
	},

	Enemy = {
		type = "Enemy",
		tag = "enemy",
		orientation = 0,
		life = 100.0,
		maxLife = 100.0,
		isPlayer = false,
		model = "marine.mesh",
		defaultAnimation = "Idle",
		behavior = "wander",
		physic_entity = "controller",
		physic_shape = "capsule",
		physic_radius = 4,
		physic_height = 6,
		physic_collision_group = 5,
		speed = 0.02,
		angularSpeed = 0.005,
		accel = 0.001,
		angularAccel = 0.0001,
		movementTolerance = 7.0,
		
		billboardLifeMaterial = "barraVida",
		billboardLifeWith = 10.0,
		billboardLifeHeight = 0.5,
		billboardLifePosition = {0.0,12.0,0.0},
		
		billboardSeleccionMaterial = "circuloSeleccion",
		billboardSeleccionWith = 15.0,
		billboardSeleccionHeight = 15.0,
		
		afectaEmpujar = 100,
		
		distOfView = 100,
		
		initState = 1,
		memInitPoint = true,
		runLifeThreshold = 50,
		
		damage = 10,
	},
	
	Granada = {
		type = "Granada",
		position = {0, 3, 0},
		orientation = 0,
		model = "Esfera.mesh",
		scale = 12.0,
		physic_entity = "simple",
		physic_type = "dynamic",
		physic_shape = "box",
		physic_dimensions = { 1.0, 1.0, 1.0 },
		physic_height = 2.0,
		physic_radius = 0.5,
		physic_mass = 1,
		physic_collision_group = 6,
		
		damage = 20.0,
		timeEmpujar = 0.3,
		distEmpujarSeg = 150.0,
	},

	BolaTeltr = {
		type = "BolaTeltr",
		position = {0, 3, 0},
		orientation = 0,
		model = "Esfera.mesh",
		scale = 12.0,
		physic_entity = "simple",
		physic_type = "dynamic",
		physic_shape = "box",
		physic_dimensions = { 1.0, 1.0, 1.0 },
		physic_height = 2.0,
		physic_radius = 0.5,
		physic_mass = 1,
		physic_collision_group = 6,
		distEmpujarSeg = 150.0,
	},
	
	Player = {
		type = "Player",
		tag = "player",
		position = {0, 5, 0},
		orientation = 180,
		life = 100.0,
		maxLife = 100.0,
		isPlayer = false,
		model = "marine.mesh",
		defaultAnimation = "Idle",
		behavior = "wander",
		physic_entity = "controller",
		physic_shape = "capsule",
		physic_radius = 3,
		physic_height = 6,
		physic_collision_group = 4,
		speed = 0.05,
		angularSpeed = 50.0,
		accel = 0.001,
		angularAccel = 11.0,
		movementTolerance = 3.0,
		
		billboardLifeMaterial = "barraVida",
		billboardLifeWith = 8.0,
		billboardLifeHeight = 1.0,
		billboardLifePosition = {0.0,13.0,0.0},
		
		billboardSeleccionMaterial = "circuloSeleccion",
		billboardSeleccionWith = 10.0,
		billboardSeleccionHeight = 10.0,
		
		billboardLanzamientoMaterial = "circuloSeleccion",
		billboardLanzamientoWith = 150.0,
		billboardLanzamientoHeight = 150.0,
		alcanceGranada = 70.0,
		
		afectaEmpujar = 100,
		
		initState = 1,
		
		
		trigger_shape = "trigger_sphere",
		trigger_type = "trigger_static",
		trigger = true,
		trigger_radius = 100,
		trigger_height = 1,
		trigger_collision_group = 3,
	},
	
	Waypoint = {
		type = "Waypoint",
		position = {0, 0, 0},
		orientation = 0,
		model = "Esfera.mesh",
		scale = 8.0,
	},
	
}