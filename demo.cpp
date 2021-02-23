#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
#include "utfcpp\source\utf8.h"
#include "configt.cpp"

using namespace std;

class Splitter
{
public:
	Splitter();
	int process();	// Process input file
protected:
	configT config;
	int cols[2];
	int col_len[2];
	ifstream inp;     // input file (must be UTF-8 encoded)
	ofstream out;
	char *linia;
	int ind; // index in linia
	string inp_fname, out_fname;
	
	string utf8_substr(const string& src, size_t begin, size_t len);
	
		// start of the query text: "INSERT INTO <table_name> ( <column_names> ) VALUES"
	string start_query_text();
};

string Splitter::start_query_text()
{
	string column_names="";
	for(auto const& column : config.columns ) 
	{
		column_names += column.name + ", ";
	}
	column_names = column_names.substr( 0, column_names.size() - 2 ); // cut last ", "
	
	return "INSERT INTO " + config.table_name + " ( " + column_names + " ) VALUES \n";
}
	
Splitter::Splitter()
{
	string config_filename = "config.txt";
	config.readConfig( config_filename );
	cols[1]=105;
	col_len[0]=6;
	col_len[1]=10;
	ind = 0;
	inp_fname = config.source_filename;
	out_fname = config.output_filename;
	inp.open(inp_fname);
	out.open(out_fname);
	if (!inp.is_open()) {
    	cout << "Could not open " << inp_fname << endl;
    }

	if (!out.is_open()) {
    	cout << "Could not open " << out_fname << endl;
    }
	else 
		cout << "Opened output file " << out_fname << endl;

}

// Arguments:
//  - src - the source string, encoded as UTF-8
//  - begin, len - substring offsets, in (variable length) chars, not in bytes!
// Result:
//  - if begin > length of src (counted in chars, not in bytes), an empty string
//  - if begin + len > length of src (counted in chars, not in bytes), all chars
//    from the one at index begin until the end of src
//  - otherwise, all characters from index begin up to index (begin+len-1),
//    with indices counted in chars, not bytes)
// Throws:
//  - all exceptions thrown by the underlying functions.
string Splitter::utf8_substr(const string& src, size_t begin, size_t len) {
   size_t i = 0;
   auto it = src.begin();
   while (i < begin) {
      utf8::next(it, src.end());
      if (it == src.end())
         return string();
      ++i;
   }
   auto result_begin = it;
   for (; len > 0; --len) {
      utf8::next(it, src.end());
      if (it == src.end())
         return string(result_begin, src.end());
   }
   return string(result_begin, it);
}

int Splitter::process()
{
    unsigned long line_count = 1;		// input file line counter
    unsigned long out_line_count = 1;	// counter of lines in current output file
    string line, part, out_line;
	string last_chars; // in output line after all values
	string _start_query_text = start_query_text();
			
	int columns_cnt = config.columns.size();
	int out_filename_suffix = 0;		// last part of output filename, when > 0
	
	    // process input file
    while (getline(inp, line)) {

		if( config.source_collation == "utf-8" )
		{
				// check for invalid utf-8 
				string::iterator end_it = utf8::find_invalid(line.begin(), line.end());
				if (end_it != line.end()) {
					cout << "Invalid UTF-8 encoding detected at line " << dec << line_count << "\n";
					cout << "This part is fine: " << string(line.begin(), end_it) << "\n";
					continue;
				}
					// Get the line length
				int length = utf8::distance(line.begin(), end_it);
				// cout << dec << "Length of line " << line_count << " is " << length <<  " chars and " << line.size() << " bytes\n";
		}
		//else if( config.source_collation == "ISO-8859-1" )//utf8mb4
		
			// prepare output line
		if( out_line_count % config.table_one_insert_count == 1 )
		{
			out_line = _start_query_text;
		}
		
		out_line += " ( ";
			
			// extract values
		int i = 0;
		for( auto column: config.columns )
		{
			if( config.source_collation == "utf-8" )
			{
				part = utf8_substr(line, column.position - 1, column.length );
			}
			else if( config.source_collation == "ISO-8859-1" )
			{
				part = line.substr( column.position - 1, column.length );
			}
			out_line += '"' + part + '"';
			i++;
			if( i < columns_cnt ) out_line += ", ";
		}

		string end_sql = config.sql_type_out == 2 ? ";\n" : ";\nGO";
		
		last_chars = (inp.peek() == EOF) || 
			( line_count % config.split_files_every_rows == 0 ) ||
			(( out_line_count - 1) % config.table_one_insert_count == config.table_one_insert_count - 1) ? end_sql : ",";

		out_line += " )" + last_chars + "\n";
				
		out.write(out_line.c_str(), out_line.size());//strlen(out_line.c_str()));
		out_line = "";

			// close current and open next output file, adjust out_line and out_line_count variables
		if( line_count % config.split_files_every_rows == 0 )
		{
			out.close();
			out_filename_suffix++;
			out_fname = config.output_filename + "_" + std::to_string( out_filename_suffix );
			out.open(out_fname);
			if (!out.is_open()) {
				cout << "Could not open output file " << out_fname << endl;
			}		
			cout << "Opened output file " << out_fname << endl;

			out_line_count = 0;
			out_line = _start_query_text;	// for the beginning of a file
		}		

        line_count++;
		out_line_count++;
    } 
	inp.close();
	out.close();
    return 0;
}

int main (int argc, char** argv)
{
	Splitter Proc;
	Proc.process();
	return 0;
}