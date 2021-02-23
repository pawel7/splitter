#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using std::string;


	struct colsT
	{
		string name;
		int position;
		int length;
		colsT( string aname, int aposition, int alength ): name(aname), position(aposition), length(alength){}
	};
	
	struct configT
	{
		string source_filename;
		string output_filename;
		string source_collation;
		string destination_collation;
		string table_name;
		std::vector<colsT> columns;
		int table_one_insert_count;
		int sql_type_out;
		long split_files_every_rows;
		configT();
		configT& readConfig( string config_filename );
		void showConfig();	
		void Error( string s );
	};
