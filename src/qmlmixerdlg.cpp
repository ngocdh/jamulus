#include "qmlmixerdlg.h"
#include <QtDebug>

QmlMixerDlg::QmlMixerDlg( CClient* pClnt )
{
    pClient = pClnt;
    bPracticeMode = false;
    sClientList = "";

    QObject::connect ( pClient, &CClient::ConClientListMesReceived, this, &QmlMixerDlg::OnConClientListMesReceived );
    QObject::connect ( pClient, &CClient::ClientIDReceived, this, &QmlMixerDlg::OnClientIDReceived );
    //QObject::connect ( pClient, &CClient::ChatTextReceived, this, &QmlMixerDlg::OnChatTextReceived ); //Notification popup, and chat textarea
/*TODO
    QObject::connect ( pClient, &CClient::Disconnected, this, &CClientDlg::OnDisconnected );
    QObject::connect ( butConnect, &QPushButton::clicked, this, &CClientDlg::OnConnectDisconBut );

    QObject::connect ( rbtReverbSelL, &QRadioButton::clicked, this, &CClientDlg::OnReverbSelLClicked );
    QObject::connect ( rbtReverbSelR, &QRadioButton::clicked, this, &CClientDlg::OnReverbSelRClicked );
    QObject::connect ( sldAudioReverb, &QSlider::valueChanged, this, &CClientDlg::OnAudioReverbValueChanged );


    QObject::connect ( MainMixerBoard, &CAudioMixerBoard::ChangeChanGain, this, &QmlMixerDlg::OnChangeChanGain );

    QObject::connect ( MainMixerBoard, &CAudioMixerBoard::ChangeChanPan, this, &QmlMixerDlg::OnChangeChanPan );
*/
}

void QmlMixerDlg::PracticeMode()
{
    bPracticeMode = ! bPracticeMode;
    pClient->SetMuteOutStream( bPracticeMode );
}

void QmlMixerDlg::Refresh()
{
    //printf("Yeah, refresh clicked %d ", vChanInfo.Size());
}

void QmlMixerDlg::OnConClientListMesReceived ( CVector<CChannelInfo> vecChanInfo )
{
    vChanInfo = vecChanInfo;
    int n = vecChanInfo.Size();
    /*if ( n > 0 )
    {
        qDebug() << "Musician 0's name: " << vecChanInfo[0].strName;
        sClientList = vecChanInfo[0].strName;
    }*/
    qDebug() << "People in room: " << n;
    for(int i = 0; i < n; i++)
    {
        QString info = QString::number( vecChanInfo[i].iChanID ) + " - " + vecChanInfo[i].strName;
        qDebug() << info;
    }

}

void QmlMixerDlg::OnClientIDReceived ( int iCh )
{
    iMyChannelId = iCh;
    qDebug() << "Received My channel Id: " << iCh;
}
