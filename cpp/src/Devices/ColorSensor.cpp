#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <math.h>
#include "ColorSensor.h"

using namespace ev3dev;

#define READ_SAMPLES 5
#define CALIB_SAMPLES 50

ColorSensor::ColorSensor()
{
	_sensor = new color_sensor(INPUT_1);
	_sensor->set_mode("RGB-RAW");

}

ColorSensor::~ColorSensor()
{
	delete _sensor;

	for(uint i=0; i<_dico_colors.size(); i++){
		delete _dico_colors[i];
	}
}

void ColorSensor::calibration()
{
	std::string rep = "";
	int samples = CALIB_SAMPLES;
	ColorRGB min; // 1020 = valeur maxi du capteur
	ColorRGB max;
	ColorEntry* entry;

	std::cout << " # Calibration ..." << std::endl;
	std::cout << " ------------------------------" << std::endl;

	while(true){
		std::cout << "Press ENTER to add new color. [q]Quit : ";
		std::getline(std::cin, rep);

		if(rep.compare("q") == 0){
			break;
		}

		std::cout << " - Name of reference : ";
		std::getline(std::cin, rep);

		if(rep.compare("") == 0){
			rep = "UNKNOW";
		}

		sampling(samples, min, max);

		entry = new ColorEntry();
		entry->setName(rep); 
		entry->setMin(min);
		entry->setMax(max);

		_dico_colors.push_back(entry);
		std::cout << " -> Color reference n°" << _dico_colors.size()-1 << " (" << rep << ") added." << std::endl;
	}

	std::cout << " ------------------------------" << std::endl;
	std::cout << " # Calibration done !" << std::endl;
	std::cout << " ------------------------------" << std::endl;
	
}

void ColorSensor::sampling(int samples, ColorRGB& average)
{
	int cur_r, cur_g, cur_b = 0;

	for(int i=0; i<samples; i++){
		cur_r = _sensor->red();
		cur_g = _sensor->green();
		cur_b = _sensor->blue();

		average.set_red(average.red() + cur_r);
		average.set_green(average.green() + cur_g);
		average.set_blue(average.blue() + cur_b);
	}

	// Moyenne 
	average.set_red(average.red() / samples);
	average.set_green(average.green() / samples);
	average.set_blue(average.blue() / samples);
}

void ColorSensor::sampling(int samples, ColorRGB& min, ColorRGB& max)
{
	min.set_red(1020);
	min.set_green(1020);
	min.set_blue(1020);

	max.set_red(0);
	max.set_green(0);
	max.set_blue(0);

	int cur_r, cur_g, cur_b = 0;

	for(int i=0; i<samples; i++){
		cur_r = _sensor->red();
		cur_g = _sensor->green();
		cur_b = _sensor->blue();

		if(cur_r < min.red())
			min.set_red(cur_r);
		if(cur_r > max.red())
			max.set_red(cur_r);

		if(cur_g < min.green())
			min.set_green(cur_g);
		if(cur_g > max.green())
			max.set_green(cur_g);

		if(cur_b < min.blue())
			min.set_blue(cur_b);
		if(cur_b > max.blue())
			max.set_blue(cur_b);

		sleep(0.1);
	}

}

void ColorSensor::save_calibration(std::string file)
{
	ColorRGB min;
	ColorRGB max;
	std::string name;

	std::ofstream out_file;
	out_file.open(file);

	for(uint i=0; i<_dico_colors.size(); i++){
		min = _dico_colors[i]->getMin();
		max = _dico_colors[i]->getMax();
		name = _dico_colors[i]->getName();

		out_file << name << " " << min << max << "\n";

	}

	out_file.close();
}

void ColorSensor::open_calibration(std::string file)
{

	ColorEntry* entry;
	std::string line;
	std::ifstream in_file(file);

	int no_line = 0;

  if (in_file.is_open()){
    while ( getline (in_file,line) )
    {
    	std::vector<std::string> values;
    	std::istringstream iss(line);

			do
			{
				std::string sub;
				iss >> sub;
				values.push_back(sub);
			} while (iss);

			std::string name = values[0];
    	ColorRGB min(std::stoi(values[1]), std::stoi(values[2]), std::stoi(values[3]));
			ColorRGB max(std::stoi(values[4]), std::stoi(values[5]), std::stoi(values[6]));


			entry = new ColorEntry();
			entry->setMin(min);
			entry->setMax(max);
			entry->setName(name);
			_dico_colors.push_back(entry);

			no_line++;
    }

    in_file.close();
  }
  else std::cout << "Unable to open file" << std::endl; 
}

int ColorSensor::getColor()
{
	ColorRGB current;
	int indice = -1;
	int distance = 1020;

	sampling(READ_SAMPLES, current);

	for(uint i=0; i<_dico_colors.size(); i++){
		ColorRGB min = _dico_colors[i]->getMin();
		ColorRGB max = _dico_colors[i]->getMax();

		int average_dist = (current.distanceOf(min) + current.distanceOf(max)) / 2;
	
		//if( (current.distanceOf(min) < distance) || (current.distanceOf(max) < distance) ){
		if(average_dist < distance){
			//distance = current.distanceOf(min);
			distance = average_dist;
			indice = i;
		}
	}

	return indice;
}

std::string ColorSensor::getColorName(int ref)
{
	return _dico_colors[ref]->getName();
}


ColorRGB ColorSensor::getColorRGB()
{
	return ColorRGB(_sensor->red(), _sensor->green(), _sensor->blue());
}