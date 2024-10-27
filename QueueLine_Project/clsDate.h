#pragma once
#pragma warning (disable : 4996)

#include <iostream>
#include <ctime>
#include <string>
#include <vector>

using namespace std;


class clsDate
{

	short _Day, _Month, _Year;
public:

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}
	clsDate(string DataString)
	{
		vector <string>vString = Split(DataString, "/");
		_Day = stoi(vString[0]);
		_Month = stoi(vString[1]);
		_Year = stoi(vString[2]);
	}
	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clsDate(short TotalDays, short Year)
	{
		clsDate GetDate = GetDateFromDayOrderInYear(TotalDays, Year);
		_Day = GetDate.Day;
		_Month = GetDate.Month;
		_Year = GetDate.Year;
	}
	void Print()
	{
		cout << DateToString() << endl;
	}

	void SetDay(short Day)
	{
		_Day = Day;
	}
	short GetDay()
	{
		return _Day;
	}
	_declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month)
	{
		_Month = Month;
	}
	short GetMonth()
	{
		return _Month;
	}
	_declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year)
	{
		_Year = Year;
	}
	short GetYear()
	{
		return _Year;
	}
	_declspec(property(get = GetYear, put = SetYear)) short Year;



	static string DateToString(clsDate Date)
	{
		return (to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year));
	}
	string DateToString()
	{
		return DateToString(*this);
	}
	static clsDate StringToDate(string DateString)
	{
		clsDate Date;
		vector <string>vDate = Split(DateString, "/");
		Date.Day = stoi(vDate[0]);
		Date.Month = stoi(vDate[1]);
		Date.Year = stoi(vDate[2]);
		return Date;

	}
	static vector <string>Split(string S1, string delim)
	{
		string Word = "";
		short pos = 0;
		vector<string>vString;
		while ((pos = S1.find(delim)) != std::string::npos)
		{
			Word = S1.substr(0, pos);
			if (Word != "")
				vString.push_back(Word);

			S1.erase(0, pos + delim.length());
		}
		if (S1 != "")
			vString.push_back(S1);

		return vString;
	}
	static bool IsLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}
	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}
	static short NumberOfDaysInMonth(short Month, short Year)
	{
		if (Month < 1 || Month > 12)
			return 0;
		short Days[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : Days[Month - 1];
	}
	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(_Month, _Year);
	}

	static short TotalDaysFromTheBeginningOfTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;
		for (short i = 1; i < Month; i++)
			TotalDays += NumberOfDaysInMonth(i, Year);
		TotalDays += Day;
		return TotalDays;
	}
	short TotalDaysFromTheBeginningOfTheYear()
	{
		return TotalDaysFromTheBeginningOfTheYear(_Day, _Month, _Year);
	}
	static clsDate GetDateFromDayOrderInYear(short TotalDays, short Year)
	{
		clsDate Date;
		short RemainingDays = TotalDays;
		Date.Year = Year;
		Date.Month = 1;
		while (true)
		{
			short MonthDays = NumberOfDaysInMonth(Date.Month, Date.Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;

	}
	clsDate GetDateFromDayOrderInYear(short TotalDays)
	{
		return GetDateFromDayOrderInYear(TotalDays, _Year);
	}
	static short DayOfWeekOrder(short Month, short Year, short Day)
	{
		short a = (14 - Month) / 12;
		short Y = Year - a;
		short m = Month + 12 * a - 2;
		short E = (Day + Y) + (Y / 4) - (Y / 100) + (Y / 400) + ((31 * m) / 12);
		short d = (E % 7);
		return d;
	}
	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Month, _Year, _Day);
	}
	static string DayOfWeekName(short DayOfOrder)
	{
		string arrDayOrder[7] = { "Sanday","Monday", "Tuesday","Wednesday","Thusday","Friday","Saturday" };
		return arrDayOrder[DayOfOrder];
	}
	static string DayOfWeekName(short Month, short Year, short Day)
	{
		string arrDayOrder[7] = { "Sanday","Monday", "Tuesday","Wednesday","Thusday","Friday","Saturday" };
		return arrDayOrder[DayOfWeekOrder(Month, Year, Day)];
	}
	string DayOfWeekName()
	{
		return DayOfWeekName(Day, Month, Year);
	}
	static string MonthShortName(short MonthNumber)
	{
		string arrMonthName[12] = { "Jan", "Feb","Mar", "Apr", "May", "Jun",
								  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec", };

		return arrMonthName[MonthNumber - 1];
	}
	string MonthShortName()
	{
		return MonthShortName(_Month);
	}
	static void PrintMonthCalender(short Month, short Year)
	{
		short current = DayOfWeekOrder(1, Month, Year);
		short NumberOfDays = NumberOfDaysInMonth(Month, Year);
		printf("\n----------------%s----------------\n", MonthShortName(Month).c_str());
		printf("  San Mon Tue Wed Thu Fri Sat\n");
		short i;
		for (i = 0; i < current; i++)
			printf("     ");
		for (short j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);
			if (++i == 7)
			{
				i = 0;
				cout << endl;
			}
		}


		printf("\n-----------------------------------\n");
	}
	void PrintMonthCalender()
	{
		PrintMonthCalender(_Month, _Year);
	}
	static void PrintYearCalender(short Year)
	{
		cout << "\n_____________________________________\n";
		cout << "\n\tCalender - " << Year << endl;
		cout << "_____________________________________\n";

		for (short i = 1; i <= 12; i++)
		{
			PrintMonthCalender(i, Year);

		}

	}
	void PrintYearCalender()
	{
		PrintYearCalender(_Year);
	}
	/*static clsDate GetDateAfterAddingDays(short Days, clsDate Date)
	{

		short RemainingDays =  Days + TotalDaysFromTheBeginningOfTheYear(Date.Day, Date.Month, Date.Year);
		Date.Month = 1;
		while (true)
		{
			short DaysInMonth = NumberOfDaysInMonth(Date.Month, Date.Year);
			if (RemainingDays > DaysInMonth)
			{
				RemainingDays -= DaysInMonth;
				Date.Month++;
				if (Date.Month > 12)
				{
					Date.Month = 1;
					Date.Year++;
				}
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}*/
	/*void GetDateAfterAddingDays(short Days)
	{
		GetDateAfterAddingDays(Days, *this);
	}*/
	void AddDays(short Days)
	{
		short RemainingDays = Days + TotalDaysFromTheBeginningOfTheYear(_Day, _Month, _Year);
		_Month = 1;
		while (true)
		{
			short DaysInMonth = NumberOfDaysInMonth(_Month, _Year);
			if (RemainingDays > DaysInMonth)
			{
				RemainingDays -= DaysInMonth;
				_Month++;
				if (_Month > 12)
				{
					_Month = 1;
					_Year++;
				}
			}
			else
			{
				_Day = RemainingDays;
				break;
			}
		}

	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month) ? true : ((Date1.Month == Date2.Month) ? (Date1.Day < Date2.Day) : false) : false);
	}
	bool IsDate1BeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}
	static bool IsDateEquals(clsDate Date1, clsDate Date2)
	{
		return   (Date1.Year == Date2.Year) ? ((Date1.Month == Date1.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
	}
	bool IsDateEquals(clsDate Date2)
	{
		return IsDateEquals(*this, Date2);
	}
	static bool IsLastDayInMonth(clsDate Date)
	{
		return Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year);
	}
	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}
	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}
	static clsDate IncreaseDateByOneDay(clsDate& Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Day = 1;
				Date.Month = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
			Date.Day++;
		return Date;
	}
	void IncreaseDateByOneDay()
	{
		IncreaseDateByOneDay(*this);
	}
	static void SwapDate(clsDate& Date1, clsDate& Date2)
	{
		clsDate tempDate;
		tempDate.Day = Date1.Day;
		tempDate.Month = Date1.Month;
		tempDate.Year = Date1.Year;

		Date1.Day = Date2.Day;
		Date1.Month = Date2.Month;
		Date1.Year = Date2.Year;

		Date2.Day = tempDate.Day;
		Date2.Month = tempDate.Month;
		Date2.Year = tempDate.Year;

	}
	static short GetDifferenceInDays(clsDate Date1, clsDate Date2, bool includedEndDay = false)
	{
		short Days = 0, SwapFlagValue = 1;
		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDate(Date1, Date2);
			SwapFlagValue = -1;
		}
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}
		return includedEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
	}
	short GetDifferenceInDays(clsDate Date2, bool includedEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, includedEndDay);
	}
	static short CalculateMyAgeInDays(clsDate DateOfBrith)
	{
		return GetDifferenceInDays(DateOfBrith, GetSystemDate(), true);
	}
	static clsDate GetSystemDate()
	{
		short Day, Month, Year;
		time_t t = time(0);
		tm* now = gmtime(&t);
		Day = now->tm_mday;
		Month = now->tm_mon + 1;
		Year = now->tm_year + 1900;
		return clsDate(to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year));
	}
	static string GetSystemDateTimeString()
	{
		short Day, Month, Year, Hour, Minute, Second;
		time_t t = time(0);
		//tm* now = gmtime(&t);
		tm* now = localtime(&t);
		Day = now->tm_mday;
		Month = now->tm_mon + 1;
		Year = now->tm_year + 1900;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second));
	}
	static short ReadNumber(string Message)
	{
		short Number = 0;
		cout << Message;
		cin >> Number;
		return Number;
	}
	static clsDate ReadFullDate()
	{
		clsDate Date;
		Date.Day = ReadNumber("Please enter a day ? ");
		Date.Month = ReadNumber("Please enter a month ? ");
		Date.Year = ReadNumber("Please enter a year ? ");
		return Date;
	}
	static clsDate DecreaseDateByOneDay(clsDate& Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Day = 31;
				Date.Month = 12;
				Date.Year--;
			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
			}
		}
		else
			Date.Day--;
		return Date;
	}
	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}
	static clsDate DecreaseDateByXDays(clsDate Date, short& Days)
	{
		for (short i = 1; i <= Days; i++)
			Date = DecreaseDateByOneDay(Date);

		return Date;
	}
	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(*this, Days);
	}
	static clsDate DecreaseDateByOneWeek(clsDate& Date)
	{
		for (short i = 1; i <= 7; i++)
			Date = DecreaseDateByOneDay(Date);

		return Date;
	}
	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}
	static clsDate DecreaseDateByXWeeks(clsDate Date, short& Weeks)
	{
		for (short i = 1; i <= Weeks; i++)
			Date = DecreaseDateByOneWeek(Date);

		return Date;
	}
	void  DecreaseDateByXWeeks(short Weeks)
	{
		DecreaseDateByXWeeks(*this, Weeks);
	}
	static clsDate DecreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.Month == 1)
		{
			Date.Month == 12;
			Date.Year--;
		}
		Date.Month--;
		short NumberOfCurrentDays = NumberOfDaysInMonth(Date.Month, Date.Year);
		if (Date.Day > NumberOfCurrentDays)
			Date.Day = NumberOfCurrentDays;

		return Date;
	}
	void  DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}
	static clsDate DecreaseDateByXMonths(clsDate Date, short& Months)
	{
		for (short i = 1; i <= Months; i++)
			Date = DecreaseDateByOneMonth(Date);
		return Date;
	}
	void DecreaseDateByXMonths(short Months)
	{
		DecreaseDateByXMonths(*this, Months);
	}
	static clsDate DecreaseDateByOneYear(clsDate& Date)
	{
		Date.Year--;

		if (Date.Month == 2)
		{
			if (IsLeapYear(Date.Year))
			{
				Date.Day = 29;
			}
			else
				Date.Day = 28;
		}

		return Date;
	}
	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}
	static clsDate DecreaseDateByXYears(clsDate Date, short& Years)
	{

		for (short i = 1; i <= Years; i++)
		{
			Date = DecreaseDateByOneYear(Date);

		}


		return Date;
	}
	void DecreaseDateByXYears(short Years)
	{
		DecreaseDateByXYears(*this, Years);
	}

	static clsDate DecreaseDateByXYearsFaster(clsDate Date, short& Years)
	{
		Date.Year -= Years;
		return Date;
	}
	void DecreaseDateByXYearsFaster(short Years)
	{
		DecreaseDateByXYearsFaster(*this, Years);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date)
	{
		Date.Year -= 10;
		return Date;
	}
	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate Date, short& Decades)
	{
		for (short i = 1; i <= Decades * 10; i++)
			Date = DecreaseDateByOneYear(Date);
		return Date;
	}
	void DecreaseDateByXDecades(short Decades)
	{
		DecreaseDateByXDecades(*this, Decades);
	}
	static clsDate DecreaseDateByXDecadesFaster(clsDate Date, short& Decades)
	{
		Date.Year -= Decades * 10;
		return Date;
	}
	void DecreaseDateByXDecadesFaster(short Decades)
	{
		DecreaseDateByXDecadesFaster(*this, Decades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year -= 100;
		return Date;
	}
	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}
	static clsDate DecreaseDateByMillennium(clsDate& Date)
	{
		Date.Year -= 1000;
		return Date;
	}
	void DecreaseDateByMillennium()
	{
		DecreaseDateByMillennium(*this);
	}
	static short DayOfWeekOrder(clsDate Date)
	{
		return DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
	}
	static string ShortDaysName(short DayOfOrder)
	{
		string DaysName[] = { "San", "Mon", "Tue", "Wed", "Thi", "Fri", "Sat" };
		return DaysName[DayOfOrder];
	}
	static bool IsEndOfWeek(clsDate Date)
	{
		return  DayOfWeekOrder(Date) == 6;
	}
	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}
	static bool IsWeekEnd(clsDate Date)
	{
		short IndexDay = DayOfWeekOrder(Date);
		return IndexDay == 6 || IndexDay == 0;
	}
	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}
	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekEnd(Date);
		/*short IndexDay = DayOfWeekOrder(Date);
		return (IndexDay >= 1 && IndexDay <= 5);*/
	}
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}
	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date);
	}
	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}
	static short DaysUntilTheEndOfMonth(clsDate Date)
	{
		clsDate EndOfMonthDate;
		EndOfMonthDate.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
		EndOfMonthDate.Month = Date.Month;
		EndOfMonthDate.Year = Date.Year;
		return GetDifferenceInDays(Date, EndOfMonthDate, true);
	}
	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}
	static short DaysUntilTheEndOfYear(clsDate Date)
	{
		clsDate EndOfYearDate;
		EndOfYearDate.Day = 31;
		EndOfYearDate.Month = 12;
		EndOfYearDate.Year = Date.Year;
		return GetDifferenceInDays(Date, EndOfYearDate, true);
	}
	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}
	static short CalculateBussinessDays(clsDate Date1, clsDate Date2)
	{
		short VaccationDays = 0;
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			if (IsBusinessDay(Date1))
				VaccationDays++;

			Date1 = IncreaseDateByOneDay(Date1);
		}
		return VaccationDays;
	}
	short CalculateBussinessDays(clsDate Date2)
	{
		return CalculateBussinessDays(*this, Date2);
	}
	static short ActuelVaccationDays(clsDate Date1, clsDate Date2)
	{
		/*short VaccationDays = 0;
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			if (IsBusinessDay(Date1))
				VaccationDays++;

			Date1 = IncreaseDateByOneDay(Date1);
		}
		return VaccationDays;*/
		return CalculateBussinessDays(Date1, Date2);
	}
	short ActuelVaccationDays(clsDate Date2)
	{
		return ActuelVaccationDays(*this, Date2);
	}
	static clsDate CalculataVacationReturnDate(clsDate DateFrom, short VacationDays)
	{
		short WeekendCounter = 0;

		while (IsWeekEnd(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}
		for (short i = 1; i <= VacationDays + WeekendCounter; i++)
		{
			if (IsWeekEnd(DateFrom))
				WeekendCounter++;
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}
		while (IsWeekEnd(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}
		return DateFrom;
	}
	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2)) && (!IsDateEquals(Date1, Date2));
	}
	bool IsDate1AfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}
	enum enCompareDate { After = 1, Equal = 0, Before = -1 };
	static enCompareDate CompareDate(clsDate Date1, clsDate Date2)
	{
		/*if (IsDate1BeforeDate2(Date1, Date2))
		{
			return enCompareDate::Before;
		}
		if (IsDate1EqualDate2(Date1, Date2))
			return enCompareDate::Equal;
		return enCompareDate::After;*/
		return IsDate1BeforeDate2(Date1, Date2) ? enCompareDate::Before : (IsDateEquals(Date1, Date2) ? enCompareDate::Equal : enCompareDate::After);
	}
	enCompareDate CompareDate(clsDate Date2)
	{
		return CompareDate(*this, Date2);
	}
	static bool IsValidDate(clsDate Date)
	{
		short DaysInMonth = NumberOfDaysInMonth(Date.Month, Date.Year);
		//return (Date.Day >= 1 && Date.Day <= DaysInMonth && Date.Month <= 12);
		if (Date.Day < 1 || Date.Day > 31)
			return false;
		if (Date.Month < 1 || Date.Month > 12)
			return false;
		if (Date.Month == 2)
		{
			if (IsLeapYear(Date.Year))
			{
				if (Date.Day > 29)
					return false;
			}
			else if (Date.Day > 28)
				return false;
		}
		if (Date.Day > DaysInMonth)
			return false;
		return true;

	}
	bool IsValidDate()
	{
		return IsValidDate(*this);
	}
	static string ReplaceWordInString(string S1, string StringToReplace, string sReplaceTo)
	{
		short pos = S1.find(StringToReplace);
		while (pos != std::string::npos)
		{
			S1 = S1.replace(pos, StringToReplace.length(), sReplaceTo);
			pos = S1.find(StringToReplace);
		}
		return S1;
	}
	static string FormatDate(clsDate Date, string DateFormat = "dd/mm/yy")
	{
		string FormattedDate = ReplaceWordInString(DateFormat, "dd", to_string(Date.Day));
		FormattedDate = ReplaceWordInString(FormattedDate, "mm", to_string(Date.Month));
		FormattedDate = ReplaceWordInString(FormattedDate, "yy", to_string(Date.Year));
		return FormattedDate;

	}
	static clsDate IncreaseDateByXDays(clsDate Date, short& Days)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByXDays(short Days)
	{
		IncreaseDateByXDays(*this, Days);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate Date, short& Weeks)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void IncreaseDateByXWeeks(short Weeks)
	{
		IncreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.Month == 12)
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
			Date.Month++;
		short NubmerOfCurrentDays = NumberOfDaysInMonth(Date.Month, Date.Year);
		if (Date.Day > NubmerOfCurrentDays)
			Date.Day = NubmerOfCurrentDays;
		return Date;

	}
	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}
	static clsDate IncreaseDateByXMonths(clsDate Date, short& Months)
	{
		for (short i = 1; i <= Months; i++)
			Date = IncreaseDateByOneMonth(Date);
		return Date;
	}
	void IncreaseDateByXMonths(short Months)
	{
		IncreaseDateByXMonths(*this, Months);
	}
	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		Date.Year++;
		return Date;
	}
	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}
	static clsDate IncreaseDateByXYears(clsDate Date, short& Years)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}
	void IncreaseDateByXYears(short Years)
	{
		IncreaseDateByXYears(*this, Years);
	}
	static clsDate IncreaseDateByXYearsFaster(clsDate Date, short& Years)
	{
		Date.Year += Years;
		return Date;
	}

	void IncreaseDateByXYearsFaster(short& Years)
	{
		IncreaseDateByXYearsFaster(*this, Years);
	}
	static clsDate IncreaseDateByOneDecade(clsDate& Date)
	{
		Date.Year += 10;
		return Date;
	}
	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}
	static clsDate IncreaseDateByXDecades(clsDate Date, short& Decades)
	{
		for (short i = 1; i <= Decades; i++)
			Date = IncreaseDateByOneDecade(Date);
		return Date;
	}
	void IncreaseDateByXDecades(short Decades)
	{
		IncreaseDateByXDecades(*this, Decades);
	}
	static clsDate IncreaseDateByXDecadesFaster(clsDate Date, short& Decades)
	{
		Date.Year += Decades * 10;
		return Date;
	}
	void IncreaseDateByXDecadesFaster(short Decades)
	{
		IncreaseDateByXDecadesFaster(*this, Decades);
	}
	static clsDate IncreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year += 100;
		return Date;
	}
	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}
	static clsDate IncreaseDateByMillenium(clsDate& Date)
	{
		Date.Year += 1000;
		return Date;
	}
	void IncreaseDateByMillenium()
	{
		IncreaseDateByMillenium(*this);
	}
	static short NumberOfDaysInYear(short Year)
	{
		return IsLeapYear(Year) ? 366 : 365;
	}

	short NumberOfDaysInYear()
	{
		return NumberOfDaysInYear(_Year);
	}
	static short NumberOfHoursInYear(short Year)
	{
		return NumberOfDaysInYear(Year) * 24;
	}
	short NumberOfHoursInYear()
	{
		return NumberOfHoursInYear(_Year);
	}
	static int NumberOfMinutesInYear(short Year)
	{
		return NumberOfHoursInYear(Year) * 60;
	}
	int NumberOfMinutesInYear()
	{
		return NumberOfMinutesInYear(_Year);
	}
	static int NumberOfSecondsInYear(short Year)
	{
		return NumberOfMinutesInYear(Year) * 60;
	}
	int NumberOfSecondsInYear()
	{
		return NumberOfSecondsInYear(_Year);
	}




};

