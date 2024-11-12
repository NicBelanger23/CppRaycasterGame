#pragma once
class valCollection
{
private:
	int* values;
	int size = 0;
public:
	valCollection(int size) {
		values = new int[size];
	}
	valCollection* add(int value) {
		values[size] = value;
		size++;
		return this;
	}

	bool contains(int value, bool defaultTrue) {
		if (defaultTrue && size <= 0) { return true; }
		for (int i = 0; i < size; i++) {
			if (value == values[i]) { return true; }
		}
		return false;
	}
};

