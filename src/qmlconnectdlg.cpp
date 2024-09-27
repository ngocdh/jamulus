#include "qmlconnectdlg.h"

QmlConnectDlg::QmlConnectDlg( CClient* pClnt )
{
    pClient = pClnt;

}

void QmlConnectDlg::connect( const QString &serveraddr ){

    if ( pClient->IsRunning() )
    {
        pClient->Stop();
        return;
    }

    pClient->SetServerAddr( serveraddr );
    pClient->ChannelInfo.strName = "qml"; //TODO - read from Profile page
    pClient->Start();    
}
