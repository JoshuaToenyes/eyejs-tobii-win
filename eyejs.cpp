/*
* This is an example that demonstrates how to connect to the EyeX Engine and subscribe to the lightly filtered gaze data stream.
*
* Copyright 2013-2014 Tobii Technology AB. All rights reserved.
*/

#include "stdafx.h"
#include <string>
#include "eyex.h"
#include "eyex/EyeX.h"
#include "ws.h"

typedef struct {
	double x, y;
} EYEJS_COORDINATES;

typedef struct {
	bool left, right, both;
} EYEJS_AVAILABILITY;

typedef struct {
	std::string 				type;
	double 							timestamp;
	EYEJS_COORDINATES 	avg, left, right;
	EYEJS_AVAILABILITY 	available;
} EYEJS_GAZEMSG;

void GazeDataEventHandler(TX_GAZEPOINTDATAEVENTPARAMS eventParams) {
	printf("MY Gaze Data: (%.1f, %.1f) timestamp %.0f ms\n", eventParams.X, eventParams.Y, eventParams.Timestamp);
}

int _tmain(int argc, char* argv[]) {

	eyex_connect();

	create_echo_server();

	return 0;
}
