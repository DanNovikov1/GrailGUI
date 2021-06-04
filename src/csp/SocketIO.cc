#include "csp/SocketIO.hh"

#include <cstdint>

#include "csp/csp.hh"

// TODO: Look into logging WSAGetLastError and strerror(errno)
// Using the logging object in csp.hh?
int SocketIO::send(socket_t sckt, const char *buf, int size, int flags) {
  uint32_t bytesSent;
  if ((bytesSent = ::send(sckt, (char *)buf, size, 0)) == err_code) {
    std::cout << WSAGetLastError() << std::endl;
    throw Ex1(Errcode::SOCKET_SEND);
  }
  return bytesSent;
}

int SocketIO::recv(socket_t sckt, const char *buf, int size, int flags) {
  uint32_t bytesRecv;
  if ((bytesRecv = ::recv(sckt, (char *)buf, size, 0)) == err_code) {
    std::cout << WSAGetLastError() << std::endl;
    throw Ex1(Errcode::SOCKET_RECV);
  }
  return bytesRecv;
}