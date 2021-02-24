#include <string>
#include "configt.h" 
#include "splitter.h" 

int main (int argc, char** argv)
{
	//std::setlocale(LC_ALL, "");
	std::string config_filename = argc >= 2 ? argv[1] : "conf/config.txt";
	
	configT config( config_filename );
	Splitter Processor( &config );
	Processor.process();
	return 0;
}