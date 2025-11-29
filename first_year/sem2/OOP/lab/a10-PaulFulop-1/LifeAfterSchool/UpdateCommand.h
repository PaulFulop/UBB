#pragma once
#include "Command.h"

class UpdateCommand : public Command {
private:
	Event newEvent, oldEvent;
	WhichService whichServ;
public:
	UpdateCommand(ServiceAM* _globalServ, ServiceUM* _userServ, Event _newEvent, Event _oldEvent, WhichService _whichServ);
	void Execute() override;
	void Undo() override;
};