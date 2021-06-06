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
    
    edtPlayerId->setValidator( new QIntValidator(0, 100, this) );
    edtVolume->setValidator(new QIntValidator(0, 100, this));
    
    QFontMetrics m (txtPlayers -> font()) ;
    txtPlayers->setFixedHeight ( 16 * m.lineSpacing() );
    txtPlayers->setReadOnly(true);
    
    sliderVolume->setRange(0, 100);
    sliderVolume->setTickInterval(10);
    sliderVolume->setOrientation(Qt::Horizontal);
    sliderVolume->setFixedHeight(2 * m.lineSpacing());

    QObject::connect ( pClient, &CClient::ConClientListMesReceived, this, &CConnectDlg::OnConClientListMesReceived );
    QObject::connect ( pClient, &CClient::ClientIDReceived, this, &CConnectDlg::OnClientIDReceived );


    QObject::connect ( butConnect, &QPushButton::clicked, this, &CConnectDlg::OnConnectClicked );
    QObject::connect ( butPracticeMode, &QPushButton::clicked, this, &CConnectDlg::OnPracticeModeClicked );
    QObject::connect ( but64, &QPushButton::clicked, this, &CConnectDlg::On64Clicked );
    QObject::connect ( but128, &QPushButton::clicked, this, &CConnectDlg::On128Clicked );
    QObject::connect ( but256, &QPushButton::clicked, this, &CConnectDlg::On256Clicked );
    QObject::connect ( butSetVolume, &QPushButton::clicked, this, &CConnectDlg::OnSetVolumeClicked );
    
    QObject::connect ( edtName, &QLineEdit::textChanged, this, &CConnectDlg::OnEdtNameChanged );
    
    QObject::connect ( sliderVolume, &QSlider::valueChanged, this, &CConnectDlg::OnVolSliderChanged );
    QObject::connect ( cmbPlayers, static_cast<void ( QComboBox::* ) ( int )> ( &QComboBox::activated ), this, &CConnectDlg::OnCmbPlayersChanged );
    
    

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
    for(int i = 0; i < n; i++)
    {
        QString info = QString::number( vecChanInfo[i].iChanID ) + " - " + vecChanInfo[i].strName;
        qDebug() << info;
        txtPlayers->append(info);
        cmbPlayers->addItem(info, QString::number( vecChanInfo[i].iChanID ));
        
    }
    but64->setFocus();

}

void CConnectDlg::OnClientIDReceived ( int iCh )
{
    iMyChannelId = iCh;
    qDebug() << "Received My channel Id: " << iCh;
    butConnect->setText( "Disconnect" );
    edtPlayerId->setText(QString::number(iCh));
}

void CConnectDlg::OnConnectClicked()
{
    
    strSelectedAddress = NetworkUtil::FixAddress ( edtServerAddress->text() );

    if ( pClient->IsRunning() ) //disconnect if connected
    {
        pClient->Stop();
        txtPlayers->clear();
        cmbPlayers->clear();
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
    pClient->SetRemoteChanGain(edtPlayerId->text().toInt(), edtVolume->text().toInt()/100.00, false);
}

void CConnectDlg::OnVolSliderChanged()
{
    edtVolume->setText(QString::number(sliderVolume->value()));
    pClient->SetRemoteChanGain(edtPlayerId->text().toInt(), edtVolume->text().toInt()/100.00, false);
}

void CConnectDlg::OnCmbPlayersChanged()
{
    edtPlayerId->setText(cmbPlayers->currentData().toString());
}

void CConnectDlg::OnEdtNameChanged()
{
    pClient->ChannelInfo.strName = edtName->text();

    // update channel info at the server
    pClient->SetRemoteInfo();

}
