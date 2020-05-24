#include "Acceptor.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"
#include "SocketsOps.h"

#include <stdio.h>

using namespace muduo;
using namespace muduo::net;

void newConnection(int sockfd, const InetAddress& peerAddr)
{
  printf("newConnection(): accepted a new connection from %s\n",
         peerAddr.toIpPort().c_str());
  ::write(sockfd, "How are you?\n", 13);
  sockets::close(sockfd);
}

int main()
{
  printf("main(): pid = %d\n", getpid());

  InetAddress listenAddr(12345);
  EventLoop loop;
  bool cc = 1;
  Acceptor acceptor(&loop, listenAddr, cc);
  acceptor.setNewConnectionCallback(newConnection);
  acceptor.listen();

  loop.loop();
}

