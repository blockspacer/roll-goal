#include "level-state.h"

#include "systems/physic-system.h"
#include "systems/render-system.h"

LevelState::LevelState(Context context) : IState(GameState::LEVEL, context)
{
	m_systems.resize(2);
	m_systems.at(0) = new PhysicSystem(*context.registry);
	m_systems.at(1) = new RenderSystem(*context.registry);
}

LevelState::~LevelState() {
	for (const auto system : m_systems) {
		delete system;
	}
}

/////////////////////////////////////////////////////////////////////////////
////////////////////////////// PUBLIC METHODS ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////


void LevelState::onEnter() {
	m_lifeCycle = LifeCycle::HAS_ENTERED;
}

void LevelState::update() {
	for (const auto system : m_systems) {
		system->update();
	}

	if (m_lifeCycle == LifeCycle::HAS_ENTERED)
		m_lifeCycle = LifeCycle::HAS_UPDATED;
}

void LevelState::onExit() {
	m_lifeCycle = LifeCycle::HAS_EXITED;
}


/////////////////////////////////////////////////////////////////////////////
//////////////////////////// GETTERS & SETTERS //////////////////////////////
/////////////////////////////////////////////////////////////////////////////


