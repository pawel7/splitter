#ifndef configt_h
#define configt_h

#include <string>
#include <vector>


	struct colsT
	{
		std::string name;
		int position;
		int length;
		colsT( std::string aname, int aposition, int alength ): name(aname), position(aposition), length(alength){}
	};
	
	struct configT
	{
		std::string source_filename;
		std::string output_filename;
		std::string source_encoding;
		std::string destination_encoding;
		std::string table_name;
		std::vector<colsT> columns;
		int table_one_insert_count;
		int sql_type_out;
		long split_files_every_rows;
		configT( std::string config_filename );
		//configT(const configT& x);
		//configT& operator= (const configT& x);
		void showConfig();	
		void Error( std::string s );
	};
#endif // header guard