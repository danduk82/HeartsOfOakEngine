/**
 * This file contains a few useful conversions between OIS and CEGUI that I have found on the net...
 *
 */

#include "CEGUI/CEGUI.h"
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>


void InjectOISKey(bool bButtonDown, OIS::KeyEvent inKey);
void InjectOISMouseButton(bool bButtonDown, OIS::MouseButtonID inButton);
