#include "stdafx.h"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <set>


typedef websocketpp::server<websocketpp::config::asio> server;

typedef server::message_ptr message;

typedef websocketpp::connection_hdl connectionHandle;

typedef std::set<connectionHandle, std::owner_less<connectionHandle>> connectionList;



class BroadcastServer {

private:
  server wss;
  connectionList connections;
  std::ofstream log;

public:
  BroadcastServer();
  void onOpen(connectionHandle hdl);
  void onClose(connectionHandle hdl);
  void onMessage(connectionHandle hdl, message msg);
  void send(std::string msg);
  void run(uint16_t port);

};
