/*
* For compilation: g++ -o pthread3.out pthread3.cpp -lpthread
*/

#include <iostream>
#include <pthread.h>
#include <array>
#include <list>
using namespace std;
list<int> firm1;
list<int> firm2;
list<int> firm3;
int seats[2][50];
int turn = 0;
int capacity = 100;
bool isFull = false;
void *registerseat(void *turnnumber)
{
	int* check = (int*)turnnumber;
	while (true)
	{
		
		while (turn != *check);
		cout << "firm " << *check + 1 << " entered shared area" << endl;
		if (capacity == 0)
		{
			if (!isFull)
			{
				cout << "All seats are filled" << endl;
				isFull = true;
			}
			
			turn = (turn + 1) % 3;
			break;
		}
		int randomseat = rand() % 100 ;
		int location = randomseat / 2;
		int location2 = randomseat % 2;
		if (seats[location2][location] == 0)
		{
			seats[location2][location] = *check + 1;
			cout << "The Seat " << "[" << location2 << "]" << " [" << location << "] " << "is reserved by agency " << *check + 1 << endl;
			capacity--;
			if (*check == 0)
			{
				firm1.push_back(randomseat);
			}
			if (*check == 1)
			{
				firm2.push_back(randomseat);
			}
			if (*check == 2)
			{
				firm3.push_back(randomseat);
			}
		}
		cout << "firm " << *check + 1 << " left shared area" << endl;
		turn = (turn + 1) % 3;
		
	}

}



int main()
{
	int id = 0;
	int id2 = 1;
	int id3 = 2;
	pthread_t thread1, thread2, thread3;
	pthread_create(&thread1, NULL, registerseat, (void*)& id);
	pthread_create(&thread2, NULL, registerseat, (void*)& id2);
	pthread_create(&thread3, NULL, registerseat, (void*)& id3);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 50; k++)
		{
			cout << seats[i][k] << " ";
		}
		cout << endl;
		cout << endl;
		
	}
	firm1.sort();
	firm2.sort();
	firm3.sort();
	for (auto v : firm1)
		cout <<"Seat Number "<< v + 1 << ", ";
	cout  << "are reserved by firm1" << endl;
	cout << endl;
	for (auto v : firm2)
		cout <<  "Seat Number " << v + 1 << ", ";
	cout << "are reserved by firm2" << endl;
	cout << endl;
	for (auto v : firm3)
		cout <<  "Seat Number " << v + 1 << ", ";
	cout << "are reserved by firm3" << endl;
	cout << endl;
	return 0;

}