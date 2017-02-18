#include "tmpfile.h"

TmpFile::TmpFile(){
	mMaxSize = SIZE_SINGLE_TMP_FILE;
	mSizeBuf = 0;
}

TmpFile::TmpFile(const char* name){
	mMaxSize = SIZE_SINGLE_TMP_FILE;
	mSizeBuf = 0;
}

bool TmpFile::is_open(){
	return mTmpfile.is_open();
}

void TmpFile::writeTmpFile(){

	if (!mTmpfile.is_open()){
		mTmpfile.open(mName, mMode);
	}
	mTmpfile << mTmpBuf.str();
	mTmpBuf.clear();
	mSizeBuf = 0;
}

int TmpFile::open(const char* name, std::ios_base::openmode mode){
	mSizeBuf = 0;
	mName = name;
	mMode=mode;
	mTmpfile.open(mName, mMode);

	return 0;
}

int TmpFile::close(){

	if (mSizeBuf>0){
		writeTmpFile();
	}
	mTmpfile.close();
	return 0;
}

template<typename T>
TmpFile& TmpFile::operator<<(const T& str){

	if ( mSizeBuf > mMaxSize){
		writeTmpFile();
	}
	mTmpBuf << std::setprecision(precision_output) << str;
	//mSizeBuf = mTmpBuf.str().length();
	mSizeBuf = (unsigned long)mTmpBuf.seekg(0, std::ios::end).tellg();
	return *this;
}


TmpFile& TmpFile::operator<<(const char *str){

	if ( mSizeBuf > mMaxSize){
		writeTmpFile();
	}
	mTmpBuf << std::setprecision(precision_output) << str;
	//mSizeBuf = mTmpBuf.str().length();
	mSizeBuf = (unsigned long)mTmpBuf.seekg(0, std::ios::end).tellg();
	//mSizeBuf+=precision_output;
	return *this;
}


template TmpFile& TmpFile::operator<<(const std::string& str);
template TmpFile& TmpFile::operator<<(const char& str);
template TmpFile& TmpFile::operator<<(const long double& str);
template TmpFile& TmpFile::operator<<(const int& str);
template TmpFile& TmpFile::operator<<(const unsigned int& str);

/*
template<>
TmpFile& TmpFile::operator<<(const double& str){

	if ( mSizeBuf > mMaxSize){
		writeTmpFile();
	}
	mTmpBuf << std::setprecision(precision_output) << str;
	mSizeBuf+=20; //TODO: right value
	return *this;
}
*/
