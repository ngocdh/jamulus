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
    
    //edtPlayerId->setValidator( new QIntValidator(0, 100, this) );
    //edtVolume->setValidator(new QIntValidator(0, 100, this));
    
    QFontMetrics m (txtPlayers -> font()) ;
    txtPlayers->setFixedHeight ( 16 * m.lineSpacing() );
    txtPlayers->setReadOnly(true);
    
    for (int i=0;i<=10;i++)
    {
        cmbVolume->addItem("Volume " + QString::number(i * 10));
        cmbReverb->addItem("Reverb " + QString::number(i * 10));
    }
    
    cmbInputGain->addItem("0 Input Gain");
    for (int i=2;i<=10;i++) cmbInputGain->addItem("Gain x" + QString::number(i));
    
    cmbBuffer->addItem("64",1);
    cmbBuffer->addItem("128",2);
    cmbBuffer->addItem("256",4);
    cmbBuffer->setCurrentIndex(1);
    
    cmbQuality->addItem("High", 2);
    cmbQuality->addItem("Normal", 1);
    cmbQuality->addItem("Low", 0);
    cmbQuality->setCurrentIndex(1);
    
    cmbChannels->addItem("Stereo",2);
    cmbChannels->addItem("Mono in-Stereo out",1);
    cmbChannels->addItem("Mono",0);
    cmbChannels->setCurrentIndex(0);
    
    cmbDevice->addItem("AutoDev", 0);
    cmbDevice->addItem("ManualDev", 20);//iOS: any value>0, Android: must find exact value
    
    InitValues();
    
    CHostAddress CentralServerAddress;

    if ( NetworkUtil().ParseNetworkAddress (
                 NetworkUtil::GetCentralServerAddress ( ECSAddType::AT_DEFAULT , "" ),
                 CentralServerAddress ) )
    {
        // send the request for the server list
        pClient->CreateCLReqServerListMes ( CentralServerAddress );
    }

    QObject::connect ( pClient, &CClient::ConClientListMesReceived, this, &CConnectDlg::OnConClientListMesReceived );
    QObject::connect ( pClient, &CClient::ClientIDReceived, this, &CConnectDlg::OnClientIDReceived );
    QObject::connect ( pClient, &CClient::CLServerListReceived, this, &CConnectDlg::OnCLServerListReceived );


    QObject::connect ( butConnect, &QPushButton::clicked, this, &CConnectDlg::OnConnectClicked );
    QObject::connect ( butPracticeMode, &QPushButton::clicked, this, &CConnectDlg::OnPracticeModeClicked );
    //QObject::connect( butGetServerList, &QPushButton::clicked, this, &CConnectDlg::OnGetServerListClicked );
    
    //QObject::connect ( but64, &QPushButton::clicked, this, &CConnectDlg::On64Clicked );
    //QObject::connect ( but128, &QPushButton::clicked, this, &CConnectDlg::On128Clicked );
    //QObject::connect ( but256, &QPushButton::clicked, this, &CConnectDlg::On256Clicked );
    QObject::connect ( butSetVolume, &QPushButton::clicked, this, &CConnectDlg::OnSetVolumeClicked );
    
    QObject::connect ( edtName, &QLineEdit::textChanged, this, &CConnectDlg::OnEdtNameChanged );
    
    //QObject::connect ( sliderVolume, &QSlider::valueChanged, this, &CConnectDlg::OnVolSliderChanged );
    QObject::connect ( cmbPlayers, static_cast<void ( QComboBox::* ) ( int )> ( &QComboBox::activated ), this, &CConnectDlg::OnCmbPlayersChanged );
    QObject::connect ( cmbBuffer, static_cast<void ( QComboBox::* ) ( int )> ( &QComboBox::activated ), this, &CConnectDlg::OnCmbBufferChanged );
    QObject::connect ( cmbQuality, static_cast<void ( QComboBox::* ) ( int )> ( &QComboBox::activated ), this, &CConnectDlg::OnCmbQualityChanged );
    QObject::connect ( cmbChannels, static_cast<void ( QComboBox::* ) ( int )> ( &QComboBox::activated ), this, &CConnectDlg::OnCmbChannelsChanged );
    QObject::connect ( cmbDevice, static_cast<void ( QComboBox::* ) ( int )> ( &QComboBox::activated ), this, &CConnectDlg::OnCmbDeviceChanged );
    QObject::connect ( cmbReverb, static_cast<void ( QComboBox::* ) ( int )> ( &QComboBox::activated ), this, &CConnectDlg::OnCmbReverbChanged );
    QObject::connect ( cmbInputGain, static_cast<void ( QComboBox::* ) ( int )> ( &QComboBox::activated ), this, &CConnectDlg::OnCmbInputGainChanged );
    
    QObject::connect ( cmbServerList, static_cast<void ( QComboBox::* ) ( int )> ( &QComboBox::activated ), this, &CConnectDlg::OnCmbServerListChanged );
    
    
    

}

void CConnectDlg::OnConClientListMesReceived ( CVector<CChannelInfo> vecChanInfo )
{
    vChanInfo = vecChanInfo;
    int n = vecChanInfo.Size();
    /*if ( n > 0 )
    {
        qDebug() << "Musician 0's name: " << vecChanInfo[0].strName;
        sClientList = vecChanInfo[0].strName;
    }*/
    qDebug() << "People in room: " << n;
    txtPlayers->clear();
    cmbPlayers->clear();
    int iMyIndex;
    for(int i = 0; i < n; i++)
    {
        QString info = QString::number( vecChanInfo[i].iChanID ) + " - " + vecChanInfo[i].strName;
        if ( vecChanInfo[i].iChanID == iMyChannelId )
        {
            info = info + "\t\t <= ME";
            iMyIndex = i;
        }
        qDebug() << info;
        txtPlayers->append(info);
        cmbPlayers->addItem(info, QString::number( vecChanInfo[i].iChanID ));
        
    }
    cmbPlayers->setCurrentIndex(iMyIndex);
    //but64->setFocus();

}

