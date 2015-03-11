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
		"\"avg\": {\"x\": %.1f, \"y\": %.1f},"
		"\"left\": {\"x\": %.1f, \"y\": %.1f},"
		"\"right\": {\"x\": %.1f, \"y\": %.1f},"
		"\"available\": {\"left\": %s, \"right\": %s, \"both\": %s}"
	"}";

BroadcastServer wss;

EYEJS_GAZE_MSG msg;

void EyeJSMsgToJSON(EYEJS_GAZE_MSG msg, char* s) {
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
	msg.timestamp = eventParams.Timestamp;

	msg.avg.x 	= eventParams.X;
	msg.avg.y 	= eventParams.Y;

	char t[1000];

	EyeJSMsgToJSON(msg, t);

	wss.send(t);
}


void PositionDataEventHandler(TX_EYEPOSITIONDATAEVENTPARAMS eventParams) {
  msg.available.right = !(eventParams.RightEyeXNormalized == 0.0 && eventParams.RightEyeYNormalized == 0.0 && eventParams.RightEyeZNormalized == 0.0);
  msg.available.left = !(eventParams.LeftEyeXNormalized == 0.0 && eventParams.LeftEyeYNormalized == 0.0 && eventParams.LeftEyeZNormalized == 0.0);
  msg.available.both = msg.available.right && msg.available.left;
}


void eyeXWorker() {
	eyex_connect();
}


void wsWorker() {
	wss.run(PORT);
}


int _tmain(int argc, char* argv[]) {

  msg.avg.x 	= 0;
  msg.avg.y 	= 0;
  msg.left.x 	= 0;
  msg.left.y 	= 0;
  msg.right.x = 0;
  msg.right.y = 0;
  msg.available.left 	= true;
  msg.available.right = true;
  msg.available.both 	= true;

	boost::thread eyeXThread(eyeXWorker);

	boost::thread wsThread(wsWorker);

	// wait for everything to be done... so forever.
	eyeXThread.join();
	wsThread.join();

	return 0;
}
