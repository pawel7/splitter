#include "configt.h"

	void configT::Error( string s )
	{
		std::cerr << s << std::endl;
		abort();
	}

		configT::configT()
		{			
			/*std::vector<colsT> my_columns= { colsT("osoby", 96, 26), colsT("miasto", 208, 17), colsT("adres", 229, 20) };
			source_filename = "sample-input.txt";
			output_filename = "output.txt";
			source_collation = "utf-8";
			destination_collation = "utf-8";
			table_name = "output";
			columns = my_columns;
			source_collation = "utf-8";
			table_one_insert_count = 10;
			sql_type_out = 1;
			split_files_every_rows = 5;*/
		}
				
		configT& configT::readConfig( string config_filename )
		{
			std::ifstream ConfigFile;
			string conf_line, column_name;
			int column_position, column_length;
		
			long line_no = 1;
			ConfigFile.open( config_filename );
			if (!ConfigFile.is_open()) 
			{
				Error( "Could not open config file " + config_filename );
			}
				// process input file
			while (getline(ConfigFile, conf_line)) 
			{		
					// ignore empty lines
				if( conf_line.length() == 0 ) continue;	
				
				size_t where_colon = conf_line.find(':');
				if( where_colon == std::string::npos )
				{
					string Errmsg = "Error: No colon in line " + std::to_string(line_no) + " in configuration file " + config_filename;
					Error( Errmsg );
				}
				string key = conf_line.substr(0, where_colon);
				
				string value = conf_line.substr( where_colon + 1 );
				std::size_t non_space_pos = value.find_first_not_of(" ");
				value = value.substr(non_space_pos);

				std::cout << std::setiosflags (std::ios::right )  << std::setw(25)<< key << " = " << value << std::endl;
				
				if ( key == "source_filename" )
				{
					source_filename = value;
				}
				else if ( key == "output_filename" )
				{
					output_filename = value;
				}
				else if ( key == "source_collation" )
				{
					source_collation = value;
				}
				else if ( key == "destination_collation" )
				{
					destination_collation = value;
				}
				else if ( key == "table_name" )
				{
					table_name = value;
				}
				else if ( key == "column_name" )
				{
					column_name = value;
				}
				else if ( key == "column_position" )
				{
					column_position = std::stoi(value);
				}
				else if ( key == "column_length" )
				{
					column_length = std::stoi(value);
					colsT mycols(column_name, column_position, column_length );
					columns.push_back(mycols);
				}
				else if ( key == "table_one_insert_count" )
				{
					table_one_insert_count = std::stoi(value);
				}
				else if ( key == "split_files_every_rows" )
				{
					split_files_every_rows = std::stol(value);
				}
				else if ( key == "sql_type_out" )
				{
					sql_type_out = std::stoi(value);
				}
				else 
				{
					Error("Unknown key: " + key);	
				};
				line_no++;
			}
			return *this;
		}
		
	void configT::showConfig()
	{
		std::cout << std::setiosflags (std::ios::right )  << std::setw(25) << "source_filename  =" << source_filename << std::endl;
		std::cout << "output_filename  =" << output_filename << std::endl;
		std::cout << "source_collation =" << source_collation << std::endl;
		std::cout << "destination_collation  =" << destination_collation << std::endl;
		std::cout << "table_name  =" << table_name << std::endl;
		
		std::cout << "table_one_insert_count  =" << table_one_insert_count << std::endl;
		std::cout << "sql_type_out  =" << sql_type_out << std::endl;
		std::cout << "split_files_every_rows  =" << split_files_every_rows << std::endl;
		for( auto col: columns )
		{
			std::cout << "name  =" << col.name << std::endl;
			std::cout << "position  =" << col.position << std::endl;
			std::cout << "length  =" << col.length << std::endl;
		}
	}
