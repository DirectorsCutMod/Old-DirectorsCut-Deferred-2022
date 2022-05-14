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

#ifndef PROJECTABLE_FACTORY_H
#define PROJECTABLE_FACTORY_H

#include "cbase.h"
#include "deferred/vgui/vgui_deferred.h"

typedef CVGUIProjectable* (*pfnGetProjInstance)();

namespace CProjectableFactory
{
	extern bool AddProjectableFactory( pfnGetProjInstance pFn, const char *pszName );
	extern CVGUIProjectable *AllocateProjectableByName( const char *pszName );
	extern CVGUIProjectable *AllocateProjectableByScript( const char *pszFileName );

	class CProjectableManager : public CAutoGameSystemPerFrame
	{
		friend class CVGUIProjectable;
	public:
		CProjectableManager();

		bool Init();
		void Update( float frametime );

	private:
		void RegisterHelpers();

		void AddThinkTarget( CVGUIProjectable *panel );
		void RemoveThinkTarget( CVGUIProjectable *panel );
		CUtlVector< CVGUIProjectable* > m_hInstantiatedPanels;
	};
	extern CProjectableManager *GetProjectableManager();

	class CProjectableHelper
	{
	public:
		static CProjectableHelper *m_pLastHelper;
		CProjectableHelper *m_pNext;

		CProjectableHelper( pfnGetProjInstance pFn, const char *pszName )
		{
			// assumes that we point to a string literal
			m_pszName = pszName;
			m_pFn = pFn;

			m_pNext = m_pLastHelper;
			m_pLastHelper = this;
		};

		const char *m_pszName;
		pfnGetProjInstance m_pFn;
	};
}


#define REGISTER_PROJECTABLE_FACTORY( className, identifierName )\
	static CVGUIProjectable *GetInstanceOf##className()\
	{\
		return new className();\
	};\
	static CProjectableFactory::CProjectableHelper helper##className( GetInstanceOf##className, identifierName );

#endif