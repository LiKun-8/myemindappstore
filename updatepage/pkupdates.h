#ifndef PKUPDATES_H
#define PKUPDATES_H

#include <QObject>
#include <QPointer>
#include <packagekitqt5/PackageKit/Transaction>
#include <packagekitqt5/PackageKit/Daemon>

class PkUpdates : public QObject
{
    Q_OBJECT
public:
    explicit PkUpdates(QObject *parent = nullptr);
    int count() const;
    QVariantMap packages() const;
signals:
    void updatesChanged();

public slots:
    Q_INVOKABLE void checkUpdates(bool force = true);

private slots:
    void onFinished(PackageKit::Transaction::Exit status, uint runtime);
    void getUpdates();
    void onPackage(PackageKit::Transaction::Info info, const QString &packageID, const QString &summary);

private:
    void onChanged();
    void onUpdatesChanged();
    void onStatusChanged();
    QPointer<PackageKit::Transaction> m_updatesTrans;
    QPointer<PackageKit::Transaction> m_cacheTrans;
//    QPointer<PackageKit::Transaction> m_installTrans;
//    QPointer<PackageKit::Transaction> m_detailTrans;
    QVariantMap m_updateList;


};

#endif // PKUPDATES_H
