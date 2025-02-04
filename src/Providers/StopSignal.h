#ifndef STOPSIGNAL_H
#define STOPSIGNAL_H
#include <atomic>

class StopSignal {
public:
    StopSignal() : stopped(false) {
    }

    StopSignal(const StopSignal &other)
        : stopped(other.stopped.load()) {
    }

    void signal_stop() {
        stopped.store(true, std::memory_order_relaxed);
    }

    bool is_stopped() const {
        return stopped.load(std::memory_order_relaxed);
    }

private:
    std::atomic<bool> stopped;
};

#endif
