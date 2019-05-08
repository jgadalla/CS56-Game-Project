#pragma once;

#include "Unit.hpp"
class crashDetector{
	private:
		struct Tab{
			Unit* item_;
			Tab* next_;
		};

		Tab* first_;
	public:
		crashDetector();
		~crashDetector();
		void addUnit(Unit* car);
		void deleteUnit(Tab* pointer);
		void collision();
		void free();
};