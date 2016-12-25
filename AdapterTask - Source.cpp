#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

#include "Strategy.h"

using namespace std;

void main()
{
	ifstream cargo("cargo.txt");
	queue<Cargo*> cargoQueue;
	while (!cargo.eof())
	{
		bool type;
		int weight;
		cargo >> type >> weight;
		if (type)
		{
			cargoQueue.push(new Barrel(weight));
		}
		else
		{
			cargoQueue.push(new Container(weight));
		}
	}
	CarBarrel cb(0,100);
	CarContainer cc(0,100);
	while (!cargoQueue.empty())
	{
		cout << "Operate cargo:\t";
		bool barrel = true;
		if (dynamic_cast<Barrel*>(cargoQueue.front()))
		{
			cout << "Container";
			barrel = false;
		}
		else
		{
			cout << "Barrel";
		}
		cout << "\tweight: " << cargoQueue.front()->weight() << endl;
		if (!barrel)
		{
			bool result = cb.isFull(cargoQueue.front()->weight());
			if (result)
			{
				cout << "CarBarrel is full. Push it away";
				cb = CarBarrel(0, 200);
			}
			else
			{
				cargoQueue.front()->load(&cb);
				cout << "Loaded. Car weight: " << cb.weight() << "/" << 100 << endl;
				cargoQueue.pop();
			}
		}
		else
		{
			bool result = cc.isFull(cargoQueue.front()->weight());
			if (result)
			{
				cout << "CarContainer is full. Push it away";
				cc = CarContainer(0, 200);
			}
			else
			{
				cargoQueue.front()->load(&cc);
				cout << "Loaded. Car weight: " << cc.weight() << "/" << 100 << endl;
				cargoQueue.pop();
			}
		}
		cout << endl;
	}
	system("pause");
}