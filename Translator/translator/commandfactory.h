#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "transl.h"


class AbstractCmdCreator
{
public:
  virtual AbstractCmdCreator() { }
  virtual Command* CreateCommand(typename Command::CommandMap* marks) const = 0;
};


template <class cmd>
class CmdCreator: public AbstractCmdCreator
{
public:
  virtual Command* CreateCommand(typename Command::CommandMap* marks) const {
    return new cmd(marks);
  }
};

class CommandFactory
{
public:
  CommandFactory();
  virtual ~CommandFactory();

  Command* CreateCommand(std::string& name_of_cmd) const;
  void Add(const std::string& name_of_cmd);
  Command* Create(const std::string& name_of_cmd, typename Command::CommandMap* marks);
  void FillCommands();
};

typedef std::map<std::string, AbstractCmdCreator*> FactoryMap;

FactoryMap factory_map_;

template <class cmd>
void CommandFactory::Add(const std::string& name_of_cmd)
{
  typename FactoryMap::iterator iter = factory_map_.find(name_of_cmd);
  if (iter == factory_map_.end())
    factory_map_[name_of_cmd] = new CmdCreator<cmd>();
}

Command* CommandFactory::Create(const string &name_of_cmd, typename Command::CommandMap* marks)
{
  typename FactoryMap::iterator iter = factory_map_.find(name_of_cmd);
  if (iter == factory_map_.end())
    return iter->second->CreateCommand(marks);
  return nullptr;
}

void CommandFactory::FillCommands()
{
  Add<PushCmd>(string("push"));
  Add<PopCmd>(string("pop"));
  Add<JmpCmd>(string("jmp"));
  Add<JlCmd>(string("jl"));
  Add<JleCmd>(string("jle"));
  Add<JeCmd>(string("je"));
  Add<JneCmd>(string("jne"));
  Add<JgeCmd>(string("jge"));
  Add<JgCmd>(string("jg"));
  Add<CallCmd>(string("call"));
  Add<RetCmd>(string("ret"));
  Add<AddCmd>(string("add"));
  Add<SubCmd>(string("sub"));
  Add<MulCmd>(string("mul"));
  Add<DivCmd>(string("div"));
  Add<SqrtCmd>(string("sqrt"));
  Add<NormCmd>(string("norm"));
  Add<EndCmd>(string("end"));
  Add<AbsCmd>(string("abs"));
}

#endif // COMMANDFACTORY_H
