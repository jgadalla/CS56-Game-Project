	#include "crashDetector.hpp"
	

	crashDetector::crashDetector():first_(NULL) {

	}

	crashDetector::~crashDetector(){
		Tab* temp = first_;	
		while(first_ ->next_!= NULL){
			deleteUnit(first_->next_);
		}
		delete first_;
	}

	void crashDetector::addUnit(Unit* car)
	{
			Tab* temp = first_;	
			first_ = new Tab();
			first_->item_ = car;
			first_->next_ = temp;
		
	}

	void crashDetector::deleteUnit(Tab* pointer) 
	{
		if (pointer != NULL)
		{
			if(pointer->next_ != NULL)
			{
				Tab* temp = pointer;
				pointer = pointer->next_;
				delete temp;
			}
			else
			{
				delete pointer;
			}
		}
	}
	
	void crashDetector::collision()
	{
		//need double while loop..
		Tab* unit = first_;
		while(unit != NULL){

			Tab* temp = unit->next_;
			while(temp != NULL){
				int tempX = temp->item_->GetX();
				int tempY = temp->item_->GetY();
				int firstX = first_->item_->GetX();
				int firstY = first_->item_->GetY();
				int boundX = first_->item_->GetWidth()/2;
				int boundY = first_->item_->GetHeight()/2;
				if(firstX < tempX + boundX && firstX > tempX - boundX){
					if(firstY < tempY + boundY && firstY > tempY + boundY){
						first_->item_-> crashed();
						temp->item_->crashed();
						deleteUnit(unit);
						deleteUnit(temp);

					}
				}
				temp = temp->next_;
			}
			unit = unit->next_;
		}

	}