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

#ifndef DEFPASS_SHADOW_H
#define DEFPASS_SHADOW_H

class CDeferredPerMaterialContextData;

struct defParms_shadow
{
	defParms_shadow()
	{
		Q_memset( this, 0xFF, sizeof( defParms_shadow ) );

		bModel = false;
	};

	// textures
	int iAlbedo;
	int iAlbedo2;
	int iAlbedo3;
	int iAlbedo4;

	// control
	int iAlphatestRef;

	// blending
	int iMultiblend;

	// config
	bool bModel;
};


void InitParmsShadowPass( const defParms_shadow &info, CBaseVSShader *pShader, IMaterialVar **params );
void InitPassShadowPass( const defParms_shadow &info, CBaseVSShader *pShader, IMaterialVar **params );
void DrawPassShadowPass( const defParms_shadow &info, CBaseVSShader *pShader, IMaterialVar **params,
	IShaderShadow* pShaderShadow, IShaderDynamicAPI* pShaderAPI,
	VertexCompressionType_t vertexCompression, CDeferredPerMaterialContextData *pDeferredContext );


#endif