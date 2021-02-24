#include <iostream>
#include <fstream>
#include <string>

#include "configt.h"

class Splitter
{
public:
	Splitter(const configT* pconfig);
	int process();	// Process input file
protected:
	const configT* pconfig;		// pointer to configuration read from a file
	std::ifstream inp;     		// input file
	std::ofstream out;
	std::string inp_fname;		// input filename
	std::string out_fname;		// output filename, it changes after writing split_files_every_rows lines
	std::string out_name_only;	// output filename without extension
	std::string out_extension;	// its extension

		// substd::string of utf-8 codepoints
	std::string utf8_substr(const std::string& src, size_t begin, size_t len);
	
		// start of the query text: "INSERT INTO <table_name> ( <column_names> ) VALUES"
	std::string start_query_text();
};
