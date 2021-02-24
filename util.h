#include <string>

	// conversion from ISO 8859-1 to UTF-8
std::string iso_8859_1_to_utf8(std::string &str);

	// conversion from ISO 8859-2 to UTF-8
std::string iso_8859_2_to_utf8(std::string &str);

/* EXPERIMENTAL
 * Convert an UTF-8 string to ISO-8859-15.
 * All invalid sequences are ignored.
 * Note: output == input is allowed,
 * but   input < output < input + length
 * is not.
 * Output has to have room for (length+1) chars, including the trailing NUL byte.
 
 https://stackoverflow.com/questions/11156473/is-there-a-way-to-convert-from-utf8-to-iso-8859-1
*/
/*size_t */ std::string utf8_to_latin9(char *const output, const char *const input, const size_t length);
