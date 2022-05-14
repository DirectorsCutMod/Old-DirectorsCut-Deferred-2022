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

#ifndef CDEF_LIGHT_CONTAINER_H
#define CDEF_LIGHT_CONTAINER_H

#include "cbase.h"

class CDeferredLight;

class CDeferredLightContainer : public CBaseEntity
{
	DECLARE_CLASS( CDeferredLightContainer, CBaseEntity );
	DECLARE_NETWORKCLASS();

public:

	CDeferredLightContainer();
	~CDeferredLightContainer();

#ifdef GAME_DLL
	virtual void Activate();

	virtual int UpdateTransmitState();

	void AddWorldLight( CDeferredLight *l );
#else
	virtual void PostDataUpdate( DataUpdateType_t type );

	virtual void UpdateOnRemove();

	virtual void ReadWorldLight( int index, def_light_t &l );
#endif

	int GetLightsAmount();

private:

/*
	floats vector3d
	origin 123
	angles 123
	coldiff 123
	colamb 123
	style 123
	ranges 123
	stylew 1 radius 2 power 3
	ranges 1 cinner 2 couter 3

	ints
	styleseed(15) cookie(7) flags(5) lighttype(1)
*/

	CNetworkArray( Vector, m_pos, DEFLIGHTCONTAINER_MAXLIGHTS );
	CNetworkArray( QAngle, m_ang, DEFLIGHTCONTAINER_MAXLIGHTS );
	CNetworkArray( Vector, m_col_diff, DEFLIGHTCONTAINER_MAXLIGHTS );
	CNetworkArray( Vector, m_col_amb, DEFLIGHTCONTAINER_MAXLIGHTS );
	CNetworkArray( Vector, m_style_amt_speed_smooth, DEFLIGHTCONTAINER_MAXLIGHTS );
	CNetworkArray( Vector, m_ranges_vdist_vrange_sdist, DEFLIGHTCONTAINER_MAXLIGHTS );
	CNetworkArray( Vector, m_style_ran_radius_power, DEFLIGHTCONTAINER_MAXLIGHTS );
	CNetworkArray( Vector, m_ranges_srange_cinner_couter, DEFLIGHTCONTAINER_MAXLIGHTS );

	CNetworkArray( int, m_type_flags_cookieindex_seed, DEFLIGHTCONTAINER_MAXLIGHTS );

	CNetworkVar( int, m_iLightCount );

#ifdef GAME_DLL
	void SetEncodedDataInt( const int index,
		int seed, int cookie, int flags, int lighttype );
#endif
	void ReadEncodedDataInt( const int index,
		ushort &seed, uint8 &cookie, uint8 &flags, uint8 &lighttype );

#ifdef CLIENT_DLL
	int m_iSanityCounter;

	CUtlVector< def_light_t* > m_hLights;
#endif

};

int GetNumLightContainers();
CDeferredLightContainer *GetLightContainer( int index );
CDeferredLightContainer *FindAvailableContainer();

#endif