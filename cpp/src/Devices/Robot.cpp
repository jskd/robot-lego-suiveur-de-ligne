#include "Robot.h"

#define SPEED 70
#define SEARCH_SPEED 70
#define CORRECT_SPEED 60

#define SEARCH_TIME 0.2
#define CORRECT_TIME 0.15

#define DELAY_CORRECTION 0.1
#define NB_LAPS 2

Robot::Robot()
{
	sleep(2);
	_engine = new Engine();
	_sn_color = new ColorSensor();
}

Robot::~Robot()
{
	delete _engine;
	delete _sn_color;
}

Engine& Robot::getEngine()
{
	return *_engine;
}

ColorSensor& Robot::getColorSensor()
{
	return *_sn_color;
}

void Robot::scan_color(){
	std::string rep = "";

	while(true){
		std::cout << " -> [Enter]Scan [q]Quit : ";
		rep = std::cin.get();

		if(rep.compare("q") == 0){
			break;
		}
		int color_ref = _sn_color->getColor();
		std::string color_name = _sn_color->getColorName(color_ref);

		std::cout << " Color #" << color_ref << " (" << color_name << ")" << std::endl;
	}
}

bool Robot::search_line(Direction dir, int bg_color, double seconds){
	clock_t begin_time = 0;
	double elapsed_time = 0;
	
	if(dir == Direction::RIGHT){
		_engine->setDirection(Direction::RIGHT);
	}
	else if(dir == Direction::LEFT){
		_engine->setDirection(Direction::LEFT);
	}
	else{
		return false;
	}
	
	_engine->run();
	begin_time = clock();
	while(elapsed_time < seconds) {
		if(_sn_color->getColor() != bg_color){
			_engine->stop();
			return true;
		}
		elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
		//sleep(0.05);
	}

	return false;
}

Direction Robot::getOpposedDir(Direction dir){
	if(dir == Direction::LEFT){
		return Direction::RIGHT;
	}
	else{
		return Direction::LEFT;
	}
}


void Robot::line_follow(){

	// INITIALISATION
	clock_t begin_time_found = 1;
	double elapsed_time_found = 0;
	clock_t laps_time = 0;
	bool on_line = false;
	int background = _sn_color->getColor();
	int begin_color = -1;
	int nb_tours = 0;
	Direction linePosition = Direction::LEFT;

	while(true){

		try{
			int current_color = _sn_color->getColor();
			// Si on est sur la ligne
			if(current_color != background){

				// Enregistrement de la couleur de départ
				if(begin_color == -1){
					begin_color = current_color;
					laps_time = clock();
					std::cout << "BEGIN COLOR # " << begin_color << " (" << _sn_color->getColorName(begin_color) << ")" << std::endl;
				}

				if(current_color == begin_color){
					double time_since_laps = double(clock() - laps_time) / CLOCKS_PER_SEC;

					if(time_since_laps >= 10){
						laps_time = clock();
						std::cout << "###### LAPS ######" << std::endl;
						nb_tours++;
					}
				}

				// Si on est au dernier tour
				if(nb_tours == NB_LAPS){
					_engine->stop();
					break;
				}

				_engine->run();
				_engine->setSpeed(SPEED);
				_engine->setDirection(Direction::FORWARD);
			}
			else{
				elapsed_time_found = double(clock() - begin_time_found) / CLOCKS_PER_SEC; 

				/* Correction de trajectoire */
				_engine->setSpeed(CORRECT_SPEED);

				if(elapsed_time_found >= DELAY_CORRECTION){
					on_line = search_line(linePosition, background, CORRECT_TIME);
				}
				else{
					on_line = search_line(getOpposedDir(linePosition), background, CORRECT_TIME);
					linePosition = getOpposedDir(linePosition);
				}

				/* Si la correction échoue on va dans la direction opposée */
				_engine->setSpeed(SEARCH_SPEED);

				if(!on_line){
					on_line = search_line(getOpposedDir(linePosition), background, SEARCH_TIME);
					linePosition = getOpposedDir(linePosition);

					if(on_line){ begin_time_found = clock(); }

				}
				else{
					begin_time_found = clock();
				}
			}

		}catch ( ... ) { std::cout << "Erreur inconnue.\n"; }
		//sleep(0.05);
	}
}

