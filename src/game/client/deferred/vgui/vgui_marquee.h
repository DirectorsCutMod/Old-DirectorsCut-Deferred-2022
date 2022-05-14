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

#ifndef VGUI_MARQUEE_H
#define VGUI_MARQUEE_H

#include "vgui_controls/controls.h"
#include "deferred/vgui/vgui_projectable.h"


class CVGUIMarquee : public CVGUIProjectable
{
	DECLARE_CLASS_SIMPLE( CVGUIMarquee, CVGUIProjectable );
public:

	CVGUIMarquee( const wchar_t *pszText = NULL, const int ispeed = 5 );
	~CVGUIMarquee();

	void SetText( const wchar_t *pszText );
	void SetFont( vgui::HFont font );
	void SetMoveSpeed( const float flspeed );

protected:
	virtual void ApplySchemeSettings( vgui::IScheme *scheme );

	virtual void Paint();
	virtual void OnThink();

	virtual void ApplyConfig( KeyValues *pKV );

private:

	wchar_t *m_pszText;
	char m_szFont[32];
	vgui::HFont m_Font;

	float m_flMoveDir;
	float m_flCurOffset;

};


#endif