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

#ifndef DEFPASS_COMPOSITE_H
#define DEFPASS_COMPOSITE_H

class CDeferredPerMaterialContextData;

struct defParms_composite
{
	defParms_composite()
	{
		Q_memset( this, 0xFF, sizeof( defParms_composite ) );

		bModel = false;
	};

	// textures
	int iAlbedo;
	int iAlbedo2;
	int iAlbedo3;
	int iAlbedo4;
	int iEnvmap;
	int iEnvmapMask;
	int iEnvmapMask2;
	int iBlendmodulate;
	int iBlendmodulate2;
	int iBlendmodulate3;

	// envmapping
	int iEnvmapTint;
	int iEnvmapSaturation;
	int iEnvmapContrast;
	int iEnvmapFresnel;

	// rimlight
	int iRimlightEnable;
	int iRimlightExponent;
	int iRimlightAlbedoScale;
	int iRimlightTint;
	int iRimlightModLight;

	// alpha
	int iAlphatestRef;

	// phong
	int iPhongScale;
	int iPhongFresnel;

	// self illum
	int iSelfIllumTint;
	int iSelfIllumMaskInEnvmapAlpha;
	int iSelfIllumFresnelModulate;
	int iSelfIllumMask;

	// blendmod
	int iBlendmodulateTransform;
	int iBlendmodulateTransform2;
	int iBlendmodulateTransform3;
	int iMultiblend;

	int iFresnelRanges;

	// config
	bool bModel;
};


void InitParmsComposite( const defParms_composite &info, CBaseVSShader *pShader, IMaterialVar **params );
void InitPassComposite( const defParms_composite &info, CBaseVSShader *pShader, IMaterialVar **params );
void DrawPassComposite( const defParms_composite &info, CBaseVSShader *pShader, IMaterialVar **params,
	IShaderShadow* pShaderShadow, IShaderDynamicAPI* pShaderAPI,
	VertexCompressionType_t vertexCompression, CDeferredPerMaterialContextData *pDeferredContext );


#endif