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

#ifndef LIGHTING_HELPER_H
#define LIGHTING_HELPER_H

#include "deferred_includes.h"

FORCEINLINE void CommitBaseDeferredConstants_Frustum( IShaderDynamicAPI* pShaderAPI,
	const int iFirstFrustumRegister, const bool bVertexShader = true )
{
	if ( bVertexShader )
		pShaderAPI->SetVertexShaderConstant( iFirstFrustumRegister, GetDeferredExt()->GetFrustumDeltaBase(), 3 );
	else
		pShaderAPI->SetPixelShaderConstant( iFirstFrustumRegister, GetDeferredExt()->GetFrustumDeltaBase(), 3 );
}
FORCEINLINE void CommitBaseDeferredConstants_Origin( IShaderDynamicAPI* pShaderAPI,
	const int iPixelShaderOriginRegister )
{
	pShaderAPI->SetPixelShaderConstant( iPixelShaderOriginRegister, GetDeferredExt()->GetOriginBase() );
}


FORCEINLINE void CommitShadowcastingConstants_Ortho( IShaderDynamicAPI *pShaderAPI, const int index,
	int iForwardRegister, int iSlopeRegister, int iOriginRegister )
{
	Vector4D fwd = GetDeferredExt()->GetLightData_Global().vecLight * -1.0f;
	const shadowData_ortho_t &data = GetDeferredExt()->GetShadowData_Ortho( index );

	pShaderAPI->SetVertexShaderConstant( iForwardRegister, fwd.Base() );
	pShaderAPI->SetVertexShaderConstant( iSlopeRegister, data.vecSlopeSettings.Base() );
	pShaderAPI->SetVertexShaderConstant( iOriginRegister, data.vecOrigin.Base() );
}
FORCEINLINE void CommitShadowcastingConstants_Proj( IShaderDynamicAPI *pShaderAPI, const int index,
	int iForwardRegister, int iSlopeRegister, int iOriginRegister )
{
	const shadowData_proj_t &data = GetDeferredExt()->GetShadowData_Proj( index );

	pShaderAPI->SetVertexShaderConstant( iForwardRegister, data.vecForward.Base() );
	pShaderAPI->SetVertexShaderConstant( iSlopeRegister, data.vecSlopeSettings.Base() );
	pShaderAPI->SetVertexShaderConstant( iOriginRegister, data.vecOrigin.Base() );
}

FORCEINLINE void CommitGlobalLightForward( IShaderDynamicAPI *pShaderAPI,
	int iFirstRegister )
{
	Vector4D vecLight = GetDeferredExt()->GetLightData_Global().vecLight;
	pShaderAPI->SetPixelShaderConstant( iFirstRegister++, vecLight.Base() );
}

FORCEINLINE void MakeShadowProjectionConstants( float *pFl0, float *pFl1, int resx, int resy )
{
	pFl0[0] = 1.0f / resx;
	pFl0[1] = 1.0f / resy;
	pFl0[2] = 2.0f / resx;
	pFl0[3] = 2.0f / resy;

	pFl1[0] = resx;
	pFl1[1] = resy;
}

FORCEINLINE void CommitShadowProjectionConstants_Ortho_Single( IShaderDynamicAPI *pShaderAPI,
	const int index, int iFirstRegister )
{
	const shadowData_ortho_t &data = GetDeferredExt()->GetShadowData_Ortho( index );
	Vector4D fwd = GetDeferredExt()->GetLightData_Global().vecLight * -1.0f;

	pShaderAPI->SetPixelShaderConstant( iFirstRegister, data.matWorldToTexture.Base(), 3 );
	iFirstRegister += 3;
	pShaderAPI->SetPixelShaderConstant( iFirstRegister++, data.vecUVTransform.Base() );
	pShaderAPI->SetPixelShaderConstant( iFirstRegister++, data.vecSlopeSettings.Base() );
	pShaderAPI->SetPixelShaderConstant( iFirstRegister++, data.vecOrigin.Base() );
	pShaderAPI->SetPixelShaderConstant( iFirstRegister, fwd.Base() );
}

