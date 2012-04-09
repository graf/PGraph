#include "graph.h"
PROJECT_BEGIN_NAMESPACE
int P282E6F54(TPOData *D);
int P8095298(TPOData *D);
int G848B1898(TPOData *D);
int A8C6F61DD(TPOData *D);
int AFC8A1A59(TPOData *D);
int ABE7A0F38(TPOData *D);
int ADCBC8AD7(TPOData *D);
int AEF49659B(TPOData *D);
int ADF8D7A12(TPOData *D);
static DefinePredicate ListPred[2] = {
	DefinePredicate("P282E6F54", &P282E6F54),
	DefinePredicate("P8095298", &P8095298)
};
static DefineTop ListTop[6] = {
	DefineTop("AEF49659B", 0, 0, &AEF49659B),
	DefineTop("A8C6F61DD", 1, 1, &A8C6F61DD),
	DefineTop("ABE7A0F38", 2, 2, &ABE7A0F38),
	DefineTop("AFC8A1A59", 3, 4, &AFC8A1A59),
	DefineTop("ADCBC8AD7", 5, 5, &ADCBC8AD7),
	DefineTop("ADF8D7A12", -77, -77, &ADF8D7A12)
};
static DefineGraph ListGraf[6] = {
	DefineGraph(0, 2),
	DefineGraph(0, 3),
	DefineGraph(0, 1),
	DefineGraph(1, 2),
	DefineGraph(0, 4),
	DefineGraph(0, 5)
};
int G848B1898(TPOData *D)
{
	//Распределение номеров процессоров для ППА
	//printf("Распределение номеров процессоров для ППА\r\n");
	int topCount = 6;
	int rootTop = 0;
	GraphMV(D, rootTop, topCount, ListPred, ListTop, ListGraf);
	return 1;
}
PROJECT_END_NAMESPACE
