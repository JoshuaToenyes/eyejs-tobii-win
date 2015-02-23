void GazeDataEventHandler(TX_GAZEPOINTDATAEVENTPARAMS eventParams);

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
