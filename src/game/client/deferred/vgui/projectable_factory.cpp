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
#include "deferred/vgui/vgui_deferred.h"

#include "vgui/ipanel.h"
#include "filesystem.h"

using namespace CProjectableFactory;

struct ProjMapping
{
	char szName[32];
	pfnGetProjInstance factory;
};

static CUtlVector< ProjMapping > m_hProjectables;

bool CProjectableFactory::AddProjectableFactory( pfnGetProjInstance pFn, const char *pszName )
{
	Assert( Q_strlen( pszName ) < 32 && 
		pszName != NULL &&
		*pszName != '\0' );

#if DEBUG
	for ( int i = 0; i < m_hProjectables.Count(); i++ )
		Assert( Q_stricmp( m_hProjectables[i].szName, pszName ) );
#endif

	ProjMapping entry;
	*entry.szName = '\0';
	Q_snprintf( entry.szName, sizeof( entry.szName ), "%s", pszName );
	entry.factory = pFn;

	m_hProjectables.AddToTail( entry );

	return true;
}

CVGUIProjectable *CProjectableFactory::AllocateProjectableByName( const char *pszName )
{
	for ( int i = 0; i < m_hProjectables.Count(); i++ )
	{
		if ( !Q_stricmp( m_hProjectables[i].szName, pszName ) )
		{
			CVGUIProjectable *pPanel = m_hProjectables[i].factory();
			Assert( pPanel );
			pPanel->MakeReadyForUse();
			return pPanel;
		}
	}

	return null;
}

CVGUIProjectable *CProjectableFactory::AllocateProjectableByScript( const char *pszFileName )
{
	CVGUIProjectable *pPanel = NULL;

	KeyValues *pKV = new KeyValues("");

	bool bSuccess = pKV->LoadFromFile( g_pFullFileSystem, VarArgs( "%s/%s", PATHLOCATION_PROJECTABLE_SCRIPTS, pszFileName ) );
	if ( !bSuccess )
		bSuccess = pKV->LoadFromFile( g_pFullFileSystem, VarArgs( "%s/%s.txt", PATHLOCATION_PROJECTABLE_SCRIPTS, pszFileName ) );

	if ( bSuccess )
	{
		const char *pszFactoryName = pKV->GetString( "factory" );

		if ( pszFactoryName != NULL && *pszFactoryName != '\0' )
			pPanel = AllocateProjectableByName( pszFactoryName );

		if ( pPanel != NULL )
		{
			KeyValues *pConfig = pKV->FindKey( "config" );

			if ( pConfig != NULL )
			{
				pPanel->LoadProjectableConfig( pConfig );
				pPanel->InvalidateLayout( true, true );
			}
		}
	}

	pKV->deleteThis();

	return pPanel;
}


static CProjectableManager g_pProjManager;
CProjectableManager *CProjectableFactory::GetProjectableManager()
{
	return &g_pProjManager;
}

CProjectableManager::CProjectableManager() : CAutoGameSystemPerFrame( "CProjectableManager" )
{
}

CProjectableHelper *CProjectableHelper::m_pLastHelper = NULL;

bool CProjectableManager::Init()
{
	RegisterHelpers();
	return true;
}

void CProjectableManager::Update( float frametime )
{
	for ( int i = 0; i < m_hInstantiatedPanels.Count(); i++ )
	{
		vgui::ipanel()->Think( m_hInstantiatedPanels[i]->GetVPanel() );
	}
}

void CProjectableManager::RegisterHelpers()
{
	for ( CProjectableHelper *pCur = CProjectableHelper::m_pLastHelper;
		pCur; pCur = pCur->m_pNext )
	{
		AddProjectableFactory( pCur->m_pFn, pCur->m_pszName );
	}
}

void CProjectableManager::AddThinkTarget( CVGUIProjectable *panel )
{
	m_hInstantiatedPanels.AddToTail( panel );
}

void CProjectableManager::RemoveThinkTarget( CVGUIProjectable *panel )
{
	m_hInstantiatedPanels.FindAndRemove( panel );
}
