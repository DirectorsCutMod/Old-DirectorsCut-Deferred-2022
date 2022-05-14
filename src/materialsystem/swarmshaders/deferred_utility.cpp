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


#include "deferred_includes.h"

#include "tier0/memdbgon.h"

ConVar deferred_radiosity_multiplier( "deferred_radiosity_multiplier", "0.4" );

void GetTexcoordSettings( const bool bDecal, const bool bMultiBlend,
	int &iNumTexcoords, int **iTexcoordDim )
{
	static int iDimDefault[] = {
		2, 0, 3,
	};

	static int iDimMultiBlend[] = {
		2, 2, 0, 4,
		4, 4, 4, 4,
	};

	if ( bMultiBlend )
	{
		*iTexcoordDim = iDimMultiBlend;
		iNumTexcoords = 8;
	}
	else if ( bDecal )
	{
		*iTexcoordDim = iDimDefault;
		iNumTexcoords = 3;
	}
	else
	{
		*iTexcoordDim = iDimDefault;
		iNumTexcoords = 1;
	}
}