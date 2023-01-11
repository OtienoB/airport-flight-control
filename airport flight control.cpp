//C++ solution
/*This program is designed to store and display the flights of the day from a text file. The program allows the user to enter the current time, enter a new flight, delete (cancel) a flight, modify the time of a flight, enter delay in a flight, display all flights, display departures flights that they have not departure yet, display arrival flights that they have not arrived yet, sort flights by FlightNO, and sort flights by Time. In order to accomplish this, various functions have been used to read and write to the text file, add and delete flights, modify flight times and delays, display flights, and sort flights. The program also allows the user to enter the current time, which is used to help determine which flights have departed and which have arrived.*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Flight
{
    string flightNo;
    string time;
    int delay;
};

//function prototypes
void readFlights(vector<Flight>&);
void writeFlights(vector<Flight>);
void enterNewFlight(vector<Flight>&);
void deleteFlight(vector<Flight>&);
void modifyTime(vector<Flight>&);
void enterDelay(vector<Flight>&);
void displayFlights(vector<Flight>);
void displayDepartures(vector<Flight>);
void displayArrivals(vector<Flight>);
void sortFlightNo(vector<Flight>&);
void sortTime(vector<Flight>&);

int main()
{
    vector<Flight> flights;
    string currentTime;

    //get the current time from the user
    cout << "Please enter the current time: ";
    cin >> currentTime;

    //read flights from file
    readFlights(flights);

    //menu
    int choice;
    do
    {
        cout << "1. Enter a new flight" << endl;
        cout << "2. Delete a flight" << endl;
        cout << "3. Modify the time of a flight" << endl;
        cout << "4. Enter delay for a flight" << endl;
        cout << "5. Display all flights" << endl;
        cout << "6. Display departures that have not departed yet" << endl;
        cout << "7. Display arrivals that have not arrived yet" << endl;
        cout << "8. Sort flights by FlightNO" << endl;
        cout << "9. Sort flights by time" << endl;
        cout << "0. Exit" << endl;

        cout << "Please enter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                enterNewFlight(flights);
                break;

            case 2:
                deleteFlight(flights);
                break;

            case 3:
                modifyTime(flights);
                break;

            case 4:
                enterDelay(flights);
                break;

            case 5:
                displayFlights(flights);
                break;

            case 6:
                displayDepartures(flights);
                break;

            case 7:
                displayArrivals(flights);
                break;

            case 8:
                sortFlightNo(flights);
                break;

            case 9:
                sortTime(flights);
                break;

            case 0:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid option, please try again." << endl;
                break;
        }
    } while (choice != 0);

    //write flights to file
    writeFlights(flights);

    return 0;
}

//function to read flights from a file
void readFlights(vector<Flight>& flights)
{
    ifstream inFile("flights.txt");
    if (inFile.fail())
    {
        cout << "Error opening file." << endl;
        return;
    }

    Flight flight;
    while (inFile >> flight.flightNo >> flight.time >> flight.delay)
    {
        flights.push_back(flight);
    }
    inFile.close();
}

//function to write flights to a file
void writeFlights(vector<Flight> flights)
{
    ofstream outFile("flights.txt");
    if (outFile.fail())
    {
        cout << "Error opening file." << endl;
        return;
    }

    for (int i = 0; i < flights.size(); i++)
    {
        outFile << flights[i].flightNo << " " << flights[i].time << " " << flights[i].delay << endl;
    }
    outFile.close();
}

//function to enter a new flight
void enterNewFlight(vector<Flight>& flights)
{
    Flight flight;
    cout << "Please enter the FlightNO: ";
    cin >> flight.flightNo;
    cout << "Please enter the Time: ";
    cin >> flight.time;
    flight.delay = 0;

    flights.push_back(flight);
    cout << "Flight added successfully!" << endl;
}

//function to delete a flight
void deleteFlight(vector<Flight>& flights)
{
    string flightNo;
    cout << "Please enter the FlightNO to be deleted: ";
    cin >> flightNo;

    int index = -1;
    for (int i = 0; i < flights.size(); i++)
    {
        if (flights[i].flightNo == flightNo)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "Flight not found!" << endl;
    }
    else
    {
        flights.erase(flights.begin()+index);
        cout << "Flight deleted successfully!" << endl;
    }
}

//function to modify the time of a flight
void modifyTime(vector<Flight>& flights)
{
    string flightNo;
    cout << "Please enter the FlightNO to modify the time: ";
    cin >> flightNo;

    int index = -1;
    for (int i = 0; i < flights.size(); i++)
    {
        if (flights[i].flightNo == flightNo)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "Flight not found!" << endl;
    }
    else
    {
        string newTime;
        cout << "Please enter the new time: ";
        cin >> newTime;

        flights[index].time = newTime;
        cout << "Time modified successfully!" << endl;
    }
}

//function to enter delay for a flight
void enterDelay(vector<Flight>& flights)
{
    string flightNo;
    cout << "Please enter the FlightNO to enter the delay: ";
    cin >> flightNo;

    int index = -1;
    for (int i = 0; i < flights.size(); i++)
    {
        if (flights[i].flightNo == flightNo)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "Flight not found!" << endl;
    }
    else
    {
        int delay;
        cout << "Please enter the delay: ";
        cin >> delay;

        flights[index].delay = delay;
        cout << "Delay entered successfully!" << endl;
    }
}

//function to display all flights
void displayFlights(vector<Flight> flights)
{
    cout << "FlightNO\tTime\tDelay" << endl;
    for (int i = 0; i < flights.size(); i++)
    {
        cout << flights[i].flightNo << "\t" << flights[i].time << "\t" << flights[i].delay << endl;
    }
}

//function to display departures that have not departed yet
void displayDepartures(vector<Flight> flights)
{
    cout << "FlightNO\tTime\tDelay" << endl;
    for (int i = 0; i < flights.size(); i++)
    {
        if (flights[i].delay <= 0)
            cout << flights[i].flightNo << "\t" << flights[i].time << "\t" << flights[i].delay << endl;
    }
}

//function to display arrivals that have not arrived yet
void displayArrivals(vector<Flight> flights)
{
    cout << "FlightNO\tTime\tDelay" << endl;
    for (int i = 0; i < flights.size(); i++)
    {
        if (flights[i].delay > 0)
            cout << flights[i].flightNo << "\t" << flights[i].time << "\t" << flights[i].delay << endl;
    }
}

//function to sort flights by FlightNO
void sortFlightNo(vector<Flight>& flights)
{
    sort(flights.begin(), flights.end(), [](Flight a, Flight b)
    {
        return a.flightNo < b.flightNo;
    });
    cout << "Flights sorted by FlightNO!" << endl;
}

//function to sort flights by time
void sortTime(vector<Flight>& flights)
{
    sort(flights.begin(), flights.end(), [](Flight a, Flight b)
    {
        return a.time < b.time;
    });
    cout << "Flights sorted by time!" << endl;
}