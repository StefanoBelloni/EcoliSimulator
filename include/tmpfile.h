#ifndef TMPFILE_H
#define TMPFILE_H

#include <fstream>
#include <sstream>
#include "constants.h"
#include "GlobalVariables.h"
#include <iomanip>

/*This is not exactly the max file size, but the limit to
 * save in the HD. */


/**
 * This class is a wrapper to the ofstream used to save temporary
 * files of the simulations. One saves first into the mSizeBuf,
 * after one reaches the MAX_SIZE_TMP_FILE we write onto the ofstream.
 */

class TmpFile
{

 public:

	TmpFile(); /*!< constructor*/
	TmpFile(const char* name);
	int open(const char* name, std::ios_base::openmode mode = std::ios_base::out);
	int close();
	bool is_open();

	template<typename T>
	TmpFile& operator<<(const T& inp_str);
	TmpFile& operator<<(const char *str);

 private:
	const char* mName;
	std::ios_base::openmode mMode;
	unsigned long mSizeBuf;
	unsigned long mMaxSize;
	std::stringstream mTmpBuf;
	void writeTmpFile();
	std::ofstream mTmpfile;

};

#endif
