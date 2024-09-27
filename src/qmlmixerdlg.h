#ifndef QMLMIXERDLG_H
#define QMLMIXERDLG_H

#include <QObject>

#include "client.h"
#include "global.h"

class QmlMixerDlg : public QObject
{
    Q_OBJECT

public:
    QmlMixerDlg ( CClient* );
    QString sClientList;

private:
    bool bPracticeMode;
    CClient * pClient;
    CVector<CChannelInfo> vChanInfo;
    int iMyChannelId;

public slots:
    void PracticeMode();
    void Refresh();
    void OnConClientListMesReceived ( CVector<CChannelInfo> vecChanInfo );
    void OnClientIDReceived ( int iCh );
};

#endif // QMLMIXERDLG_H
