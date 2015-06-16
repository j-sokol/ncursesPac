#ifndef C2DARRAY_H_DEFINED
#define C2DARRAY_H_DEFINED

#include <vector>
#include <cstdlib>

/// Basically a 2D array of chars made with std::vector.
class C2DArray 
	{
	public:
		/// Creates a 2D array with `width` and `height`.
		C2DArray ( int width, int height )
			{
				array . resize ( width );
				for (int i = 0; i < width; ++i)
				{
					array [ i ] . resize ( height );
				}
			}
		~C2DArray () { };
		/// Returns element at `x` `y`.
		char at ( int x, int y ) const
			{
				return array [y] [x];
			}
		/// Sets `value` of element at `x` `y`.
		void set ( int x, int y, char value )
			{
				array [y] [x] = value;
			}
		/// Width size of the array.
		size_t width ( ) const
			{
				return array . size ();
			}
		/// Height size of the array.
		size_t height ( ) const
			{
				return array [0] . size ();
			}
	private:
		/// Internal vector storage of chars.
		std::vector < std::vector < char > > array;
	};
	
#endif //C2DARRAY_H_DEFINED
