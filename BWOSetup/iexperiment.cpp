#include "IExperiment.h"

#include <QThread>                      // for pauses
#include <QtConcurrent/QtConcurrent>    // makes it possible to write multi-threaded programs

IExperiment::IExperiment()
    : mExpSettings(nullptr)
{
}

IExperiment::IExperiment(QObject *expSettings)
    : mExpSettings(expSettings)
{
}

IExperiment::~IExperiment()
{
    if(mExperimentIsRunning)
        stop();
}

void IExperiment::start()
{
    if (mExpSettings != nullptr)
        mExpThreadRes = QtConcurrent::run(this, &IExperiment::toDo, mExpSettings);
    // To DO: Implement no argument exception
    // one way to do it is to get rid of the constructor without parameters
    else throw;
}

void IExperiment::stop()
{
    while (mExpThreadRes.isRunning()) {
        mExpThreadRes.cancel();
        mExpThreadRes.waitForFinished();
    }
    mExperimentIsRunning = false;
}
