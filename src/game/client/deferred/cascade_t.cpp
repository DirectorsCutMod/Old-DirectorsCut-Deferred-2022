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


#include "cbase.h"
#include "deferred/deferred_shared_common.h"


static const cascade_t g_CascadeInfo[] = {
	// res	orthosize	light offset	zFar		slopemin	slopemax	normalmax	renderdelay		rad		radcascade
	{ 2048, 1024.0f,	10000.0f,		12000.0f,	1.0f,		2.0f,		2.0f,		0.0f,			true,	0
#if CSM_USE_COMPOSITED_TARGET
	// viewport offset x/y
	, 0, 0
#endif
	},

	{ 1024, 4096.0f,	10000.0f,		15000.0f,	4.0f,		6.0f,		20.0f,		0.25f,			true,	1
#if CSM_USE_COMPOSITED_TARGET
	, 2048, 0
#endif
	},
};
static const int iNumCascades = ARRAYSIZE( g_CascadeInfo );


const cascade_t &GetCascadeInfo( int index )
{
	Assert( index >= 0 && index < iNumCascades );
	COMPILE_TIME_ASSERT( iNumCascades == SHADOW_NUM_CASCADES );

	return g_CascadeInfo[ index ];
}
