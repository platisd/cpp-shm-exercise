#include <array>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <string>
#include <thread>

struct Message
{
    static constexpr std::size_t maxSize{100};
    std::size_t length{0};
    std::array<char, maxSize> payload{};
};

const std::string writerToReader{"writerToReader"};
const std::size_t messageQueueLength{200};
const std::size_t maxMessageSize{sizeof(Message)};

struct ChannelRemover
{
    ChannelRemover()
    {
        boost::interprocess::message_queue::remove(writerToReader.c_str());
    }

    ~ChannelRemover()
    {
        boost::interprocess::message_queue::remove(writerToReader.c_str());
    }
};

int main()
{
    ChannelRemover remover{};
    boost::interprocess::message_queue messageQueue{
        boost::interprocess::create_only,
        writerToReader.c_str(),
        messageQueueLength,
        maxMessageSize};

    for (unsigned int i = 0; i < messageQueueLength; i++)
    {
        Message m{};
        const auto priority = i % 3;
        std::string payload{"Message no." + std::to_string(i)
                            + " priority: " + std::to_string(priority)};
        std::copy(payload.begin(), payload.end(), m.payload.begin());
        m.length = payload.length();

        messageQueue.send(&m, maxMessageSize, priority);
        std::cout << m.payload.data() << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds{30});

    return 0;
}
