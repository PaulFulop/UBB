#pragma once
#include "Command.h"

class RemoveCommand : public Command {
private:
	Event event;
	WhichService whichServ;
public:
	RemoveCommand(ServiceAM* _globalServ, ServiceUM* _userServ, Event _event, WhichService _whichServ);
	void Execute() override;
	void Undo() override;
};