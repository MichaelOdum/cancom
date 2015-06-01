/*
 * 	cancom.h
 *
 *  Created on: 		Nov 2013
 *  Authors: 			Dan Pierce
 */

#ifndef CANCOM_H_
#define CANCOM_H_

#include <libpcan.h>
#include <fcntl.h>
#include <string>
 #include "ros/ros.h"
#include <std_msgs/String.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Quaternion.h>
 #include <sensor_msgs/PointCloud.h>
 #include <can_msgs/RadarData.h>
 #include <geometry_msgs/PointStamped.h>
 #include <can_msgs/TruckData.h>
 #include <boost/thread.hpp>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

class Cancom {

public:
	Cancom();
	~Cancom();

	bool init(int sensor_type, std::string port_);
	can_msgs::RadarData radarCanMsgCallback();
	sensor_msgs::PointCloud radarPointCloudCallback();
	can_msgs::TruckData truckCanMsgCallback();

	virtual bool StartReading();

private:
	HANDLE CanHandle;

	can_msgs::RadarData currentTracks;

	can_msgs::TruckData currentTruckMsg;


    tf::TransformBroadcaster tf_broadcaster; 

	sensor_msgs::PointCloud Tracks;
	int groupscanindex;
	int prevgroupscanindex;
	//sensor_msgs::PointCloud radarxyz;

	bool bReading; 

	boost::shared_ptr<boost::thread> mReadThread; //!< Boost thread for listening for data from Prowler  
	boost::mutex readingMutex;  //!< mutex for bReading variable  
	boost::condition_variable readingCond; //!< condition for bReading variable  
	bool bStartReading; //!< signals read thread to stop

	void ReadThread(); 
	void ReadSensorData();

	bool initRadar();
	bool is_init;
	void parse_can(TPCANRdMsg read_msg_full);

};


#endif /* CANCOM_H_ */
