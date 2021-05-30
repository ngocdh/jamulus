#ifndef QMLCONNECTDLG_H
#define QMLCONNECTDLG_H

#include <QObject>

#include "client.h"
#include "global.h"

class QmlConnectDlg : public QObject
{
    Q_OBJECT

public:
    QmlConnectDlg( CClient* );
    CClient * Client;

public slots:
    void connect( const QString &serveraddr );
};

#endif // QMLCONNECTDLG_H
