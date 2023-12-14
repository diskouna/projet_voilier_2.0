#include "MyTimer.h"
#include "MyGPIO.h"
#include "MYADC.h"
#include "GIROUETTE.h"
#include "MyServo.h"
#include "BORDAGE_AUTOMMATIQUE.h"

float bordage(float angle_alpha) {
	float angle_deg;

	if (angle_alpha>=45 && angle_alpha<=180 ) {
		angle_deg = ((angle_alpha-45)*90)/135;}
	else{
		angle_deg = 0;}
	MyServo_Rotate(angle_deg);
		
		return angle_deg;
}
