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

#include "radiosity_propagate_ps30.inc"
#include "radiosity_propagate_vs30.inc"

BEGIN_VS_SHADER( RADIOSITY_PROPAGATE, "" )
	BEGIN_SHADER_PARAMS

		SHADER_PARAM( NORMALMAP, SHADER_PARAM_TYPE_TEXTURE, "", "" )
		SHADER_PARAM( BLUR, SHADER_PARAM_TYPE_BOOL, "", "" )

	END_SHADER_PARAMS

	SHADER_INIT_PARAMS()
	{
	}

	SHADER_INIT
	{
		Assert( params[ BASETEXTURE ]->IsDefined() );
		Assert( params[ NORMALMAP ]->IsDefined() );

		if ( params[ BASETEXTURE ]->IsDefined() )
			LoadTexture( BASETEXTURE );

		if ( params[ NORMALMAP ]->IsDefined() )
			LoadTexture( NORMALMAP );
	}

	SHADER_FALLBACK
	{
		return 0;
	}

	SHADER_DRAW
	{
		SHADOW_STATE
		{
			pShaderShadow->SetDefaultState();

			pShaderShadow->EnableDepthTest( false );
			pShaderShadow->EnableDepthWrites( false );
			pShaderShadow->EnableAlphaWrites( false );

			pShaderShadow->EnableTexture( SHADER_SAMPLER0, true );
			pShaderShadow->EnableTexture( SHADER_SAMPLER1, true );

			int iTexDim[] = { 4, 4 };
			pShaderShadow->VertexShaderVertexFormat( VERTEX_POSITION, 2, iTexDim, 0 );

			DECLARE_STATIC_VERTEX_SHADER( radiosity_propagate_vs30 );
			SET_STATIC_VERTEX_SHADER( radiosity_propagate_vs30 );

			DECLARE_STATIC_PIXEL_SHADER( radiosity_propagate_ps30 );
			SET_STATIC_PIXEL_SHADER_COMBO( BLUR, PARM_INT( BLUR ) );
			SET_STATIC_PIXEL_SHADER( radiosity_propagate_ps30 );
		}
		DYNAMIC_STATE
		{
			pShaderAPI->SetDefaultState();

			DECLARE_DYNAMIC_VERTEX_SHADER( radiosity_propagate_vs30 );
			SET_DYNAMIC_VERTEX_SHADER( radiosity_propagate_vs30 );

			DECLARE_DYNAMIC_PIXEL_SHADER( radiosity_propagate_ps30 );
			SET_DYNAMIC_PIXEL_SHADER( radiosity_propagate_ps30 );

			BindTexture( SHADER_SAMPLER0, BASETEXTURE );
			BindTexture( SHADER_SAMPLER1, NORMALMAP );
		}

		Draw();
	}
END_SHADER