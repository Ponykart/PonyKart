#ifndef PHYSICSMAIN_H_INCLUDED
#define PHYSICSMAIN_H_INCLUDED

#include <functional>
#include <vector>
#include <OgreFrameListener.h>
#include "Levels/LevelChangedEventArgs.h"

class btDiscreteDynamicsWorld;
class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;

namespace Ponykart
{
namespace Physics
{
	using PhysicsWorldEvent = std::vector<std::function<void (btDiscreteDynamicsWorld*)>>;
	using PhysicsSimulateEvent = std::vector<std::function<void(btDiscreteDynamicsWorld* world, const Ogre::FrameEvent& evt)>>;

	class PhysicsMain : public Ogre::FrameListener
	{
	public:
		PhysicsMain();
		void onLevelUnload(Levels::LevelChangedEventArgs* eventArgs); // Deletes the world
		// Getters
		btDiscreteDynamicsWorld* getWorld();

	private:
		// Runs just before every frame. Simulates one frame of physics.
		// Physics simulation should be the only thing that's using FrameEnded!
		bool frameEnded(const Ogre::FrameEvent& evt) override;

	private:
		static const int _maxSubsteps;
		static const float _fixedTimestep;
		btBroadphaseInterface* broadphase;
		btDefaultCollisionConfiguration* dcc;
		btCollisionDispatcher* dispatcher;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* world;

	public:
		static bool drawLines; // Should we draw debug lines or not?
		static bool slowMo;

		static PhysicsWorldEvent postCreateWorld; ///< Is invoked right after the physics world is created.
		static PhysicsSimulateEvent preSimulate; ///< Is invoked right before the physics world is simulated.
		static PhysicsSimulateEvent postSimulate; ///< Is invoked right after the physics world is simulated.
		/// Is invoked just after PreSimulate but just before the physics world is simulated.
		/// You should use this as a last "get everything ready" point before we simulate.
		static PhysicsSimulateEvent finaliseBeforeSimulation;
	};
} // Physics
} // Ponykart


#endif // PHYSICSMAIN_H_INCLUDED
