#pragma once
#include <list>
namespace geek {
	class ObserverContext {
	public:
		virtual ~ObserverContext() {}
	};
	class ManagerObserverContext :public ObserverContext {
	public:
		ManagerObserverContext(int c = 0, int d = 0, int u = 0, int q = 0) :insertCount(c), deleteCount(d), changeCount(u), queryCount(q) {}
		int changeCount = 0, queryCount = 0, deleteCount = 0, insertCount = 0;
	};
	class Observer {
	public:
		virtual void Update(ObserverContext* context) = 0;

	public:
		virtual ~Observer() {}
	};

	class Subject {
	public:
		virtual void Attach(Observer* observer) {
			observers.push_back(observer);
		}
		virtual void Detach(Observer* observer) {
			observers.remove(observer);
		}
		virtual void Notify() {
			for (auto &ob : observers) {
				ob->Update(context);
			}
		}

		void setContext(ObserverContext *c) {
			context = c;
		}
		ObserverContext* getContext() const {
			return context;
		}
	public:
		virtual ~Subject() {}
	protected:
		ObserverContext *context;
		std::list<Observer*> observers;
	};
}