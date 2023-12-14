#include "MyTimer.h"
#include "MyGPIO.h"
#include "MYADC.h"
#include "GIROUETTE.h"
#include "MyServo.h"
#include "BORDAGE_AUTOMMATIQUE.h"

float bordage(float angle_alpha) {
	float angle_deg;
// Si l'angle du vent arrive entre -45 et +45 par rapport à l'axe du bateau, 
	if (angle_alpha>=45 && angle_alpha<=180 ) {
		angle_deg = ((angle_alpha-45)*90)/135;} // On implémente une fonction linéaire qui va de 0 à 90 selon le vent
	else{
		angle_deg = 0;} // Sinon, on se remet dans l'axe
	MyServo_Rotate(angle_deg); // Le servomoteur recupère l'angle affecté et s'assure que le voilier se place correctement
		
		return angle_deg;
}
