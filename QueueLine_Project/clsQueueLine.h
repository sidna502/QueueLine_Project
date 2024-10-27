#pragma once
#include "clsDate.h"
#include <queue>
#include <stack>
#include <iomanip>
using namespace std;


class clsQueueLine
{
	short _TotalTickets = 0;
	short _AverageServeTime = 0;
	string _Prefix = "";

	class clsTicket
	{
		short _AverageServeTime = 0;
		string _Prefix = "";
		string _TicketTime = "";
		short _WaitingClients = 0;
		short _Number = 0;
		//short _ExpectedServeTime = 0;

	public:
		clsTicket(string Prefix, short Number, short WaitingClients, short AverageServeTime)
		{
			_Prefix = Prefix;
			_Number = Number;
			_WaitingClients = WaitingClients;
			_AverageServeTime = AverageServeTime;
			_TicketTime = clsDate::GetSystemDateTimeString();

		}
		string Prefix()
		{
			return _Prefix;
		}
		string TicketTime()
		{
			return _TicketTime;
		}
		short Number()
		{
			return _Number;
		}
		string FullNumber()
		{
			return _Prefix + to_string(_Number);
		}
		short WaitingClients()
		{
			return _WaitingClients;
		}
		short ExpectedServeTime()
		{
			return _AverageServeTime * _WaitingClients;
		}
		void Print()
		{

			cout << left << setw(30) << "" << "___________________________________" << endl;
			cout << setw(30) << "" << "\t\t " << FullNumber() << endl;
			cout << setw(30) << "" << "\t " << _TicketTime << endl;
			cout << setw(30) << "" << "\tWaiting Clients =  " << _WaitingClients << endl;
			cout << setw(30) << "" << "\tServe Time in " << ExpectedServeTime() << " Minutes" << endl;

			cout << left << setw(30) << "" << "___________________________________" << endl;
		}
	};

public:
	queue <clsTicket> QueueLine;
	clsQueueLine(string Prefix, short AverageSeveTime)
	{
		_Prefix = Prefix;
		_AverageServeTime = AverageSeveTime;
		_TotalTickets = 0;
	}
	void IssueTicket()
	{
		_TotalTickets++;
		clsTicket Ticket(_Prefix, _TotalTickets, WaitingClients(), _AverageServeTime);
		QueueLine.push(Ticket);
	}
	short WaitingClients()
	{
		return QueueLine.size();
	}
	short ServedClient()
	{
		return _TotalTickets - WaitingClients();
	}
	void PrintInfo()
	{
		cout << left << setw(30) << "" << "___________________________________" << endl;
		cout << setw(30) << "" << "\t\tQueue Info\n";
		cout << setw(30) << "" << "___________________________________" << endl;
		cout << setw(30) << "" << "\tPrefix        = " << _Prefix << endl;
		cout << setw(30) << "" << "\tTotal Tickets = " << _TotalTickets << endl;
		cout << setw(30) << "" << "\tServerd Clients = " << ServedClient() << endl;
		cout << setw(30) << "" << "\tWaiting Clients = " << WaitingClients() << endl;
		cout << setw(30) << "" << "___________________________________" << endl;
	}
	bool ServeNextClient()
	{
		if (QueueLine.empty()) return false;
		QueueLine.pop();
		return true;
	}
	string WhoIsNext()
	{
		if (QueueLine.empty()) return "No Client Left";
		
		else
			return QueueLine.front().FullNumber();
	}
	void PrintTicketsLineRTL()
	{
		
		if (QueueLine.empty())
		{
			cout << setw(30) << "" << "\t\tNo Tickets\n";
			return;
		}
		else
			cout<< "\n\n" << setw(30) << "" << "\tTickets: ";
		queue <clsTicket> TemQueueLine = QueueLine;
		while (!TemQueueLine.empty())
		{
			cout << TemQueueLine.front().FullNumber() << " <--";
			TemQueueLine.pop();
		}
		cout << endl;
	}
	void PrintTicketsLineLTR()
	{
		
		if (QueueLine.empty())
		{
			cout << setw(30) << "" << "\t\tNo Tickets\n";
			return;
		}
		else
			cout << "\n" << setw(30) << "" << "\tTickets: ";

		queue <clsTicket> TemQueueLine = QueueLine;
		stack <clsTicket> TemStackLine;
		while (!TemQueueLine.empty())
		{
			TemStackLine.push(TemQueueLine.front());
			TemQueueLine.pop();
		}
		while (!TemStackLine.empty())
		{
			clsTicket Ticket = TemStackLine.top();
			cout << Ticket.FullNumber() << " --> ";
			TemStackLine.pop();
		}
		cout << "\n";
	}
	void PrintAllTickets()
	{
		queue <clsTicket> TemQueueLine = QueueLine;
		while (!TemQueueLine.empty())
		{
			TemQueueLine.front().Print();
			TemQueueLine.pop();
		}
	}
};

