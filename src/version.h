#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "03";
	static const char MONTH[] = "05";
	static const char YEAR[] = "2009";
	static const double UBUNTU_VERSION_STYLE = 9.05;
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 7;
	static const long REVISION = 17;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 4;
	#define RC_FILEVERSION 0,1,7,17
	#define RC_FILEVERSION_STRING "0, 1, 7, 17\0"
	static const char FULLVERSION_STRING[] = "0.1.7.17";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 6;
	

}
#endif //VERSION_h
