/**
* Copyright (C) 2014, BMW Car IT GmbH
* Author: Jonas Sticha (Jonas.Sticha@bmw-carit.de)
*
* This software is licensed under BSD 3-clause License
* (see http://spdx.org/licenses/BSD-3-Clause).
**/

#include "ros/ros.h"
#include <sched.h>
#include <iostream>
#include <pthread.h>

void* doRosSpin(void*)
{
        ros::spin();
}

int main(int argc, char* argv[])
{
	struct sched_param schedParam;
	schedParam.sched_priority = 95;
	if(sched_setscheduler(0, SCHED_RR, &schedParam))
	{
		std::cout << "ERROR: Couldn't switch to realtime priority!" << std::endl;
		return 1;
	}
	ros::init(argc, argv, "stuck_at_shutdown");
	pthread_t thread;
        pthread_create(&thread, NULL, &doRosSpin, NULL);
	sleep(1);
	//If ros::shutdown() is uncommented the program gets stuck there
	//Otherwise it gets stuck at return 0
	//ros::shutdown();
	return 0;
}

