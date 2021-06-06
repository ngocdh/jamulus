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

#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWhatsThis>
#include <QTimer>
#include <QLocale>
#include <QtConcurrent>
#include "global.h"
#include "util.h"
#include "settings.h"
#include "multicolorled.h"
#include "ui_connectdlgbase.h"

/* Definitions ****************************************************************/
// defines the time interval at which the request server list message is re-
// transmitted until it is received
#define SERV_LIST_REQ_UPDATE_TIME_MS 2000 // ms

/* Classes ********************************************************************/
class CConnectDlg : public CBaseDlg, private Ui_CConnectDlgBase
{
    Q_OBJECT

public:
    CConnectDlg ( CClient* pNCliP, CClientSettings*, QWidget* parent = nullptr );

protected:
    virtual void showEvent ( QShowEvent* );
    void InitValues();

    CClientSettings* pSettings;
    CClient*         pClient;
    QString      strSelectedAddress;
    QString      strSelectedServerName;
    
    bool         bPracticeMode = false;
    
    CVector<CChannelInfo> vChanInfo;
    int iMyChannelId;

public slots:
    void OnConnectClicked();
    void On64Clicked();
    void On128Clicked();
    void On256Clicked();
    void OnSetVolumeClicked();
    void OnPracticeModeClicked();
    void OnVolSliderChanged();
    void OnCmbPlayersChanged();
    void OnCmbBufferChanged();
    void OnCmbQualityChanged();
    void OnCmbChannelsChanged();
    void OnCmbDeviceChanged();
    void OnEdtNameChanged();
    
    void OnConClientListMesReceived ( CVector<CChannelInfo> vecChanInfo );
    void OnClientIDReceived ( int iCh );
    

signals:
    void ReqServerListQuery ( CHostAddress InetAddr );
    void CreateCLServerListPingMes ( CHostAddress InetAddr );
    void CreateCLServerListReqVerAndOSMes ( CHostAddress InetAddr );
    void CreateCLServerListReqConnClientsListMes ( CHostAddress InetAddr );
};
