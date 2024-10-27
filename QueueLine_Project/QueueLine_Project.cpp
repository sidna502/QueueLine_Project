#include <iostream>
#include "clsQueueLine.h"


int main()
{
	system("color 5f");
	clsQueueLine PayBillsQueue("A0", 10);

	PayBillsQueue.IssueTicket();
	PayBillsQueue.IssueTicket();
	PayBillsQueue.IssueTicket();
	PayBillsQueue.IssueTicket();
	PayBillsQueue.IssueTicket();

	cout << "Pay Bills Queue Info:\n\n";
	PayBillsQueue.PrintInfo();

	PayBillsQueue.PrintTicketsLineRTL();
	PayBillsQueue.PrintTicketsLineLTR();

	PayBillsQueue.PrintAllTickets();

	PayBillsQueue.ServeNextClient();
	cout << "\nPay Bills Queue after serving queue client:\n\n";
	PayBillsQueue.PrintInfo();

	system("pause > 0");
}

