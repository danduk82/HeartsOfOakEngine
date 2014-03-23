#include "TutorialApplication.h"

bool ITutorial02::mouseMoved(const OIS::MouseEvent &arg)
{
	// If we are dragging the left mouse button.
		if (mLMouseDown)
		{
		} // if

		// If we are dragging the right mouse button.
		else if (mRMouseDown)
		{
			mCamera->yaw(Ogre::Degree(-arg.state.X.rel * mRotateSpeed));
			mCamera->pitch(Ogre::Degree(-arg.state.Y.rel * mRotateSpeed));
		} // else if
	return true;
}

bool ITutorial02::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	// Left mouse button down
	if (id == OIS::MB_Left)
	{
		// Setup the ray scene query, use CEGUI's mouse position
		//CEGUI::Vector2f mousePos  = CEGUI::MouseCursor::getPosition();
		CEGUI::Vector2f mousePos  = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();
		Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(mousePos.d_x/float(arg.state.width), mousePos.d_y/float(arg.state.height));
		mRaySceneQuery->setRay(mouseRay);

		// Execute query
		Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
		Ogre::RaySceneQueryResult::iterator itr = result.begin( );

		// Get results, create a node/entity on the position
		if (itr != result.end() && itr->worldFragment)
		{
			char name[16];
			sprintf( name, "Robot%d", mCount++ );
			Ogre::Entity *ent = mSceneMgr->createEntity(name, "robot.mesh");
			mCurrentObject = mSceneMgr->getRootSceneNode()->createChildSceneNode(std::string(name) + "Node", itr->worldFragment->singleIntersection);
			mCurrentObject->attachObject(ent);
			mCurrentObject->setScale(0.1f, 0.1f, 0.1f);
		} // if

		mLMouseDown = true;
	} // if

	// Right mouse button down
	else if (id == OIS::MB_Right)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
		mRMouseDown = true;
	} // else if

	if (mLMouseDown)
	{
		//CEGUI::Vector2f mousePos = CEGUI::MouseCursor.getPosition();
		CEGUI::Vector2f mousePos  = CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();
		Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(mousePos.d_x/float(arg.state.width),mousePos.d_y/float(arg.state.height));
		mRaySceneQuery->setRay(mouseRay);

		Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
		Ogre::RaySceneQueryResult::iterator itr = result.begin();

		if (itr != result.end() && itr->worldFragment){
			mCurrentObject->setPosition(itr->worldFragment->singleIntersection);
		}

	} // if


	return true;
}

bool ITutorial02::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	// Left mouse button up
	if (id == OIS::MB_Left)
	{
		mLMouseDown = false;
	} // if

	// Right mouse button up
	else if (id == OIS::MB_Right)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
		mRMouseDown = false;
	} // else if
	return true;
}