void CConnectDlg::OnClientIDReceived ( int iCh )
{
    iMyChannelId = iCh;
    qDebug() << "Received My channel Id: " << iCh;
    butConnect->setText( "Disconnect" );
    //edtPlayerId->setText(QString::number(iCh));
}

void CConnectDlg::OnConnectClicked()
{
    
    strSelectedAddress = NetworkUtil::FixAddress ( edtServerAddress->text() );

    if ( pClient->IsRunning() ) //disconnect if connected
    {
        pClient->Stop();
        InitValues();
        butConnect->setText( "Connect" );
        return;
    }
    
    pClient->SetServerAddr(strSelectedAddress);
    pClient->ChannelInfo.strName = edtName->text();
    pClient->Start();
    
    
}

void CConnectDlg::showEvent ( QShowEvent* )
{


}

void CConnectDlg::OnPracticeModeClicked()
{
    bPracticeMode = !bPracticeMode;
    pClient->SetMuteOutStream(bPracticeMode);
    if (!bPracticeMode) butPracticeMode->setText("PracticeMode");
        else butPracticeMode->setText("NormalMode");
}

void CConnectDlg::On64Clicked()
{
    pClient->SetSndCrdPrefFrameSizeFactor(1);
}
void CConnectDlg::On128Clicked()
{
    pClient->SetSndCrdPrefFrameSizeFactor(2);
}
void CConnectDlg::On256Clicked()
{
    pClient->SetSndCrdPrefFrameSizeFactor(4);
}
void CConnectDlg::OnSetVolumeClicked()
{
    pClient->SetRemoteChanGain(cmbPlayers->currentData().toInt(), cmbVolume->currentIndex()/10.00, cmbPlayers->currentData().toInt()==iMyChannelId);
}

void CConnectDlg::OnVolSliderChanged()
{
//    edtVolume->setText(QString::number(sliderVolume->value()));
//    pClient->SetRemoteChanGain(edtPlayerId->text().toInt(), edtVolume->text().toInt()/100.00, edtPlayerId->text().toInt()==iMyChannelId);
}

void CConnectDlg::OnCmbPlayersChanged()
{
    //edtPlayerId->setText(cmbPlayers->currentData().toString());
}

void CConnectDlg::OnCmbBufferChanged()
{
    pClient->SetSndCrdPrefFrameSizeFactor(cmbBuffer->currentData().toInt());
}
void CConnectDlg::OnCmbQualityChanged()
{
    pClient->SetAudioQuality(static_cast<EAudioQuality> (cmbBuffer->currentData().toInt()));
}
void CConnectDlg::OnCmbChannelsChanged()
{
    pClient->SetAudioChannels(static_cast<EAudChanConf> (cmbBuffer->currentData().toInt()));
}
void CConnectDlg::OnCmbDeviceChanged()
{
    pClient->SetInputDeviceId(cmbDevice->currentData().toInt());
    //pClient->SetBuiltInMicId(cmbDevice->currentData().toInt());
}
void CConnectDlg::OnCmbInputGainChanged()
{
    pClient->SetInputBoost(cmbInputGain->currentIndex() + 1);
}
void CConnectDlg::OnCmbReverbChanged()
{
    pClient->SetReverbLevel(cmbReverb->currentIndex() * 10) ;
}

void CConnectDlg::OnEdtNameChanged()
{
    pClient->ChannelInfo.strName = edtName->text();

    // update channel info at the server
    pClient->SetRemoteInfo();

}

void CConnectDlg::OnGetServerListClicked()
{
    CHostAddress CentralServerAddress;

    if ( NetworkUtil().ParseNetworkAddress (
                 NetworkUtil::GetCentralServerAddress ( ECSAddType::AT_DEFAULT , "" ),
                 CentralServerAddress ) )
    {
        // send the request for the server list
        pClient->CreateCLReqServerListMes ( CentralServerAddress );
    }
    //pClient->CreateCLReqServerListMes ( CHostAddress(QHostAddress("anygenre1.jamulus.io"),22124) );
    //qDebug("sending server request");
    //pClient->Serverlist
}

void CConnectDlg::OnCLServerListReceived ( CHostAddress InetAddr, CVector<CServerInfo> vecServerInfo )
{
    //ConnectDlg.SetServerList ( InetAddr, vecServerInfo );
    //qDebug(" Received Server list: %d", vecServerInfo.size());
    cmbServerList->clear();
    cmbServerList->addItem( "Servers", "0.0.0.0" );
    for ( uint i=1; i < vecServerInfo.size(); i++ )
    {
        cmbServerList->addItem( vecServerInfo[i].strName + " - " + vecServerInfo[i].strCity, vecServerInfo[i].HostAddr.toString() );
    }
}

void CConnectDlg::OnCmbServerListChanged()
{
    edtServerAddress->setText(cmbServerList->currentData().toString());
/*
    strSelectedAddress = NetworkUtil::FixAddress ( cmbServerList->currentData().toString() );
    if ( pClient->IsRunning() ) //disconnect if connected
    {
        pClient->Stop();
        InitValues();
        butConnect->setText( "Connect" );
    }
    
    pClient->SetServerAddr(strSelectedAddress);
    pClient->ChannelInfo.strName = edtName->text();
    pClient->Start();*/
    
}

void CConnectDlg::InitValues()
{
    txtPlayers->clear();
    cmbPlayers->clear();
    cmbPlayers->addItem("Players");
    iMyChannelId = -1;
    
}
