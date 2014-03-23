/**
 * This converts input from OIS to CEGUI.
 */

#include "OIS_2_CEGUI.h"


void InjectOISKey(bool bButtonDown, OIS::KeyEvent inKey)
{
	if (bButtonDown)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown((CEGUI::Key::Scan)inKey.key);
		CEGUI::System::getSingleton().getDefaultGUIContext().injectChar((CEGUI::Key::Scan)inKey.text);

	}
	else
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)inKey.key);
	}
}

void InjectOISMouseButton(bool bButtonDown, OIS::MouseButtonID inButton)
{
	if (bButtonDown == true)
	{
		switch (inButton)
		{
		case OIS::MB_Left:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::LeftButton);
			//CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
			break;
		case OIS::MB_Middle:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::MiddleButton);
			break;
		case OIS::MB_Right:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::RightButton);
			break;
		case OIS::MB_Button3:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::X1Button);
			break;
		case OIS::MB_Button4:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::X2Button);
			break;
		default:
			break;

		}
	}
	else // bButtonDown = false
	{
		switch (inButton)
		{
		case OIS::MB_Left:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::LeftButton);
			break;
		case OIS::MB_Middle:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::MiddleButton);
			break;
		case OIS::MB_Right:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::RightButton);
			break;
		case OIS::MB_Button3:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::X1Button);
			break;
		case OIS::MB_Button4:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::X2Button);
			break;
		default:
			break;
		}
	}

}
