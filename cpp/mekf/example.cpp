#include "stdafx.h"
#include "mekf.h"

int main()
{
	mekf my_mekf;
	double rawValues[6];

	//Dummy Raw Values
	for (int i = 0; i < 6; i++)
	{
		rawValues[i] = 0;
	}
	float dt = 0.01;
	double quaternion[4] = { 1, 0, 0, 0 };
	
	int calibrationSamples = 100;
	uint32_t timestamp = 0; // milliseconds*10. For instance, 1400 = 140ms

	int actualSample = 0;
	while (actualSample < calibrationSamples) {

		my_mekf.setRawData(rawValues, timestamp);
		my_mekf.calibrationOnline();
		my_mekf.getQuaternion(quaternion);
		actualSample++;
		
	}		

	my_mekf.setStationary_samples(50);
	my_mekf.setCovarianceMatrices();

	std::cout << "Calibration completed" << endl;
	Eigen::Vector3d gb;
	my_mekf.getGyroscopeBias(&gb);
	std::cout << "Gyroscope Byas = " << std::fixed << std::setprecision(5) << gb << std::endl;
	
	
	while (1) {
		timestamp += dt;
		my_mekf.setRawData(rawValues, timestamp);
		my_mekf.mekfOnline();
		my_mekf.getQuaternion(quaternion);

	}

    return 0;

}

