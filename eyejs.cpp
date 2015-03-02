/*
* This is an example that demonstrates how to connect to the EyeX Engine and subscribe to the lightly filtered gaze data stream.
*
* Copyright 2013-2014 Tobii Technology AB. All rights reserved.
*/

#include "stdafx.h"

#include "eyex.h"
#include "eyex/EyeX.h"

#include <iostream>

#include "ws.h"

#include "eyejs.h"

#include <boost/thread.hpp>

const int PORT = 5619;

const char * EYEJS_GAZE_MSG_FMT =
  "{"
		"\"type\": \"gaze\","
		"\"avg\": {x: %.1f, y: %.1f},"
		"\"left\": {x: %.1f, y: %.1f},"
		"\"right\": {x: %.1f, y: %.1f},"
		"\"available\": {\"left\": %s, \"right\": %s, \"both\": %s},"
	"}";

BroadcastServer wss;

void GazeMsgToJSON(EYEJS_GAZE_MSG msg, char* s) {
	sprintf(s, EYEJS_GAZE_MSG_FMT,
		msg.avg.x,
		msg.avg.y,
		msg.left.x,
		msg.left.y,
		msg.right.x,
		msg.right.y,
		msg.available.left  ? "true" : "false",
		msg.available.right ? "true" : "false",
		msg.available.both  ? "true" : "false");
}


void GazeDataEventHandler(TX_GAZEPOINTDATAEVENTPARAMS eventParams) {
	EYEJS_GAZE_MSG msg;
	msg.timestamp = eventParams.Timestamp;

	msg.avg.x 	= eventParams.X;
	msg.avg.y 	= eventParams.Y;
	msg.left.x 	= 0;
	msg.left.y 	= 0;
	msg.right.x = 0;
	msg.right.y = 0;

	msg.available.left 	= true;
	msg.available.right = true;
	msg.available.both 	= true;

	char t[1000];

	GazeMsgToJSON(msg, t);

	wss.send(t);
}


void eyeXWorker() {
	eyex_connect();
}


void wsWorker() {
	wss.run(PORT);
}


int _tmain(int argc, char* argv[]) {

	boost::thread eyeXThread(eyeXWorker);

	boost::thread wsThread(wsWorker);

	// wait for everything to be done... so forever.
	eyeXThread.join();
	wsThread.join();

	return 0;
}
