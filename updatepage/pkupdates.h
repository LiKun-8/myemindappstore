#ifndef PKUPDATES_H
#define PKUPDATES_H

#include <QObject>
#include <QPointer>
#include <QStringList>
#include <packagekitqt5/PackageKit/Transaction>
#include <packagekitqt5/PackageKit/Daemon>
#include "../jsonfunc.h"
#include "../sharedata.h"

#define MAXUPNUM 100

class PkUpdates : public QObject
{
    Q_OBJECT
public:
    explicit PkUpdates(QObject *parent = nullptr);
    int count() const;
    int insCount() const;
    QStringList getPacName() const;
    QVariantMap packages() const;

    ShareData *shareData;
    JSONFUNC *jsonFunc;
signals:
    void updatesChanged();
    void getUpdFinished(QStringList);
    void upReleaseAry(int *,int);
public slots:
    Q_INVOKABLE void checkUpdates(bool force = true);

private slots:
    void onFinished(PackageKit::Transaction::Exit status, uint runtime);
    void getUpdates();
    void getPackages();
    void onPackage(PackageKit::Transaction::Info info, const QString &packageID, const QString &summary);
    void onGetPackages(PackageKit::Transaction::Info info, const QString &packageID, const QString &summary);
    void getUpRelease();
private:
    void onChanged();
    void onUpdatesChanged();
    void onStatusChanged();
    QPointer<PackageKit::Transaction> m_updatesTrans;
    QPointer<PackageKit::Transaction> m_cacheTrans;
    QPointer<PackageKit::Transaction> m_packagesTrans;
//    QPointer<PackageKit::Transaction> m_installTrans;
//    QPointer<PackageKit::Transaction> m_detailTrans;
    QVariantMap m_updateList;
    QVariantMap m_packagesList;
    QStringList m_upNameList;
    int releseAry[MAXUPNUM];

};

#endif // PKUPDATES_H
