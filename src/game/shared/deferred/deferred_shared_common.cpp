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


INetworkStringTable *g_pStringTable_LightCookies = NULL;


static const char *g_pszLightParamNames[ LPARAM_COUNT ] =
{
	"diffuse",
	"ambient",
	"radius",
	"power",
	"spot_cone_inner",
	"spot_cone_outer",
	"vis_dist",
	"vis_range",
	"shadow_dist",
	"shadow_range",
	"light_type",
	"cookietex",
	"style_amt",
	"style_speed",
	"style_smooth",
	"style_random",
	"style_seed",

	"spawnFlags",
	"angles",
	"origin",

	"ambient_low",
	"ambient_high",

#if DEFCFG_ADAPTIVE_VOLUMETRIC_LOD
	"volume_lod0_dist",
	"volume_lod1_dist",
	"volume_lod2_dist",
	"volume_lod3_dist",
#endif
#if DEFCFG_CONFIGURABLE_VOLUMETRIC_LOD
	"volume_samples",
#endif
};

const char *GetLightParamName( LIGHT_PARAM_ID id )
{
	Assert( id >= 0 && id < LPARAM_COUNT );

	return g_pszLightParamNames[ id ];
}

void UTIL_StringToIntArray( int *pVector, int count, const char *pString )
{
	char *pstr, *pfront, tempString[128];
	int	j;

	Q_strncpy( tempString, pString, sizeof(tempString) );
	pstr = pfront = tempString;

	for ( j = 0; j < count; j++ )			// lifted from pr_edict.c
	{
		pVector[j] = atoi( pfront );

		// skip any leading whitespace
		while ( *pstr && *pstr <= ' ' )
			pstr++;

		// skip to next whitespace
		while ( *pstr && *pstr > ' ' )
			pstr++;

		if (!*pstr)
			break;

		pstr++;
		pfront = pstr;
	}
	for ( j++; j < count; j++ )
	{
		pVector[j] = 0;
	}
}