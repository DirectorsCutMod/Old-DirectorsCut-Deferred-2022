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

#ifndef C_VGUI_EDITOR_PROPS_H
#define C_VGUI_EDITOR_PROPS_H

#include "cbase.h"
#include "vgui_controls/frame.h"


class CVGUILightEditor_Properties : public vgui::Frame
{
	DECLARE_CLASS_SIMPLE( CVGUILightEditor_Properties, vgui::Frame );

public:

	CVGUILightEditor_Properties( vgui::Panel *pParent );
	~CVGUILightEditor_Properties();

	void SendPropertiesToRoot();

	enum PROPERTYMODE
	{
		PROPERTYMODE_LIGHT = 0,
		PROPERTYMODE_GLOBAL,
	};

	PROPERTYMODE GetPropertyMode();
	void SetPropertyMode( PROPERTYMODE mode );
	void OnRequestPropertyLayout( PROPERTYMODE mode );

protected:

	void OnSizeChanged( int newWide, int newTall );

	void PerformLayout();

	MESSAGE_FUNC_PTR( OnPropertyChanged, "PropertyChanged", panel );
	MESSAGE_FUNC( OnLightSelectionChanged, "LightSelectionChanged" );
	MESSAGE_FUNC( OnFileLoaded, "FileLoaded" );

private:

	PROPERTYMODE m_iPropMode;

	vgui::PanelListPanel *m_pListRoot;

	CUtlVector< Panel* > m_hProperties;

	void FlushProperties();
	void UpdatePropertyVisibility();

	void CreateProperties();
	void CreateProperties_LightEntity();
	void CreateProperties_GlobalLight();
	void AddPropertyToList( Panel *panel );

	void PropertiesReadAll();
	void RefreshGlobalLightData();

	KeyValues *AllocKVFromVisible();
};


#endif