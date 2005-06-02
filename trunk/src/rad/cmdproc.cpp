
#include "cmdproc.h"

void CommandProcessor::Execute(PCommand command)
{
  command->Execute();
  m_undoStack.push(command);
  
  while (!m_redoStack.empty())
    m_redoStack.pop();
  
}

void CommandProcessor::Undo()
{
  if (!m_undoStack.empty())
  {
    PCommand command = m_undoStack.top();
    m_undoStack.pop();
    
    command->Restore();
    m_redoStack.push(command);
  }
}

void CommandProcessor::Redo()
{
  if (!m_redoStack.empty())
  {
    PCommand command = m_redoStack.top();
    m_redoStack.pop();
    
    command->Execute();
    m_undoStack.push(command);
  }
}

///////////////////////////////////////////////////////////////////////////////
Command::Command()
{
  m_executed = false;
}

void Command::Execute()
{
  if (!m_executed)
  {
    DoExecute();
    m_executed = true;
  }
}

void Command::Restore()
{
  if (m_executed)
  {
    DoRestore();
    m_executed = false;
  }
}

