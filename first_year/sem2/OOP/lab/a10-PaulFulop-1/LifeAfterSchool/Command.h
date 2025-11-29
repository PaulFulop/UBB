#pragma once
#include "ServiceAM.h"
#include "ServiceUM.h"

enum WhichService{
	AdminService,
	UserService
};

class Command {
protected:
	ServiceAM* globalServ;
	ServiceUM* userServ;
public:
	Command(ServiceAM* _globalServ, ServiceUM* _userServ) : globalServ(_globalServ), userServ(_userServ) {}
	virtual ~Command() { globalServ->~ServiceAM(), userServ->~ServiceUM(); }

	virtual void Execute() = 0;
	virtual void Undo() = 0;
};