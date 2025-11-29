#include "RemoveCommand.h"

RemoveCommand::RemoveCommand(ServiceAM* _globalServ, ServiceUM* _userServ, Event _event, WhichService _whichServ): 
	Command(_globalServ, _userServ), event(_event), whichServ(_whichServ){ }

void RemoveCommand::Execute() {
	whichServ == AdminService ? globalServ->RemoveEvent(event.title) : userServ->RemoveUserEvent(event.title);
}

void RemoveCommand::Undo() {
	whichServ == AdminService ? globalServ->AddEvent(event) : userServ->AddUserEvent(userServ->FindEvent(event));
}