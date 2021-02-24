#include <fstream>
#include <clocale>
#include <iomanip>

#include "utfcpp\source\utf8.h"
#include "configt.h"
#include "splitter.h"
#include "util.h"

std::string Splitter::start_query_text()
{
	std::string column_names="";
	for(auto const& column : pconfig->columns ) 
	{
		column_names += column.name + ", ";
	}
	column_names = column_names.substr( 0, column_names.size() - 2 ); // cut last ", "
	
	return "INSERT INTO " + pconfig->table_name + " ( " + column_names + " ) VALUES \n";
}
	
Splitter::Splitter(const configT* _pconfig)
{
	pconfig = _pconfig;
	inp_fname = pconfig->source_filename;
	out_fname = pconfig->output_filename;
	
	std::string path = out_fname;
	
    size_t dot = path.find_last_of(".");
    if (dot != std::string::npos)
    {
        out_name_only = path.substr(0, dot);
        out_extension = path.substr(dot);
    }
    else
    {
        out_name_only = path;
        out_extension = "";
    }
	//std::cout << "out_name_only = " << out_name_only << ", out_extension = " << out_extension << std::endl;
	
	inp.open(inp_fname);
	out.open(out_fname);
	if (!inp.is_open()) {
    	std::cout << "Could not open " << inp_fname << std::endl;
    }

	if (!out.is_open()) {
    	std::cout << "Could not open " << out_fname << std::endl;
    }
	else 
		std::cout << "Opened output file " << out_fname << std::endl;

}

// Arguments:
//  - src - the source std::string, encoded as UTF-8
//  - begin, len - substd::string offsets, in (variable length) chars, not in bytes!
// Result:
//  - if begin > length of src (counted in chars, not in bytes), an empty std::string
//  - if begin + len > length of src (counted in chars, not in bytes), all chars
//    from the one at index begin until the end of src
//  - otherwise, all characters from index begin up to index (begin+len-1),
//    with indices counted in chars, not bytes)
// Throws:
//  - all exceptions thrown by the underlying functions.
std::string Splitter::utf8_substr(const std::string& src, size_t begin, size_t len) {
   size_t i = 0;
   auto it = src.begin();
   while (i < begin) {
      utf8::next(it, src.end());
      if (it == src.end())
         return std::string();
      ++i;
   }
   auto result_begin = it;
   for (; len > 0; --len) {
      utf8::next(it, src.end());
      if (it == src.end())
         return std::string(result_begin, src.end());
   }
   return std::string(result_begin, it);
}

int Splitter::process()
{
	unsigned long line_count = 1;		// input file line counter
    unsigned long out_line_count = 1;	// counter of lines in current output file
    std::string line, part, out_line;
	std::string last_chars; // in output line after all values
	std::string _start_query_text = start_query_text();
			
	int columns_cnt = pconfig->columns.size();
	int out_filename_suffix = 0;		// last part of output filename, when > 0
	
	if( pconfig->source_encoding != "utf-8" ) 
	{
		std::setlocale(LC_ALL, "");
	}
	//else std::setlocale(LC_ALL, "en_US.UTF-8");
		
	    // process input file
    while (getline(inp, line)) {

		if( pconfig->source_encoding == "utf-8" )
		{
				// check for invalid utf-8 
				std::string::iterator end_it = utf8::find_invalid(line.begin(), line.end());
				if (end_it != line.end()) {
					std::cout << "Invalid UTF-8 encoding detected at line " << std::dec << line_count << "\n";
					std::cout << "This part is fine: " << std::string(line.begin(), end_it) << "\n";
					continue;
				}
					// Get the line length
				int length = utf8::distance(line.begin(), end_it);
				// std::cout << dec << "Length of line " << line_count << " is " << length <<  " chars and " << line.size() << " bytes\n";
		}
		
			// prepare output line
		if( out_line_count % pconfig->table_one_insert_count == 1 )
		{
			out_line = _start_query_text;
		}
		
		out_line += " ( ";
			
			// extract values
		int i = 0;
		for( auto column: pconfig->columns )
		{
			if( pconfig->source_encoding == "utf-8" )
			{
				part = utf8_substr(line, column.position - 1, column.length );
				//std::cout <<  pconfig->source_encoding << " --> " <<  pconfig->destination_encoding << std::endl;
				if( pconfig->destination_encoding == "ISO-8859-1" )
				{	
					// Experimental !!
					std::string out_part, outstr;
					int len = part.size() + 1;
					outstr.reserve( len );
					char *const output = (char * const )outstr.c_str();
					out_part = utf8_to_latin9( output, part.c_str(), len-1);
					part = out_part;
					// std::string utf8_to_latin9(char *const output, const char *const input, const size_t length);
				}
			}
			else if( pconfig->source_encoding == "ISO-8859-1" )
			{
				part = line.substr( column.position - 1, column.length );
				
				if( pconfig->destination_encoding == "utf-8" )
				{
					//std::setlocale(LC_ALL, "en_US.UTF-8");
					part = iso_8859_1_to_utf8( part );
				}
			}
			else if( pconfig->source_encoding == "ISO-8859-2" )
			{
				part = line.substr( column.position - 1, column.length );
				
				if( pconfig->destination_encoding == "utf-8" )
				{
					// to nie działa dobrze
					part = iso_8859_2_to_utf8( part );
				}
			}

			out_line += '"' + part + '"';
			i++;
			if( i < columns_cnt ) out_line += ", ";
		}

		std::string end_sql = pconfig->sql_type_out == 2 ? ";\n" : ";\nGO";
		
		last_chars = (inp.peek() == EOF) || 
			( line_count % pconfig->split_files_every_rows == 0 ) ||
			(( out_line_count - 1) % pconfig->table_one_insert_count == pconfig->table_one_insert_count - 1) ? end_sql : ",";

		out_line += " )" + last_chars + "\n";
				
		out.write(out_line.c_str(), out_line.size());//strlen(out_line.c_str()));
		out_line = "";

			// close current and open next output file, adjust out_line and out_line_count variables
		if( line_count % pconfig->split_files_every_rows == 0 )
		{
			out.close();
			out_filename_suffix++;
			
			out_fname = out_name_only + "_" + std::to_string( out_filename_suffix ) + out_extension;
			out.open(out_fname);
			if (!out.is_open()) {
				std::cout << "Could not open output file " << out_fname << std::endl;
			}		
			std::cout << "Opened output file " << out_fname << std::endl;

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

