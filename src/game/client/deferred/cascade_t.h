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

#ifndef CASCADE_T_H
#define CASCADE_T_H

#include "deferred/deferred_shared_common.h"

struct cascade_t
{
	int iResolution;

	float flProjectionSize;
	float flOriginOffset;
	float flFarZ;

	float flSlopeScaleMin;
	float flSlopeScaleMax;
	float flNormalScaleMax;

	float flUpdateDelay;
	bool bOutputRadiosityData;
	int iRadiosityCascadeTarget;

#if CSM_USE_COMPOSITED_TARGET
	int iViewport_x;
	int iViewport_y;
#endif
};

const cascade_t &GetCascadeInfo( int index );


#endif