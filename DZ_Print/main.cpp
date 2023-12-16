#define _CRT_SECURE_NO_DEPRECATE 
#include <iostream>
#include <queue>
#include <ctime>


using namespace std;

struct PrintRequest 
{
    string user;
    time_t timestamp;
};

class PrintQueue 
{
private:
    queue<PrintRequest> requestQueue;
    queue<PrintRequest> printLog;

public:
    void addRequest(const PrintRequest& request)
    {
        requestQueue.push(request);
    }

    void printNextRequest() 
    {
        if (requestQueue.empty())
        {
            cout << "No pending print requests." << endl;
            return;
        }

        PrintRequest request = requestQueue.front();
        requestQueue.pop();

        time_t now = time(0);
        request.timestamp = now;
        printLog.push(request);

        cout << "Printing request for user: " << request.user << " at: " << asctime(localtime(&now)) << endl;
    }

    void printStatistics() 
    {
        if (printLog.empty()) 
        {
            cout << "No print statistics available." << endl;
            return;
        }

        cout << "Print Statistics:" << endl;
        while (!printLog.empty()) {
            PrintRequest request = printLog.front();
            printLog.pop();

            cout << "User: " << request.user << ", Printed at: " << asctime(localtime(&request.timestamp));
        }
    }
};

int main() 
{
    PrintQueue printQueue;

    printQueue.addRequest({ "John Doe", 0 });
    printQueue.addRequest({ "Alice Smith", 0 });
    printQueue.addRequest({ "Bob Johnson", 0 });

    printQueue.printNextRequest();
    printQueue.printNextRequest();
    printQueue.printNextRequest();

    printQueue.printStatistics();

    return 0;
}