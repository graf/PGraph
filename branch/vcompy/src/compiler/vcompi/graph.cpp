#include "graph.h"

PROJECT_BEGIN_NAMESPACE
//DefineGraph::DefineGraph(int NambPred, int NambTop)
//{
//    this->NambPred = NambPred;
//    this->NambTop = NambTop;
//}

DefineGraph::DefineGraph(int NambPred, int NambTop, int Type)
{
    this->NambPred = NambPred;
    this->NambTop = NambTop;
	this->Type = Type;
}

DefineTop::DefineTop(const char *NameTop, int FirstDef, int LastDef, int (*top)(TPOData *))
{
    this->NameTop = NameTop;
    this->FirstDef = FirstDef;
    this->LastDef = LastDef;
    this->top = top;
}

DefinePredicate::DefinePredicate(const char *name, int (*predicate)(TPOData *))
{
    this->name = name;
    this->predicate = predicate;
}
PROJECT_END_NAMESPACE
