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

#ifndef DEFERRED_UTILITY_H
#define DEFERRED_UTILITY_H


#define DEFAULT_ALPHATESTREF 0.5f
#define DEFAULT_PHONG_SCALE 0.3f
#define DEFAULT_PHONG_EXP 0.15f
#define DEFAULT_PHONG_BOOST 1.0f

#define PARM_VALID( x ) ( x != -1 )

#define PARM_DEFINED( x ) ( x != -1 &&\
	params[ x ]->IsDefined() == true )

#define PARM_NO_DEFAULT( x ) ( PARM_VALID( x ) &&\
	!PARM_DEFINED( x ) )

#define PARM_SET( x ) ( PARM_DEFINED( x ) &&\
	params[ x ]->GetIntValue() != 0 )

#define PARM_TEX( x ) ( PARM_DEFINED( x ) &&\
	params[ x ]->IsTexture() == true )

#define PARM_FLOAT( x ) ( params[x]->GetFloatValue() )

#define PARM_INT( x ) ( params[x]->GetIntValue() )

#define PARM_VALIDATE( x ) Assert( PARM_DEFINED( x ) );

#define PARM_INIT_INT( x, val ) \
	if ( PARM_VALID( x ) && !params[ x ]->IsDefined() )\
	params[ x ]->SetIntValue( val );

#define PARM_INIT_FLOAT( x, val ) \
	if ( PARM_VALID( x ) && !params[ x ]->IsDefined() )\
	params[ x ]->SetFloatValue( val );

#define PARM_INIT_VEC3( x, val0, val1, val2 ) \
	if ( PARM_VALID( x ) && !params[ x ]->IsDefined() )\
	params[ x ]->SetVecValue( val0, val1, val2 );

void GetTexcoordSettings( const bool bDecal, const bool bMultiBlend,
	int &iNumTexcoords, int **iTexcoordDim );

extern ConVar deferred_radiosity_multiplier;

#include "defpass_gbuffer.h"

#endif