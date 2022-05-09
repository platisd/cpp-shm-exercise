#include <array>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <string>

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
    ~ChannelRemover()
    {
        boost::interprocess::message_queue::remove(writerToReader.c_str());
    }
};

int main()
{
    ChannelRemover remover{};
    boost::interprocess::message_queue messageQueue{
        boost::interprocess::open_or_create,
        writerToReader.c_str(),
        messageQueueLength,
        maxMessageSize};

    Message message{};
    std::size_t receivedSize{};
    unsigned int priority{};
    while (messageQueue.try_receive(
        &message, maxMessageSize, receivedSize, priority))
    {
        std::string payload{message.payload.data(), message.length};
        std::cout << payload << std::endl;
    }

    return 0;
}
