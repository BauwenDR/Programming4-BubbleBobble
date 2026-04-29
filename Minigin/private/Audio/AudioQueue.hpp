#ifndef MINIGIN_AUDIOTHREAD_HPP
#define MINIGIN_AUDIOTHREAD_HPP

namespace dae::AudioQueue
{
    void Launch();
    void Shutdown();

    void SendShutdownSignal();
    void RunSoundThread();
}

#endif //MINIGIN_AUDIOTHREAD_HPP
