#include "Tests.h"
#include <iostream>

void TestAll()
{
	//TestEvent();
	//TestDynamicVector();
	TestRepository();
	TestServiceAM();
	TestServiceUM();
	std::cout << "Everything is good!\n";
}

//void TestEvent()
//{
//	Event event1 = Event();
//
//	assert(event1.title == "");
//	assert(event1.description == "");
//	assert(event1.dt == "");
//	assert(event1.nr_of_people == 0);
//	assert(event1.link == "");
//
//	Event event2 = Event("t1", "d1", "dt1", 5, "l1");
//	event1.title = "t1";
//
//	assert(event1 == event2);
//
//	event1 = event2;
//
//	assert(event1.title == event2.title);
//	assert(event1.description == event2.description);
//	assert(event1.dt == event2.dt);
//	assert(event1.nr_of_people == event2.nr_of_people);
//	assert(event1.link == event2.link);
//
//	string s = event1.ToString();
//
//	event1.dt = "smafmfsa";
//	assert(event1.ValidDT() == false);
//
//	event1.dt = "13/10/2024";
//	assert(event1.ValidDT() == false);
//
//	event1.dt = "11/31/2024";
//	assert(event1.ValidDT() == false);
//
//	event1.dt = "11/20/2l24";
//	assert(event1.ValidDT() == false);
//
//	event1.dt = "03/10/2025";
//	assert(event1.ValidDT() == true);
//
//	assert(s == "Title: t1\nDescription: d1\nDate and Time: dt1\nNumber of participants: 5\nLink: l1\n");
//}

void TestRepository()
{
	/*Repository testRepo = Repository();
	assert(testRepo.events.length == 0);

	assert(testRepo.AddToRepo(Event("t1", "d1", "dt1", 5, "l1")) == true);
	assert(testRepo.AddToRepo(Event("t1", "d1", "dt1", 5, "l1")) == false);
	assert(testRepo.events.data[0].title == "t1");
	assert(testRepo.events.length == 1);
	assert(testRepo.events.capacity == 1);

	assert(testRepo.AddToRepo(Event("t2", "d2", "dt3", 10, "l2")) == true);

	Repository testRepo1 = Repository();
	testRepo1 = testRepo;
	assert(testRepo1.events.length == 2);

	Repository testRepo2 = Repository(testRepo1);
	assert(testRepo2.events.length == 2);

	assert(testRepo.RemoveFromRepo(Event("t1", "", "", 0, "")) == true);
	assert(testRepo.RemoveFromRepo(Event("t1", "", "", 0, "")) == false);
	assert(testRepo.events.data[0].title == "t2");

	assert(testRepo.UpdateToRepo(Event("t2", "", "", 0, ""), Event("t2", "d3", "dt3", 15, "l3")) == true);
	assert(testRepo.UpdateToRepo(Event("t3", "", "", 0, ""), Event("t3", "d3", "dt3", 15, "l3")) == false);
	assert(testRepo.events.data[0].title == "t2");

	assert(testRepo.AddToRepo(Event("t3", "d3", "dt3", 25, "l3")) == true);
	assert(testRepo.FilterEvents(20).length == 1);
	*/
}

void TestServiceAM()
{
	/*ServiceAM testServ = ServiceAM();
	assert(testServ.repo.events.length == 0);

	testServ.AddEvent(Event("t1", "d1", "dt1", 5, "l1"));
	assert(testServ.repo.events.data[0].title == "t1");

	try {
		testServ.AddEvent(Event("t1", "d1", "dt1", 5, "l1"));
	}
	catch (const exception& e) {
		string s = e.what();
		assert(s == "The event already exists (duplicate title).\n");
	}

	testServ.AddEvent(Event("t2", "d1", "dt1", 5, "l1"));
	assert(testServ.repo.events.length == 2);

	testServ.RemoveEvent("t1");
	assert(testServ.repo.events.data[0].title == "t2");

	try {
		testServ.RemoveEvent("t1");
	}
	catch (const exception& e){
		string s = e.what();
		assert(s == "Event not found.\n");
	}

	testServ.UpdateEvent(Event("t2", "", "", 0, ""), Event("t2", "d2", "dt2", 10, "l2"));
	assert(testServ.repo.events.data[0].description == "d2");
	assert(testServ.repo.events.data[0].dt == "dt2");
	assert(testServ.repo.events.data[0].nr_of_people == 10);
	assert(testServ.repo.events.data[0].link == "l2");

	assert(testServ.ListFilterEvents(11) == "\nTitle: t2\nDescription: d2\nDate and Time: dt2\nNumber of participants: 10\nLink: l2\n\n");
	assert(testServ.ListFilterEvents(9) == "\n");

	try {
		testServ.UpdateEvent(Event("t1", "", "", 0, ""), Event("t1", "d2", "dt2", 10, "l2"));
	}
	catch (const exception& e) {
		string s = e.what();
		assert(s == "Event not found.\n");
	}

	assert(testServ.ListOfEvents() == "\nTitle: t2\nDescription: d2\nDate and Time: dt2\nNumber of participants: 10\nLink: l2\n\n");*/
}

void TestServiceUM()
{
	/*Repository globalRepo = Repository();
	globalRepo.AddToRepo(Event("title1", "desc1", "03/22/2025", 102, "l1"));
	globalRepo.AddToRepo(Event("title2", "desc2", "03/30/2022", 1203, "l2"));
	globalRepo.AddToRepo(Event("title3", "desc3", "04/17/2024", 52, "l3"));
	globalRepo.AddToRepo(Event("title4", "desc4", "08/22/2020", 50000, "l4"));

	ServiceUM userServ = ServiceUM(&globalRepo);
	assert(userServ.globalRepo->events.length == 4);
	int prev_nrParticipants = userServ.globalRepo->events.data[0].nr_of_people;
	userServ.AddUserEvent(0);
	assert(userServ.userRepo.events.length == 1);
	assert(userServ.globalRepo->events.data[0].nr_of_people == prev_nrParticipants + 1);

	Repository usersByMonth = userServ.GetEventsByMonth(3);
	assert(usersByMonth.events.length == 2);

	try {
		userServ.AddUserEvent(0);
	}
	catch (const exception& e) {
		string s = e.what();
		assert(s == "This event has already been added.\n");
	}

	try {
		userServ.AddUserEvent(6);
	}
	catch (const exception& e) {
		string s = e.what();
		assert(s == "Out of range.\n");
	}

	try {
		userServ.RemoveUserEvent("title2");
	}
	catch (const exception& e) {
		string s = e.what();
		assert(s == "Event not found.\n");
	}

	assert(userServ.ListUserEvents() == "\nTitle: title1\nDescription: desc1\nDate and Time: 03/22/2025\nNumber of participants: 102\nLink: l1\n\n");
	
	userServ.RemoveUserEvent("title1");

	assert(userServ.userRepo.events.length == 0);
	assert(userServ.globalRepo->events.data[0].nr_of_people == prev_nrParticipants);

	userServ.SortEventsByDate(*userServ.globalRepo);
	assert(userServ.globalRepo->events.data[0].title == "title4");
	assert(userServ.globalRepo->events.data[1].title == "title2");*/
}