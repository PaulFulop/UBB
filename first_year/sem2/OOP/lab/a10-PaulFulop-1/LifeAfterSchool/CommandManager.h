#pragma once
#include "Command.h"
#include <stack>

class CommandManager {
private:
	std::stack<Command*> undoStack;
	std::stack<Command*> redoStack;
public:
	void CommandExecute(Command* cmd);
	void CommandUndo();
	void CommandRedo();
};