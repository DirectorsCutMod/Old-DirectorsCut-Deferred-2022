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

#ifndef FLASHLIGHTEFFECT_DEFERRED_H
#define FLASHLIGHTEFFECT_DEFERRED_H

#include "cbase.h"
#include "flashlighteffect.h"

struct def_light_t;

class CFlashlightEffectDeferred : public CFlashlightEffect
{
public:

	CFlashlightEffectDeferred(int nEntIndex = 0, const char *pszTextureName = NULL, float flFov = 0.0f, float flFarZ = 0.0f, float flLinearAtten = 0.0f );
	~CFlashlightEffectDeferred();

protected:

	void UpdateLightProjection( FlashlightState_t &state );
	void LightOff();

private:

	def_light_t *m_pDefLight;
};


#endif