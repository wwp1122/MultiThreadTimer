#include "WVThreadTimer.h"


WVThreadTimer::WVThreadTimer(QObject *parent)
    : QObject(parent)
{
    timer_ = new QTimer;
    timer_->moveToThread(&thread_);

    connect(timer_, &QTimer::timeout, [&]() { emit Timeout(); });
    connect(&thread_, &QThread::finished, timer_, &QObject::deleteLater);

    connect(this, SIGNAL(StartTimer(int)), timer_, SLOT(start(int)), Qt::BlockingQueuedConnection);
    connect(this, &WVThreadTimer::StopTimer, timer_, &QTimer::stop, Qt::BlockingQueuedConnection);

    thread_.start();
}

WVThreadTimer::~WVThreadTimer()
{
    Stop();
    timer_->deleteLater();

    if (thread_.isRunning()) {
        thread_.quit();
        thread_.wait();
    }
}

void WVThreadTimer::SetSingleShot(bool is_single) {
    timer_->setSingleShot(is_single);
}
void WVThreadTimer::Start(int msec) {
    emit StartTimer(msec);
}
void WVThreadTimer::Stop() {
    emit StopTimer();
}
bool WVThreadTimer::IsActive() {
    return timer_->isActive();
}
