#include "qmlconnectdlg.h"

QmlConnectDlg::QmlConnectDlg( CClient* pClient )
{
    Client = pClient;

}

void QmlConnectDlg::connect( const QString &serveraddr ){

    if ( Client->IsConnected() )
        Client->Stop();
    Client->SetServerAddr( serveraddr );
    Client->Start();
}
