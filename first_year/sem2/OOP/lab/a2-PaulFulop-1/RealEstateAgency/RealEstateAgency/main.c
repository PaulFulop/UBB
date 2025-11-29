#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <crtdbg.h>
#include <stdlib.h>
#include "ui.h"
#include "tests.h"

void TestAll();

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(236);

	UI* ui = CreateUI();
    Estate* est1 = NewEstate("house", "str1", 50, 10000);
    Estate* est2 = NewEstate("apartment", "str2", 60, 1234);
    Estate* est3 = NewEstate("penthouse", "str3", 2500, 1410200);
    Estate* est4 = NewEstate("penthouse", "str4", 1520, 2445100);
    Estate* est5 = NewEstate("house", "str5", 75, 1200);
    Estate* est6 = NewEstate("house", "str6", 230, 10540);
    Estate* est7 = NewEstate("house", "str7", 120, 8230);
    Estate* est8 = NewEstate("apartment", "str8", 125, 1345);
    Estate* est9 = NewEstate("apartment", "str9", 150, 1345);
    Estate* est10 = NewEstate("house", "str10", 170, 1000);

    AddEstate(ui->serv, est1);
    AddEstate(ui->serv, est2);
    AddEstate(ui->serv, est3);
    AddEstate(ui->serv, est4);
    AddEstate(ui->serv, est5);
    AddEstate(ui->serv, est6);
    AddEstate(ui->serv, est7);
    AddEstate(ui->serv, est8);
    AddEstate(ui->serv, est9);
    AddEstate(ui->serv, est10);

    Start(ui);
	DestroyUI(ui);

    DestroyEstate(est1);
    DestroyEstate(est2);
    DestroyEstate(est3);
    DestroyEstate(est4);
    DestroyEstate(est5);
    DestroyEstate(est6);
    DestroyEstate(est7);
    DestroyEstate(est8);
    DestroyEstate(est9);
    DestroyEstate(est10);

    TestAll();

	_CrtDumpMemoryLeaks();
	return 0;
}

void TestAll()
{
    TestEstate();
    TestRepo();
    TestOperationStack();
    TestService();
    printf("Everything is good!");
}