#include <QDebug>
#include "pkupdates.h"

PkUpdates::PkUpdates(QObject *parent) :
    QObject(parent),
    m_updatesTrans(Q_NULLPTR),
    m_cacheTrans(Q_NULLPTR),
    m_packagesTrans(Q_NULLPTR)
{    
    shareData = new ShareData();
    jsonFunc = new JSONFUNC(shareData);

    connect(PackageKit::Daemon::global(), &PackageKit::Daemon::updatesChanged, this, &PkUpdates::onUpdatesChanged,Qt::QueuedConnection);
    //    connect(PackageKit::Daemon::global(), &PackageKit::Daemon::networkStateChanged, this, &PkUpdates::networkStateChanged);
}

void PkUpdates::checkUpdates(bool force)
{
    qDebug() << "Checking updates, forced";
    m_cacheTrans = PackageKit::Daemon::refreshCache(force);

    connect(m_cacheTrans.data(), &PackageKit::Transaction::finished, this, &PkUpdates::onFinished);
}

void PkUpdates::getUpdates()
{
    m_updatesTrans = PackageKit::Daemon::getUpdates();
    m_updateList.clear();
    m_upNameList.clear();

    connect(m_updatesTrans.data(), &PackageKit::Transaction::finished, this, &PkUpdates::onFinished);
    //    connect(m_updatesTrans.data(), &PackageKit::Transaction::errorCode, this, &PkUpdates::onErrorCode);
    connect(m_updatesTrans.data(), &PackageKit::Transaction::package, this, &PkUpdates::onPackage);
    //    connect(m_updatesTrans.data(), &PackageKit::Transaction::requireRestart, this, &PkUpdates::onRequireRestart);
    //    connect(m_updatesTrans.data(), &PackageKit::Transaction::repoSignatureRequired, this, &PkUpdates::onRepoSignatureRequired);
}

void PkUpdates::getPackages()
{
    m_packagesTrans = PackageKit::Daemon::getPackages(PackageKit::Transaction::FilterInstalled);
    m_packagesList.clear();

    connect(m_packagesTrans.data(), &PackageKit::Transaction::finished, this, &PkUpdates::onFinished);
    //    connect(m_updatesTrans.data(), &PackageKit::Transaction::errorCode, this, &PkUpdates::onErrorCode);
    connect(m_packagesTrans.data(), &PackageKit::Transaction::package, this, &PkUpdates::onGetPackages);
    //    connect(m_updatesTrans.data(), &PackageKit::Transaction::requireRestart, this, &PkUpdates::onRequireRestart);
    //    connect(m_updatesTrans.data(), &PackageKit::Transaction::repoSignatureRequired, this, &PkUpdates::onRepoSignatureRequired);
}

int PkUpdates::count() const
{
    return m_updateList.count();
}

int PkUpdates::insCount() const
{
    return m_packagesList.count();
}

void PkUpdates::onUpdatesChanged()
{
    qDebug() << __FUNCTION__ << ": Updates changed, getting updates!";

    getUpdates();
    jsonFunc->setAppname();

//    getPackages();
}

QVariantMap PkUpdates::packages() const
{
    return m_updateList;
}

QStringList PkUpdates::getPacName() const
{
    return m_upNameList;
}


void PkUpdates::onPackage(PackageKit::Transaction::Info info, const QString &packageID, const QString &summary)
{
    QString packageName = PackageKit::Transaction::packageName(packageID);
//    qDebug() << __FUNCTION__ << ": Got update package:" << packageName;

    switch (info) {
    case PackageKit::Transaction::InfoBlocked:
        return;
    default:
        break;
    }
    m_updateList.insert(packageID, summary);
    m_upNameList.append(packageName);
}

void PkUpdates::onGetPackages(PackageKit::Transaction::Info info, const QString &packageID, const QString &summary)
{
    switch (info) {
    case PackageKit::Transaction::InfoInstalled:
    {
        QString packageName = PackageKit::Transaction::packageName(packageID);
//        qDebug() << __FUNCTION__ << ": Got packages:" << packageID;
        m_packagesList.insert(packageID, summary);

    }
        break;
    default:
        break;
    }
}



void PkUpdates::onFinished(PackageKit::Transaction::Exit status, uint runtime)
{
    qDebug() << __FUNCTION__ ;
    PackageKit::Transaction * trans = qobject_cast<PackageKit::Transaction *>(sender());
    if (!trans)
        return;

    trans->deleteLater();

    if (trans->role() == PackageKit::Transaction::RoleRefreshCache)
    {
        if (status == PackageKit::Transaction::ExitSuccess)
        {
            qDebug() << "Cache transaction finished successfully";
            return;
        }
        else
        {
            qDebug() << "Cache transaction didn't finish successfully";
        }
    }
    else if (trans->role() == PackageKit::Transaction::RoleGetUpdates)
    {
        if (status == PackageKit::Transaction::ExitSuccess)
        {
            connect(jsonFunc,SIGNAL(productIsOk()),this,SLOT(getUpRelease()));

//            emit getUpdFinished(m_upNameList);
//            m_upNameList.clear();
            qDebug() << "Check updates transaction finished successfully";
            qDebug() << "Total number of updates: " << count() << endl;
        }
        else
        {
            qDebug() << "Check updates transaction didn't finish successfully";
        }
    }
    else if(trans->role() == PackageKit::Transaction::RoleGetPackages)
    {
        if (status == PackageKit::Transaction::ExitSuccess)
        {
            qDebug() << "Get Packages Installed transaction finished successfully";
            qDebug() << "Total number of Packages Installed: " << insCount() << endl;
        }
        else
        {
            qDebug() << "Get Packages Installed transaction didn't finish successfully";
        }
    }
}

void PkUpdates::getUpRelease()
{

    int releaseAry[m_upNameList.count()];
    int num = 0;
    qDebug()<< shareData->classStrMap.count();
    QMap<int,CLASSSTRUCT>::iterator item = shareData->classStrMap.begin();
    for(; item != shareData->classStrMap.end(); ++item)
    {
        qDebug()<<item.value().proName;
    }
    for(int i = 0; i < m_upNameList.count(); i++)
        for(; item != shareData->classStrMap.end(); ++item)
        {
            qDebug()<<item.value().proName;
            if(m_upNameList.at(i) == item.value().proName)
            {
                qDebug() << "m_upNameList.at(i) : " << m_upNameList.at(i);
                releaseAry[num] = item.value().releaseId;
                num++;
            }
        }
    if(num != 0)
    {
        jsonFunc->getUpdateRelease(releaseAry,num);
    }
}


