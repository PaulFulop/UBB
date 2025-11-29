#include "UpdateCommand.h"

UpdateCommand::UpdateCommand(ServiceAM* _globalServ, ServiceUM* _userServ, Event _newEvent, Event _oldEvent, WhichService _whichServ):
	Command(_globalServ, _userServ), newEvent(_newEvent), oldEvent(_oldEvent), whichServ(_whichServ) { }

void UpdateCommand::Execute() {
	globalServ->UpdateEvent(oldEvent, newEvent);
}

void UpdateCommand::Undo() {
	globalServ->UpdateEvent(newEvent, oldEvent);
}