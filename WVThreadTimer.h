#pragma once

#include <QObject>
#include <QTimer>
#include <QThread>

//Only for use in multi thread

class WVThreadTimer : public QObject
{
    Q_OBJECT

public:
    WVThreadTimer(QObject *parent = nullptr);
    ~WVThreadTimer();

    void SetSingleShot(bool is_Single);
    void Start(int msec);
    bool IsActive();
    void Stop();

private:
    QTimer* timer_;
    QThread thread_;

signals:
    void StartTimer(int);
    void StopTimer();
    void Timeout();
};
