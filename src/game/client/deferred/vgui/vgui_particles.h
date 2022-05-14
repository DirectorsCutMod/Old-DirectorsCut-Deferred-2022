/*
*	The following header has been retroactively applied to all
*	code modified for use in Alien Swarm Deferred in order to
*	comply with its original Apache License 2.0 specification:
*
* 	Copyright 2013 Kristjan Skutta
*
* 	Licensed under the Apache License, Version 2.0 (the "License");
* 	you may not use this file except in compliance with the License.
* 	You may obtain a copy of the License at
*
* 		http://www.apache.org/licenses/LICENSE-2.0
*
* 	Unless required by applicable law or agreed to in writing, software
* 	distributed under the License is distributed on an "AS IS" BASIS,
* 	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* 	See the License for the specific language governing permissions and
* 	limitations under the License.
*/

#ifndef VGUI_PARTICLES_H
#define VGUI_PARTICLES_H

#include "vgui_controls/controls.h"
#include "deferred/vgui/vgui_projectable.h"
#include "view_shared.h"

class CParticleCollection;

class CVGUIParticles : public CVGUIProjectable
{
	DECLARE_CLASS_SIMPLE( CVGUIParticles, CVGUIProjectable );
public:

	CVGUIParticles();
	~CVGUIParticles();

protected:
	virtual void PerformLayout();

	virtual void Paint();
	virtual void OnThink();

	virtual void ApplyConfig( KeyValues *pKV );

private:

	CParticleCollection *AddParticleSystem( const char *pszName, Vector origin = vec3_origin, QAngle angles = vec3_angle );
	void FlushAllParticles();

	CUtlVector< CParticleCollection* >m_hParticles;

	CViewSetup m_ViewSetup;
};


#endif