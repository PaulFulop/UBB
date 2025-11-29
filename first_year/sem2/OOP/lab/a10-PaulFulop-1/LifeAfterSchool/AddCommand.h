#pragma once
#include "Command.h"

class AddCommand : public Command {
private:
	Event newEvent;
	WhichService whichServ;
public:
	AddCommand(ServiceAM* _globalServ, ServiceUM* _userServ, Event _newEvent, WhichService _whichServ);
	void Execute() override;
	void Undo() override;
};