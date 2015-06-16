#ifndef CBOARDUTILS_H_DEFINED
#define CBOARDUTILS_H_DEFINED

#include <Game/CBoard.h>

#include <string>
#include <vector>


/// Exeption class that occurs if there was an error during loading a level.
///
class BadFileExeption 
	{
	public:
		BadFileExeption ( )
		{}
		
	};

/// Utilities for class CBoard, loads file with board, lists files
/// in folder with maps.
class CBoardUtils
	{
	public:
		CBoardUtils();
		~CBoardUtils();

		/// Loads and parses file with name `filename`.
		/// @note it looks for it in `./examples/maps/`, so only
		/// playing game from base directory will work.
		static CBoard * load_file ( const std::string & filename );

		/// lists all files with extension in folder.
		/// @note it looks for it in `./examples/maps/`, so only
		/// playing game from base directory will work.
		static std::vector<std::string> list_files ( const std::string & extension = "pacmap" );
	};

	
#endif //CBOARDUTILS_H_DEFINED
