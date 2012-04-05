Archetype = {

	World = {
		type = "World",
		
		physic_collision_group = 1,
		billboardMoverMaterial = "circuloSeleccion",
		billboardMoverDimension = 10.0,
		billboardMoverTime = 2.0,
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
	
	Enemies = {
		type = "Enemies",
		position = {80, 5, -80},
		periodo = 10000,
	},

	Enemy = {
		type = "Enemy",
		orientation = 0,
		life = 40.0,
		maxLife = 100.0,
		isPlayer = false,
		model = "loco.mesh",
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
		
		trigger_shape = "trigger_sphere",
		trigger_type = "trigger_static",
		trigger = true,
		trigger_radius = 25,
		trigger_height = 1,
		trigger_collision_group = 3,
	},
	
	Player = {
		type = "Player",
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
	},
	
	Waypoint = {
		type = "Waypoint",
		position = {0, 0, 0},
		orientation = 0,
		model = "Esfera.mesh",
		scale = 8.0,
	},
	
}