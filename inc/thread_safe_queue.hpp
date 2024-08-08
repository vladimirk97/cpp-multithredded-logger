#ifndef THREAD_SAFE_QUEUE_H_
#define THREAD_SAFE_QUEUE_H_

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <queue>

#define DEFAULT_QUEUE_SIZE  10

template<typename T>
class TSQueue {
  private:  
    std::queue<std::shared_ptr<T>> m_queue;
    std::mutex m_lock;
    std::condition_variable m_cv_send;
    std::condition_variable m_cv_recv;
    std::atomic<bool> m_shutting_down;

    const std::size m_queue_size;

  public:
    TSQueue(std::size_t queue_size = DEFAULT_QUEUE_SIZE);
    ~TSQueue();

    void push(T data);

    std::shared_ptr<T> pop(void);

    bool empty(void);

    void shutdown(void);
};

template<typename T>
TSQueue<T>::TSQueue(std::size_t queue_size): m_queue_size(queue_size) {};

template<typename T>
TSQueue<T>::~TSQueue() {};

template<typename T>
void TSQueue<T>::push(T data) {
    std::shared_ptr<T> send_data = std::make_shared<T>(data);
    std::unique_lock<std::mutex> lock(m_lock);
    m_cv_recv.wait(lock, [this] () {return (m_queue.size() < m_queue_size);});

    if(m_shutting_down.load() && m_queue.empty()) {
        return;
    }

    m_queue.push(send_data);

    lock.unlock();
    m_cv_send.notify_one();
}

template<typename T>
std::shared_ptr<T> TSQueue<T>::pop(void) {
    std::unique_lock<std::mutex> lock(m_lock);
    m_cv_send.wait(lock, [this] () {return (!m_queue.empty() || m_shutting_down.load());});
    if(m_shutting_down.load()) {
        return nullptr;
    }

    std::shared_ptr<T> recv_data = m_queue.front();
    m_queue.pop();

    lock.unlock();
    m_cv_recv.notify_one();

    return recv_data;
}

template<typename T>
bool TSQueue<T>::empty(void) {
    std::unique_lock<std::mutex> lock(m_lock);
    return m_queue.empty();
}

template<typename T>
void TSQueue<T>::shutdown(void) {
    m_shutting_down.load(true);
    m_cv_send.notify_all();
    m_cv_recv.notify_all();
}

#endif