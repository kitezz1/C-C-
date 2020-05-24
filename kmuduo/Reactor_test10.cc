#include "muduo/net/TcpServer.h"

#include "muduo/base/AsyncLogging.h"
#include "muduo/base/Logging.h"
#include "muduo/base/Thread.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"

#include <functional>
#include <utility>

#include <stdio.h>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

class TestServer
{
 public:
  TestServer(EventLoop* loop,
             const InetAddress& listenAddr, int numThreads)
    : loop_(loop),
      server_(loop, listenAddr, "TestServer"),
      numThreads_(numThreads)
  {
    server_.setConnectionCallback(std::bind(&TestServer::onConnection, this, _1));
    server_.setMessageCallback(std::bind(&TestServer::onMessage, this, _1, _2, _3));
    server_.setThreadNum(numThreads);
  }

  void start()
  {
	  server_.start();
  }

 private:
  void onConnection(const TcpConnectionPtr& conn)
  {
    if (conn->connected())
    {
      printf("onConnection(): new connection [%s] from %s\n",
             conn->name().c_str(),
             conn->peerAddress().toIpPort().c_str());
    }
    else
    {
      printf("onConnection(): connection [%s] is down\n",
             conn->name().c_str());
    }
  }

  void onMessage(const TcpConnectionPtr& conn,
                   Buffer* buf,
                   Timestamp time)
  {
    printf("onMessage(): received %zd bytes [%s] from connection [%s]\n",
           buf->internalCapacity(), (buf->retrieveAllAsString()).c_str(), conn->name().c_str());
  }

  EventLoop* loop_;
  TcpServer server_;
  int numThreads_;
};


int main()
{
  printf("main(): pid = %d\n", getpid());

  InetAddress listenAddr(12345);
  EventLoop loop;

  TestServer server(&loop, listenAddr,4);
  server.start();

  loop.loop();
}
