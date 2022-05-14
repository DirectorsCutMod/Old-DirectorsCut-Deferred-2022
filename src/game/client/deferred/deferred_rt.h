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

#ifndef DEFERRED_RT_H
#define DEFERRED_RT_H

class ITexture;

float GetDepthMapDepthResolution( float zDelta );
void DefRTsOnModeChanged();
void InitDeferredRTs( bool bInitial = false );

ITexture *GetDefRT_Normals();
ITexture *GetDefRT_Depth();
ITexture *GetDefRT_Albedo();
ITexture *GetDefRT_Specular();
ITexture *GetDefRT_LightCtrl();
ITexture *GetDefRT_Lightaccum();

ITexture *GetDefRT_VolumePrepass();
ITexture *GetDefRT_VolumetricsBuffer( int index );

ITexture *GetDefRT_RadiosityBuffer( int index );
ITexture *GetDefRT_RadiosityNormal( int index );

int GetShadowResolution_Spot();
int GetShadowResolution_Point();

#if DEFCFG_ADAPTIVE_SHADOWMAP_LOD
int GetShadowResolution_Spot_LOD1();
int GetShadowResolution_Spot_LOD2();


int GetShadowResolution_Point_LOD1();
int GetShadowResolution_Point_LOD2();
#endif

#if DEFCFG_ADAPTIVE_SHADOWMAP_LOD
int GetShadowResolution_Point_LOD1()
{
	return deferred_rt_shadowpoint_lod1_res.GetInt();
}

int GetShadowResolution_Point_LOD2()
{
	return deferred_rt_shadowpoint_lod2_res.GetInt();
}
#endif

ITexture *GetShadowColorRT_Ortho( int index );
ITexture *GetShadowDepthRT_Ortho( int index );

ITexture *GetShadowColorRT_Proj( int index );
ITexture *GetShadowDepthRT_Proj( int index );

ITexture *GetShadowColorRT_DP( int index );
ITexture *GetShadowDepthRT_DP( int index );

ITexture *GetProjectableVguiRT( int index );

ITexture *GetRadiosityAlbedoRT_Ortho( int index );
ITexture *GetRadiosityNormalRT_Ortho( int index );

#endif