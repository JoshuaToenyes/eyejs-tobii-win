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

BroadcastServer wss;

void GazeDataEventHandler(TX_GAZEPOINTDATAEVENTPARAMS eventParams) {
	EYEJS_GAZEMSG msg;
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

	char t[100];

	sprintf(t, "MY Gaze Data: (%.1f, %.1f) timestamp %.0f ms\n", eventParams.X, eventParams.Y, eventParams.Timestamp);

	wss.send(t);

	printf("MY Gaze Data: (%.1f, %.1f) timestamp %.0f ms\n", eventParams.X, eventParams.Y, eventParams.Timestamp);
}


void eyeXWorker() {
	eyex_connect();
}


void wsWorker() {
	wss.run(9002);
}


int _tmain(int argc, char* argv[]) {

	boost::thread eyeXThread(eyeXWorker);

	boost::thread wsThread(wsWorker);

	// wait for everything to be done... so forever.
	eyeXThread.join();
	wsThread.join();

	return 0;
}
