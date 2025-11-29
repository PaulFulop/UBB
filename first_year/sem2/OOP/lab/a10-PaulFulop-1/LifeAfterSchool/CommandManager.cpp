#include "CommandManager.h"

void CommandManager::CommandExecute(Command* cmd) {
	undoStack.push(cmd);
	cmd->Execute();
	while (!redoStack.empty())
		redoStack.pop();
}

void CommandManager::CommandUndo() {
	if (!undoStack.empty()) {
		Command* cmd = undoStack.top();
		undoStack.pop();
		cmd->Undo();
		redoStack.push(cmd);
	}
}

void CommandManager::CommandRedo() {
	if (!redoStack.empty()) {
		Command* cmd = redoStack.top();
		redoStack.pop();
		cmd->Execute();
		undoStack.push(cmd);
	}
}