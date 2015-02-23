#include "stdafx.h"
#include "ws.h"

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

BroadcastServer::BroadcastServer() {
  wss.init_asio();

  wss.set_open_handler(bind(&BroadcastServer::onOpen, this, ::_1));
  wss.set_close_handler(bind(&BroadcastServer::onClose, this, ::_1));
  wss.set_message_handler(bind(&BroadcastServer::onMessage, this, ::_1, ::_2));
}

void BroadcastServer::onOpen(connectionHandle handle) {
  connections.insert(handle);
}

void BroadcastServer::onClose(connectionHandle handle) {
  connections.erase(handle);
}

void BroadcastServer::onMessage(connectionHandle hdl, message msg) {
  for (auto connection : connections) {
    wss.send(connection, msg);
  }
}

void BroadcastServer::send(std::string msg) {
  for (auto connection : connections) {
    wss.send(connection, msg, websocketpp::frame::opcode::text);
  }
}

void BroadcastServer::run(uint16_t port) {
  wss.listen(port);
  wss.start_accept();
  wss.run();
}
