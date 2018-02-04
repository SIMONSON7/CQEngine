#ifndef __C2S_H__
#define __C2S_H__

enum C2S_CODE
{
	HEART = 0,
	LOGIN,
	LOGIN_RET,
	LOGOUT,

	STICKPKG_TEST
};

struct Header
{
	short code_;
	short len_;
};

struct Package
{
	Header head_;
};

struct HeartPackage : public Package
{
	HeartPackage()
	{
		head_.code_ = HEART;
		head_.len_ = sizeof(HeartPackage);
	}
};

struct LoginPackage : public Package
{
	LoginPackage()
	{
		head_.code_ = LOGIN;
		head_.len_ = sizeof(LoginPackage);
	}

	char name_[32];
	char pwd_[32];
};

struct LoginRetPackage : public Package
{
	LoginRetPackage()
	{
		head_.code_ = LOGIN_RET;
		head_.len_ = sizeof(LoginRetPackage);
	}
	char result_[64];
};

struct StickPackageTest : public Package
{
	StickPackageTest()
	{
		head_.code_ = STICKPKG_TEST;
		head_.len_ = sizeof(StickPackageTest);
	}
	char data_[20480];
};

#endif