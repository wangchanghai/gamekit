/*
-------------------------------------------------------------------------------
	This file is part of the Ogre GameKit port.
	http://gamekit.googlecode.com/

	Copyright (c) 2009 Charlie C.
-------------------------------------------------------------------------------
 This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
	 claim that you wrote the original software. If you use this software
	 in a product, an acknowledgment in the product documentation would be
	 appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
	 misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#include "gkWindowSystem.h"
#include "gkMouseNode.h"
#include "gkLogicSocket.h"
#include "gkEngine.h"
#include "gkLogger.h"


using namespace Ogre;


// ----------------------------------------------------------------------------
gkMouseNode::gkMouseNode(gkLogicTree *parent, size_t id) :
		gkLogicNode(parent, NT_MOUSE, id)
{
	ADD_ISOCK(mSockets[0],  this, gkLogicSocket::ST_REAL);
	ADD_ISOCK(mSockets[1],  this, gkLogicSocket::ST_REAL);
	mSockets[0].setValue(1.f);
	mSockets[1].setValue(1.f);

	ADD_OSOCK(mSockets[2],  this, gkLogicSocket::ST_BOOL);
	ADD_OSOCK(mSockets[3],  this, gkLogicSocket::ST_REAL);
	ADD_OSOCK(mSockets[4],  this, gkLogicSocket::ST_REAL);
	ADD_OSOCK(mSockets[5],  this, gkLogicSocket::ST_REAL);
	ADD_OSOCK(mSockets[6],  this, gkLogicSocket::ST_REAL);
	ADD_OSOCK(mSockets[7],  this, gkLogicSocket::ST_REAL);
}

// ----------------------------------------------------------------------------
bool gkMouseNode::evaluate(Real tick)
{
	gkMouseDevice dev= gkWindowSystem::getSingleton().getMouse();

	Real x= 0, y= 0;
	Real x_scale= mSockets[0].getValueReal();
	Real y_scale= mSockets[1].getValueReal();

	if (dev.moved)
	{
		if (mSockets[3].isConnected()) x= dev.relitave.x * x_scale;
		if (mSockets[4].isConnected()) y= dev.relitave.y * y_scale;
	}

	if (mSockets[5].isConnected()) mSockets[5].setValue(dev.absolute.x * x_scale);
	if (mSockets[6].isConnected()) mSockets[6].setValue(dev.absolute.y * y_scale);

	mSockets[3].setValue(x);
	mSockets[4].setValue(y);
	mSockets[2].setValue(dev.moved);
	mSockets[7].setValue(dev.wheelDelta);
	return false;
}