#include <QDebug>
#include "pkupdates.h"

PkUpdates::PkUpdates(QObject *parent) :
    QObject(parent),
    m_updatesTrans(Q_NULLPTR),
    m_cacheTrans(Q_NULLPTR)
  //    m_installTrans(Q_NULLPTR),
  //    m_detailTrans(Q_NULLPTR)
{
    connect(PackageKit::Daemon::global(), &PackageKit::Daemon::updatesChanged, this, &PkUpdates::onUpdatesChanged);
    //    connect(PackageKit::Daemon::global(), &PackageKit::Daemon::networkStateChanged, this, &PkUpdates::networkStateChanged);
}

void PkUpdates::checkUpdates(bool force)
{
    qDebug() << "Checking updates, forced";
    m_cacheTrans = PackageKit::Daemon::refreshCache(force);

    //    connect(m_cacheTrans.data(), &PackageKit::Transaction::statusChanged, this, &PkUpdates::onStatusChanged);
//    connect(m_cacheTrans.data(), &PackageKit::Transaction::finished, this, &PkUpdates::onFinished);
    //    connect(m_cacheTrans.data(), &PackageKit::Transaction::errorCode, this, &PkUpdates::onErrorCode);
    //    connect(m_cacheTrans.data(), &PackageKit::Transaction::requireRestart, this, &PkUpdates::onRequireRestart);
    //    connect(m_cacheTrans.data(), &PackageKit::Transaction::repoSignatureRequired, this, &PkUpdates::onRepoSignatureRequired);
}

void PkUpdates::getUpdates()
{
    m_updatesTrans = PackageKit::Daemon::getUpdates();
    m_updateList.clear();

    connect(m_updatesTrans.data(), &PackageKit::Transaction::finished, this, &PkUpdates::onFinished);
    //    connect(m_updatesTrans.data(), &PackageKit::Transaction::errorCode, this, &PkUpdates::onErrorCode);
    connect(m_updatesTrans.data(), &PackageKit::Transaction::package, this, &PkUpdates::onPackage);
    //    connect(m_updatesTrans.data(), &PackageKit::Transaction::requireRestart, this, &PkUpdates::onRequireRestart);
    //    connect(m_updatesTrans.data(), &PackageKit::Transaction::repoSignatureRequired, this, &PkUpdates::onRepoSignatureRequired);
}


void PkUpdates::onFinished(PackageKit::Transaction::Exit status, uint runtime)
{
    qDebug() << __FUNCTION__ ;
    PackageKit::Transaction * trans = qobject_cast<PackageKit::Transaction *>(sender());
    if (!trans)
        return;

    trans->deleteLater();

    //    if (trans->role() == PackageKit::Transaction::RoleRefreshCache)
    //    {
    //        if (status == PackageKit::Transaction::ExitSuccess)
    //        {
    //            qDebug() << "Cache transaction finished successfully";
    //            return;
    //        }
    //        else
    //        {
    //            qDebug() << "Cache transaction didn't finish successfully";
    //        }
    //    }
    /*else*/ if (trans->role() == PackageKit::Transaction::RoleGetUpdates)
    {
        if (status == PackageKit::Transaction::ExitSuccess)
        {
            qDebug() << "Check updates transaction finished successfully";
            qDebug() << "Total number of updates: " << count() << endl;
        }
//        else if (trans->role() == PackageKit::Transaction::RoleUpdatePackages)
//        {
//            const QStringList packages = trans->property("packages").toStringList();
//            qDebug() << "Finished updating packages:" << packages;
//            if (status == PackageKit::Transaction::ExitNeedUntrusted)
//            {
//                qDebug() << "Transaction needs untrusted packages";
//                // restart transaction with "untrusted" flag
//                //            installUpdates(packages, false /*simulate*/, true /*untrusted*/);
//                return;
//            }
//            else if (status == PackageKit::Transaction::ExitSuccess && trans->transactionFlags().testFlag(PackageKit::Transaction::TransactionFlagSimulate))
//            {
//                qDebug() << "Simulation finished with success, restarting the transaction";
//                //            installUpdates(packages, false /*simulate*/, false /*untrusted*/);
//                return;
//            }
//            else if (status == PackageKit::Transaction::ExitSuccess)
//            {
//                qDebug() << "Update packages transaction finished successfully";
//            }
//            else
//            {
//                qDebug() << "Update packages transaction didn't finish successfully";
//                // just try to refresh cache in case of error, the user might have installed the updates manually meanwhile
//                //                checkUpdates(false /* force */);
//                return;
//            }
//            return;
//        }

        //        emit updatesChanged();
    }
}

int PkUpdates::count() const
{
    return m_updateList.count();
}

void PkUpdates::onUpdatesChanged()
{
    qDebug() << __FUNCTION__ << ": Updates changed, getting updates!";
    getUpdates();
}

QVariantMap PkUpdates::packages() const
{
    return m_updateList;
}

void PkUpdates::onPackage(PackageKit::Transaction::Info info, const QString &packageID, const QString &summary)
{
    QString packageName = PackageKit::Transaction::packageName(packageID);
    qDebug() << __FUNCTION__ << ": Got update package:" << packageName;

    switch (info) {
    case PackageKit::Transaction::InfoBlocked:
        // Blocked updates are not instalable updates so there is no
        // reason to show/count them
        return;
    default:
        break;
    }
    m_updateList.insert(packageID, summary);
}
