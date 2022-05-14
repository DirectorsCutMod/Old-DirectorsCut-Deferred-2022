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

#ifndef C_VGUI_EDITOR_CONTROLS_H
#define C_VGUI_EDITOR_CONTROLS_H

#include "cbase.h"
#include "vgui_controls/frame.h"


class CVGUILightEditor_Controls : public vgui::Frame
{
	DECLARE_CLASS_SIMPLE( CVGUILightEditor_Controls, vgui::Frame );

public:

	CVGUILightEditor_Controls( vgui::Panel *pParent );
	~CVGUILightEditor_Controls();

protected:

	void PerformLayout();

	MESSAGE_FUNC( OnLevelSpawn, "LevelSpawn" );

	MESSAGE_FUNC_PTR( OnRadioButtonChecked, "RadioButtonChecked", panel );
	MESSAGE_FUNC_PTR( OnCheckButtonChecked, "CheckButtonChecked", panel );
	MESSAGE_FUNC_PTR( OnTextChanged, "TextChanged", panel );

	MESSAGE_FUNC_PARAMS( OnFileSelected, "FileSelected", pKV );

	void OnCommand( const char *pCmd );

private:

	void OnLoadVmf();
	void LoadVmf( const char *pszPath );

	void BuildVmfPath( char *pszOut, int maxlen, bool bMakeRelative = true );
	bool BuildCurrentVmfPath( char *pszOut, int maxlen );
	void OpenVmfFileDialog();
	vgui::FileOpenDialog *m_pFileVmf;
	vgui::DirectorySelectDialog *m_pDirVmf;
	vgui::ComboBox *m_pCBoxDbg;
};

#endif