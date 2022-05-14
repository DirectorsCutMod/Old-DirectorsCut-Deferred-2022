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

#ifndef CDEFERRED_MANAGER_CLIENT_H
#define CDEFERRED_MANAGER_CLIENT_H

#include "cbase.h"

enum DEF_MATERIALS
{
	DEF_MAT_LIGHT_GLOBAL = 0,

	DEF_MAT_LIGHT_POINT_WORLD,
	DEF_MAT_LIGHT_POINT_FULLSCREEN,
	DEF_MAT_LIGHT_SPOT_WORLD,
	DEF_MAT_LIGHT_SPOT_FULLSCREEN,

	DEF_MAT_LIGHT_VOLUME_PREPASS,
	DEF_MAT_LIGHT_VOLUME_BLEND,
	DEF_MAT_LIGHT_VOLUME_POINT_WORLD,
	DEF_MAT_LIGHT_VOLUME_POINT_FULLSCREEN,
	DEF_MAT_LIGHT_VOLUME_SPOT_WORLD,
	DEF_MAT_LIGHT_VOLUME_SPOT_FULLSCREEN,

	DEF_MAT_LIGHT_RADIOSITY_GLOBAL,
	DEF_MAT_LIGHT_RADIOSITY_DEBUG,
	DEF_MAT_LIGHT_RADIOSITY_PROPAGATE_0,
	DEF_MAT_LIGHT_RADIOSITY_PROPAGATE_1,
	DEF_MAT_LIGHT_RADIOSITY_BLUR_0,
	DEF_MAT_LIGHT_RADIOSITY_BLUR_1,
	DEF_MAT_LIGHT_RADIOSITY_BLEND,

#if DEFCFG_DEFERRED_SHADING == 1
	DEF_MAT_SCREENSPACE_SHADING,
	DEF_MAT_SCREENSPACE_COMBINE,
#endif

	DEF_MAT_BLUR_G6_X,
	DEF_MAT_BLUR_G6_Y,

#ifdef DEBUG
	DEF_MAT_WIREFRAME_DEBUG,
#endif

	DEF_MAT_COUNT
};

class CDeferredManagerClient : public CAutoGameSystem
{
	typedef CAutoGameSystem BaseClass;
public:

	CDeferredManagerClient();
	~CDeferredManagerClient();

	virtual bool Init();
	virtual void Shutdown();

	inline bool IsDeferredRenderingEnabled();

	ImageFormat GetShadowDepthFormat();
	ImageFormat GetNullFormat();

	inline IMaterial *GetDeferredMaterial( DEF_MATERIALS mat );

private:

	bool m_bDefRenderingEnabled;

	void InitializeDeferredMaterials();
	void ShutdownDeferredMaterials();

	IMaterial *m_pMat_Def[ DEF_MAT_COUNT ];
	KeyValues *m_pKV_Def[ DEF_MAT_COUNT ];
};

bool CDeferredManagerClient::IsDeferredRenderingEnabled()
{
	return m_bDefRenderingEnabled;
}

IMaterial *CDeferredManagerClient::GetDeferredMaterial( DEF_MATERIALS mat )
{
	Assert( mat >= 0 && mat < DEF_MAT_COUNT );

	return m_pMat_Def[ mat ];
}

extern CDeferredManagerClient *GetDeferredManager();

#endif