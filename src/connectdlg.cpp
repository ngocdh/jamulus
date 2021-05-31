/******************************************************************************\
 * Copyright (c) 2004-2020
 *
 * Author(s):
 *  Volker Fischer
 *
 ******************************************************************************
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
\******************************************************************************/

#include "connectdlg.h"

/* Implementation *************************************************************/
CConnectDlg::CConnectDlg ( CClient* pNCliP, CClientSettings* Settings, QWidget* parent ) :
    CBaseDlg ( parent, Qt::Dialog )
{
    setupUi ( this );
    
    pClient = pNCliP;
    pSettings = Settings ;

    butConnect->setFocus();



    QObject::connect ( butConnect, &QPushButton::clicked, this, &CConnectDlg::OnConnectClicked );
    QObject::connect ( butPracticeMode, &QPushButton::clicked, this, &CConnectDlg::OnPracticeModeClicked );

}


void CConnectDlg::OnConnectClicked()
{
    
    strSelectedAddress = NetworkUtil::FixAddress ( edtServerAddress->text() );

    if ( pClient->IsConnected() )
        pClient->Stop();
    
    pClient->SetServerAddr(strSelectedAddress);
    pClient->Start();
    
}

void CConnectDlg::showEvent ( QShowEvent* )
{


}

void CConnectDlg::OnPracticeModeClicked()
{
    bPracticeMode = !bPracticeMode;
    pClient->SetMuteOutStream(bPracticeMode);
}
