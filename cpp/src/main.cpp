#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <ctime>
#include <system_error>

#include "Devices/Robot.h"

using namespace std;
using namespace ev3dev;

void exit_handler(int s);

Robot robot;
int file_log;

int main(int argc, char* argv[]){

  // Redirection dans un fichier de log
  close(STDERR_FILENO);
  file_log = open( "log.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
  dup2( file_log, STDERR_FILENO);

  // Gestion des interruptions
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = exit_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);

  // Calibration et scan
  if(argc > 1){
    if(strcmp(argv[1], "-c") == 0){
      robot.getColorSensor().calibration();
      robot.getColorSensor().save_calibration("calibration.calib");
      exit(0);
    }
    if(strcmp(argv[1], "-s") == 0){
      robot.getColorSensor().open_calibration("calibration.calib");
      robot.scan_color();
      exit(0);
    }
  }

  robot.getColorSensor().open_calibration("calibration.calib");

  // Suivi de ligne
  robot.line_follow();
  
  robot.getEngine().stop();
  close(file_log);
  close(STDERR_FILENO);
  
  return 0;
}

void exit_handler(int s){
  printf("Caught signal %d\n",s);
  robot.getEngine().stop();
  close(STDERR_FILENO);
  close(file_log);
  exit(1);
}
