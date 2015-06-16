#include <Game/CBoardUtils.h>

#include <dirent.h>
#include <algorithm>
#include <sys/stat.h>
#include <iostream>
#include <fstream>


CBoard * CBoardUtils::load_file ( const std::string & name )
	{
		std::string tmp_line;
		int ghost_x    = 0;
		int ghost_y    = 0;
		int player_x   = 0;
		int player_y   = 0;
		int	width      = 0;
		int height     = 0;
		int dots       = 0;
		int line_count = 0;
		bool bad_file  = false;

		static std::string directory = "./examples/maps/";
		static std::string extension = "pacmap";

		std::string filepath  = ( directory + name + "." + extension );
		std::ifstream file ( filepath );
		std::vector < std::string > board_lines;
		std::vector < std::vector < char > > tmp_board;

		if ( ! file . good () )
			bad_file = true; 

		while ( getline ( file, tmp_line))
			{
				// ....
				if ( tmp_line == "Player position:")
					file >> std::skipws >> player_x >> player_y ;
				
				if ( tmp_line == "Ghost position:")
					file >> std::skipws >> ghost_x >> ghost_y ;

				if ( tmp_line == "Map definition:")
					while ( getline ( file, tmp_line))
					{
						if ( tmp_line == "End of map definition.")
						{
							break;	
						}
						
						board_lines . push_back ( tmp_line );
						++line_count;
					}
			}
		if ( board_lines . size () < 5  || board_lines [0] . size () < 5 ||
			 !ghost_x || !ghost_y || !player_y || !player_x )
			bad_file = true;

		for (unsigned int i = 0; i < board_lines . size (); ++i)
		{
			if ( board_lines [0] . size () != board_lines [i] . size () )
				bad_file = true; 

			std::vector < char > char_line;

			for (unsigned int j = 0; j < board_lines[0] . size (); ++j)
			{
				char_line . push_back (board_lines[i] [j]);
				if ( board_lines[i] [j] == '.' || board_lines[i] [j] == '*' )
					dots++;

			}

			tmp_board . push_back ( char_line );
		}

		if ( bad_file )
			throw BadFileExeption(); 

		width  = tmp_board  . size();
		height = tmp_board [0] . size();

		CBoard * board = new CBoard ( width, height, dots);
		board -> set_board ( tmp_board );
		board -> set_start_pos ( std::make_pair ( player_x, player_y ));
		board -> set_ghost_start_pos ( ghost_x, ghost_y );

		if ((! board -> is_empty_spot ( player_x, player_y ) &&
			 ! board -> is_dot        ( player_x, player_y ) &&
			 ! board -> is_star       ( player_x, player_y )) ||
			(! board -> is_empty_spot ( ghost_x, ghost_y ) &&
			 ! board -> is_dot        ( ghost_x, ghost_y ) &&
			 ! board -> is_star       ( ghost_x, ghost_y )))
			{
				std::cerr << "problem here";
				delete board;
				throw BadFileExeption(); 
			}

		return board;
	}
std::vector<std::string> CBoardUtils::list_files ( const std::string & extension )
	{
		struct dirent * dp;
   	std::vector<std::string> list_files;
		struct stat st;
    if( stat( "./examples/maps/", &st ) )
        return list_files;

   	auto dirp = opendir("./examples/maps/");
   	std::string name;
   	
   

   	while ((dp = readdir(dirp)) != NULL)
    	{
    		name = dp -> d_name;
    		if ( name.substr ( name.find_last_of(".") + 1) == extension) 
    			{
    				name.erase(name.find_last_of("."), std::string::npos);
    				list_files . push_back ( name );
    			}


    	}
   	(void)closedir(dirp);
   	std::stable_sort (list_files.begin(), list_files.end());

   	return list_files;
	}