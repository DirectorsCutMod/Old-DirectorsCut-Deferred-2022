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

#include "defconstruct_vs30.inc"
#include "lightingpass_point_ps30.inc"

BEGIN_VS_SHADER( LIGHTING_WORLD, "" )
	BEGIN_SHADER_PARAMS

		SHADER_PARAM( LIGHTTYPE, SHADER_PARAM_TYPE_INTEGER, "0", "" )
		SHADER_PARAM( WORLDPROJECTION, SHADER_PARAM_TYPE_BOOL, "0", "" )

	END_SHADER_PARAMS

	void SetupParmsLightPass( lightPassParms &p )
	{
		p.iLightTypeVar = LIGHTTYPE;
		p.iWorldProjection = WORLDPROJECTION;
	}

	SHADER_INIT_PARAMS()
	{
		lightPassParms parms;
		SetupParmsLightPass( parms );
		InitParmsLightPass( parms, this, params );
	}

	SHADER_INIT
	{
		lightPassParms parms;
		SetupParmsLightPass( parms );
		InitPassLightPass( parms, this, params );
	}

	SHADER_FALLBACK
	{
		return 0;
	}

	SHADER_DRAW
	{
		lightPassParms parms;
		SetupParmsLightPass( parms );
		DrawPassLightPass( parms, this, params, pShaderShadow, pShaderAPI, vertexCompression );
	}

END_SHADER