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

#ifndef VGUI_PROJECTABLE_H
#define VGUI_PROJECTABLE_H

#include "vgui_controls/controls.h"
#include "vgui_controls/panel.h"

class ITexture;

class CVGUIProjectable : public vgui::Panel
{
	DECLARE_CLASS_SIMPLE( CVGUIProjectable, vgui::Panel );
public:

	CVGUIProjectable();
	~CVGUIProjectable();

	void LoadProjectableConfig( KeyValues *pKV );
	void SetControllableName( const char *name );
	void SetParentName( const char *name );

	virtual void DrawSelfToRT( ITexture *pTarget, bool bClear = true );

protected:
	virtual void PerformLayout();
	virtual void ApplySchemeSettings( vgui::IScheme *scheme );

	virtual void ApplyConfig( KeyValues *pKV );

private:
	char *m_pszControllableName;
	char *m_pszParentName;

	KeyValues *m_pConfig;
};


#endif