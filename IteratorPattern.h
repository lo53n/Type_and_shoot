#ifndef IteratorPattern
#define IteratorPattern


//Iterator interface
using namespace std;

template <class T>
class Iterator{
private:
	int index;
public:
	Iterator(){};
	virtual ~Iterator(){};

	virtual void first() = 0;
	virtual void next() = 0;
	virtual bool isDone() = 0;
	virtual T currentItem() = 0;
	virtual T getRest() = 0;
};
#endif //!IteratorPattern
