#pragma once

class GDIPlusManager
{
public:
	GDIPlusManager();
	~GDIPlusManager();

private:
	static ULONG_PTR token;
	static int RefCount;

};