FORCEINLINE void CommitShadowProjectionConstants_Ortho_Composite( IShaderDynamicAPI *pShaderAPI,
	const int numCascades, int iFirstRegister )
{
	int stepsLeft = numCascades;
	for ( int i = 0; i < numCascades; i++ )
	{
		const shadowData_ortho_t &data = GetDeferredExt()->GetShadowData_Ortho( i );
		int iCurRegister = iFirstRegister + i * 3;

		pShaderAPI->SetPixelShaderConstant( iCurRegister, data.matWorldToTexture.Base(), 3 );
		iCurRegister += i;
		iCurRegister += stepsLeft * 3;
		pShaderAPI->SetPixelShaderConstant( iCurRegister, data.vecUVTransform.Base() );
		iCurRegister += numCascades;
		pShaderAPI->SetPixelShaderConstant( iCurRegister, data.vecSlopeSettings.Base() );
		iCurRegister += numCascades;

		float fl_0[4] = { 0, 0, 0, 0 };
		float fl_1[4] = { 0, 0, 0, 0 };

		MakeShadowProjectionConstants( fl_0, fl_1, data.iRes_x, data.iRes_y );
		
		pShaderAPI->SetPixelShaderConstant( iCurRegister, fl_0 );
		iCurRegister += numCascades;
		pShaderAPI->SetPixelShaderConstant( iCurRegister, fl_1 );

		stepsLeft--;
	}
}

FORCEINLINE void CommitShadowProjectionConstants_DPSM( IShaderDynamicAPI *pShaderAPI,
	int iFirstRegister )
{
	shadowData_general_t data = GetDeferredExt()->GetShadowData_General();

	float fl_0[4] = { 0, 0, 0, 0 };
	float fl_1[4] = { 0, 0, 0, 0 };

	MakeShadowProjectionConstants( fl_0, fl_1, data.iDPSM_Res_x, data.iDPSM_Res_y );

	pShaderAPI->SetPixelShaderConstant( iFirstRegister++, fl_0 );
	pShaderAPI->SetPixelShaderConstant( iFirstRegister, fl_1 );
}

FORCEINLINE void CommitShadowProjectionConstants_Proj( IShaderDynamicAPI *pShaderAPI,
	int iFirstRegister )
{
	shadowData_general_t data = GetDeferredExt()->GetShadowData_General();

	float fl_0[4] = { 0, 0, 0, 0 };
	float fl_1[4] = { 0, 0, 0, 0 };

	MakeShadowProjectionConstants( fl_0, fl_1, data.iPROJ_Res, data.iPROJ_Res );

	pShaderAPI->SetPixelShaderConstant( iFirstRegister++, fl_0 );
	pShaderAPI->SetPixelShaderConstant( iFirstRegister, fl_1 );
}

FORCEINLINE void CommitViewVertexShader( IShaderDynamicAPI *pShaderAPI,
	int iRegView )
{
	VMatrix v;
	v.Identity();
	pShaderAPI->GetMatrix( MATERIAL_VIEW, v.Base() );
	v = v.Transpose();
	pShaderAPI->SetVertexShaderConstant( iRegView, v.Base(), 3 );
}

FORCEINLINE Vector4D MakeHalfAmbient( Vector4D ambient_low, Vector4D ambient_high )
{
	Vector4D lowDelta = ambient_low - ambient_high;
	lowDelta = ambient_high + lowDelta * 0.5f;
	for (int i = 0; i < 3; i++)
		lowDelta[i] = MAX(0,lowDelta[i]);
	return lowDelta;
}

FORCEINLINE void CommitFullScreenTexel( IShaderDynamicAPI *pShaderAPI,
	int iConstantRegister, float flScale = 1.0f )
{
	int w, t;
	pShaderAPI->GetBackBufferDimensions( w, t );
	float fl4[4] = { flScale / w, flScale / t, 0, 0 };
	pShaderAPI->SetPixelShaderConstant( iConstantRegister, fl4 );
}

FORCEINLINE void CommitHalfScreenTexel( IShaderDynamicAPI *pShaderAPI,
	int iConstantRegister, float flScale = 1.0f )
{
	CommitFullScreenTexel( pShaderAPI, iConstantRegister, flScale * 0.5f );
}


#endif