class clsPeriod
{

public:
	clsDate StartDate;
	clsDate EndDate;
	clsPeriod(clsDate StartDate, clsDate EndDate)
	{
		this->StartDate = StartDate;
		this->EndDate = EndDate;
	}
	static bool IsOverlapPeriods(clsPeriod Period1, clsPeriod Period2)
	{

		if (
			clsDate::CompareDate(Period2.EndDate, Period1.StartDate) == clsDate::Before
			||
			clsDate::CompareDate(Period2.StartDate, Period1.EndDate) == clsDate::After
			)
			return false;
		else
			return true;

	}
	bool IsOverLapWith(clsPeriod Period2)
	{
		return IsOverlapPeriods(*this, Period2);
	}

	static short CalculatePeriodLength(clsPeriod Period, bool IncludedEndDate = false)
	{
		return clsDate::GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludedEndDate);
	}
	static bool IsDateInPeriod(clsPeriod Period, clsDate Date)
	{
		//return CompareDate(Period.StartDate, Date)   == Before && CompareDate(Period.EndDate, Date) == After;
		//return (CompareDate(Date, Period.StartDate)  == After && CompareDate(Date, Period.EndDate) == Before);
		//return !(CompareDate(Date, Period.StartDate) == Before && CompareDate(Date, Period.EndDate) == After);
		return !(clsDate::CompareDate(Date, Period.StartDate) == clsDate::Before && clsDate::CompareDate(Date, Period.EndDate) == clsDate::After);

	}
	bool IsDateInPeriod(clsDate Date)
	{
		return IsDateInPeriod(*this, Date);
	}
	static short CountOverLapDays(clsPeriod Period1, clsPeriod Period2)
	{
		int Period1Length = CalculatePeriodLength(Period1, true);
		int Period2Length = CalculatePeriodLength(Period1, true);
		int OverLapCounter = 0;
		if (!clsPeriod::IsOverlapPeriods(Period1, Period2))
			return 0;
		if (Period1Length < Period2Length)
		{
			while (clsDate::IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
			{
				if (IsOverlapPeriods(Period1, Period2))
				{
					OverLapCounter++;
				}
				Period1.StartDate = clsDate::IncreaseDateByOneDay(Period1.StartDate);
			}
		}
		else
		{
			while (clsDate::IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate))
			{
				if (IsOverlapPeriods(Period2, Period1))
				{
					OverLapCounter++;
				}
				Period2.StartDate = clsDate::IncreaseDateByOneDay(Period2.StartDate);
			}
		}
		return OverLapCounter;

	}
	short CountOverLapDays(clsPeriod Period2)
	{
		return CountOverLapDays(*this, Period2);
	}
	void Print()
	{
		cout << "Period Start: ";
		StartDate.Print();


		cout << "Period End: ";
		EndDate.Print();


	}


};
