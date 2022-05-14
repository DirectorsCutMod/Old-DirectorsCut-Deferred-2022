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
#include "deferred/vgui/vgui_deferred.h"

#include "vgui/ISurface.h"


using namespace vgui;

REGISTER_PROJECTABLE_FACTORY( CVGUIMarquee, "marquee" );

CVGUIMarquee::CVGUIMarquee( const wchar_t *pszText, const int ispeed )
{
	m_pszText = NULL;
	Q_snprintf( m_szFont, sizeof( m_szFont ), "default" );

	SetText( pszText );
	SetMoveSpeed( ispeed );

	m_Font = 0;
	m_flCurOffset = 0;
}

CVGUIMarquee::~CVGUIMarquee()
{
	delete [] m_pszText;
}

void CVGUIMarquee::SetText( const wchar_t *pszText )
{
	delete [] m_pszText;

	if ( pszText == NULL || *pszText == '\0' )
	{
		pszText = NULL;
		return;
	}

	int textLen = Q_wcslen( pszText ) + 1;
	m_pszText = new wchar_t[ textLen ];
	Q_wcsncpy( m_pszText, pszText, textLen * sizeof( wchar_t ) );
}

void CVGUIMarquee::SetFont( vgui::HFont font )
{
	m_Font = font;
}

void CVGUIMarquee::SetMoveSpeed( const float flspeed )
{
	m_flMoveDir = flspeed;
}

void CVGUIMarquee::ApplySchemeSettings( vgui::IScheme *scheme )
{
	BaseClass::ApplySchemeSettings( scheme );
	m_Font = scheme->GetFont( m_szFont );
}

void CVGUIMarquee::ApplyConfig( KeyValues *pKV )
{
	BaseClass::ApplyConfig( pKV );

	SetText( pKV->GetWString( "text", L"No text in marquee script!" ) );
	SetMoveSpeed( pKV->GetFloat( "speed" ) );
	Q_snprintf( m_szFont, sizeof( m_szFont ), "%s", pKV->GetString( "font", m_szFont ) );
}

void CVGUIMarquee::Paint()
{
	BaseClass::Paint();

	if ( m_pszText == NULL )
		return;

	int w, t;
	GetSize( w, t );

	int strWidth, strTall;
	surface()->GetTextSize( m_Font, m_pszText, strWidth, strTall );

	if ( strWidth < 1 )
		return;

	int iWalk = -strWidth + m_flCurOffset;

	surface()->DrawSetTextColor( GetFgColor() );
	surface()->DrawSetTextFont( m_Font );

	while ( iWalk < w )
	{
		surface()->DrawSetTextPos( iWalk, t * 0.5f - strTall * 0.5f );
		surface()->DrawPrintText( m_pszText, Q_wcslen( m_pszText ) );

		iWalk += strWidth;
	}
}

void CVGUIMarquee::OnThink()
{
	if ( m_pszText == NULL )
		return;

	int strWidth, strTall;
	surface()->GetTextSize( m_Font, m_pszText, strWidth, strTall );

	if ( strWidth < 1 )
		return;

	m_flCurOffset += m_flMoveDir * gpGlobals->frametime;

	while ( abs( m_flCurOffset ) > strWidth )
		m_flCurOffset -= strWidth * Sign( m_flCurOffset );
}