#pragma once

class CarBarrel;
class CarContainer;

class Cargo
{
public:
	Cargo(int weight) : weight_(weight) {}
	virtual bool load(CarBarrel*)const { throw "Error type"; }
	virtual bool load(CarContainer*)const { throw "Error type"; }
	int weight()const { return weight_; }
protected:
	int weight_;
};

class Car
{
public:
	Car(int weight, int max) : weight_(weight) 
	{
		maxWeight_ = max;
	}
	void load(int weight)
	{
		weight_ += weight;
	}
	bool isFull(int weight)
	{
		return (weight_ + weight) >= maxWeight_;
	}
	int weight()const { return weight_; }
private:
	int weight_;
	int maxWeight_;
};

class CarBarrel : public Car
{
public:
	CarBarrel(int weight, int max):
		Car(weight, max)
	{ }
};

class CarContainer : public Car
{
public:
	CarContainer(int weight, int max) :
		Car(weight, max)
	{
	}
};

class Container : public Cargo
{
public:
	Container(int weight) : Cargo(weight) {}
	bool load(CarContainer* car)const
	{
		if (car->isFull(weight_))
		{
			return false;
		}
		else
		{
			car->load(weight_);
		}
		return true;
	}
};

class Barrel : public Cargo
{
public:
	Barrel(int weight) : Cargo(weight) {}
	bool load(CarBarrel* car)const
	{
		if (car->isFull(weight_))
		{
			return false;
		}
		else
		{
			car->load(weight_);
		}
		return true;
	}
};

