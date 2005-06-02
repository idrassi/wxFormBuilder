#ifndef __COMMAND_PROC__
#define __COMMAND_PROC__

#include <stack>
#include <boost/smart_ptr.hpp>


using namespace std;
using namespace boost;

class Command;
typedef shared_ptr<Command> PCommand;

class CommandProcessor
{
 private:
  typedef stack<PCommand> CommandStack;
  
  CommandStack m_undoStack;
  CommandStack m_redoStack;
  
 public:
   void Execute(PCommand command);
   
   void Undo();
   void Redo();
};


class Command
{
 private:
  bool m_executed;
  
 protected:
  /**
   * Ejecuta el comando.
   */
  virtual void DoExecute() = 0;
  
  /**
   * Restaura el estado previo a la ejecución del comando.
   */
  virtual void DoRestore() = 0;
  
 public:
  Command();
  virtual ~Command() {};
  
  void Execute();
  void Restore();
};

#endif //__COMMAND_PROC__
