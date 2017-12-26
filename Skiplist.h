include <iostream>

template <typename KEY_T, typename DATA_T>
class SkipList {
	size_t MaxLevel;
	double SkipDivisor;
	struct Pair {
		KEY_T Key;
		DATA_T Data;
		Pair* Previous;
		Array<Pair*> Next;
		Pair(const KEY_T& InKey, const DATA_T& InData, Pair* InPrevious, size_t InLevel);
		Pair(size_t InLevel);
		~Pair();
		Pair& operator=(const Pair& InPair);
		Pair* PreviousOnLevel(size_t InLevel);
		Pair* NextOnLevel(size_t InLevel);
	};
	Pair Start;
	Pair* NewPrevious(const KEY_T& InKey);
	Pair* PairByKey(const KEY_T& InKey);
	size_t NewLevel();
public:
	class Iterator {
		SkipList* CurrentList;
		Pair* CurrentPair;
		friend class SkipList<KEY_T, DATA_T>;
	public:
		Iterator(const Iterator& InIterator);
		Iterator(SkipList& InSkipList);
		operator bool();
		Iterator& operator++();
		Iterator& operator--();
		Iterator operator++(int);
		Iterator operator--(int);
		Iterator& operator+=(size_t n);
		Iterator& operator-=(size_t n);
		Iterator& operator=(const Iterator& InIterator);
		Iterator& operator=(const KEY_T& InKey);
		DATA_T& operator*();
		void Delete();
	};
	SkipList(size_t InNumberOfLanes = 3, double InSkipDivisor = 1.0 / 4.0);
	~SkipList();
	Iterator GetBegin();
	Iterator GetEnd();
	void Add(const KEY_T& InKey, const DATA_T& InData);
	void Delete(const KEY_T& InKey);
	DATA_T& operator[](const KEY_T& InKey);
	size_t Count();
	void Clear();
	Iterator Find(const DATA_T& Unknown);
	bool IsEmpty();
};

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Pair* SkipList<KEY_T, DATA_T>::Pair::PreviousOnLevel(size_t InLevel) {
	if (!this)
		return NULL;
	Pair* Current = Previous;
	for (; Current && !(Current->Next.Count() >= InLevel + 1); Current = Current->Previous) {}
	return Current;
}

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Pair* SkipList<KEY_T, DATA_T>::Pair::NextOnLevel(size_t InLevel) {
	if (!this)
		return NULL;
	Pair* Current = Next[InLevel - 1];
	for (; Current && !(Current->Next.Count() >= InLevel + 1); Current = Current->Next[InLevel - 1]) {}
	return Current;
}

template <typename KEY_T, typename DATA_T>
SkipList<KEY_T, DATA_T>::Pair::Pair(const KEY_T& InKey, const DATA_T& InData, SkipList<KEY_T, DATA_T>::Pair* InPrevious, size_t InLevel) :Key(InKey), Data(InData), Previous(InPrevious) {
	Pair* Current = Previous->Next[0];
	Next.AddLast(Current);
	for (size_t Counter = 1; Counter <= InLevel; Counter++) {
		Current = NextOnLevel(Counter);
		Next.AddLast(Current);
	}
	Current = Previous;
	for (size_t Counter = 0; Counter <= InLevel; Counter++)
		if (Current = PreviousOnLevel(Counter))
			Current->Next[Counter] = this;
}

template <typename KEY_T, typename DATA_T>
SkipList<KEY_T, DATA_T>::Pair::Pair(size_t InLevel) : Previous(NULL) {
	for (size_t Counter = 0; Counter <= InLevel; Counter++)
		Next.AddLast(NULL);
}

template <typename KEY_T, typename DATA_T>
SkipList<KEY_T, DATA_T>::Pair::~Pair() {
	size_t OurLevel = Next.Count() - 1;
	Pair* Current = this;
	for (size_t Counter = 0; Counter <= OurLevel; Counter++)
		if (Current = PreviousOnLevel(Counter))
			Current->Next[Counter] = Next[Counter];
}

template <typename KEY_T, typename DATA_T>
SkipList<KEY_T, DATA_T>::SkipList(size_t InMaxLevel, double InSkipDivisor) :MaxLevel(InMaxLevel), SkipDivisor(InSkipDivisor), Start(MaxLevel) {}

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Pair& SkipList<KEY_T, DATA_T>::Pair::operator=(const SkipList<KEY_T, DATA_T>::Pair& InPair) {
	Key = InPair.Key;
	Data = InPair.Data;
	Previous = InPair.Previous;
	size_t max = Next.Count();
	for (size_t i; i<max; ++i)
		Next.AddLast(Next[i]);
	return *this;
}

template <typename KEY_T, typename DATA_T>
SkipList<KEY_T, DATA_T>::~SkipList() {
	Clear();
}

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Pair* SkipList<KEY_T, DATA_T>::NewPrevious(const KEY_T& InKey) {
	Pair* Previous = &Start;
	Pair* Current = Start.Next[MaxLevel];
	for (size_t Counter = MaxLevel; Counter >= 0; Counter--) {
		while (Current && InKey>Current->Key) {
			Previous = Current;
			Current = Current->Next[Counter];
		}
		if (!Counter)
			break;
		Current = Previous;
	};
	return Previous;
}

template <typename KEY_T, typename DATA_T>
size_t SkipList<KEY_T, DATA_T>::NewLevel() {
	size_t Level = 0;
	while (rand() % 1000<SkipDivisor * 1000 && Level <= MaxLevel)
		Level++;
	return Level;
}

template <typename KEY_T, typename DATA_T>
void SkipList<KEY_T, DATA_T>::Add(const KEY_T& InKey, const DATA_T& InData) {
	Pair* Previous = NewPrevious(InKey);
	Pair* Next = Previous->Next[0];
	if (Next && Next->Key == InKey)
		throw String("Not unique key!");
	new Pair(InKey, InData, Previous, NewLevel());
}

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Pair* SkipList<KEY_T, DATA_T>::PairByKey(const KEY_T& InKey) {
	Pair* Current = NewPrevious(InKey);
	if ((Current = Current->Next[0]) && Current->Key == InKey)
		return Current;
	throw String("No pair for this key!");
}

template <typename KEY_T, typename DATA_T>
void SkipList<KEY_T, DATA_T>::Delete(const KEY_T& InKey) {
	if (IsEmpty())
		throw String("There is empty list!");
	delete PairByKey(InKey);
}

template <typename KEY_T, typename DATA_T>
DATA_T& SkipList<KEY_T, DATA_T>::operator[](const KEY_T& InKey) {
	if (IsEmpty())
		throw String("List is empty!");
	return PairByKey(InKey)->Data;
}

template <typename KEY_T, typename DATA_T>
size_t SkipList<KEY_T, DATA_T>::Count() {
	if (IsEmpty())
		return 0;
	Pair* Next = Start.Next[0];
	size_t n = 1;
	while (Next = Next->Next[0])
		n++;
	return n;
}

template <typename KEY_T, typename DATA_T>
void SkipList<KEY_T, DATA_T>::Clear() {
	Pair* Current = Start.Next[1];
	Pair* Previous = NULL;
	while (Current) {
		Current->Previous = NULL;
		Previous = Current;
		Current = Current->Next[0];
		delete Previous;
	}
	for (size_t i = 0; i <= Start.Next.Count() - 1; i++)
		Start.Next[i] = NULL;
}

template <typename KEY_T, typename DATA_T>
SkipList<KEY_T, DATA_T>::Iterator::Iterator(const SkipList<KEY_T, DATA_T>::Iterator& InIterator) :CurrentList(InIterator.CurrentList), CurrentPair(InIterator.CurrentPair) {}

template <typename KEY_T, typename DATA_T>
SkipList<KEY_T, DATA_T>::Iterator::Iterator(SkipList<KEY_T, DATA_T>& InSkipList) : CurrentList(&InSkipList), CurrentPair(InSkipList.Start.Next[0]) {}

template <typename KEY_T, typename DATA_T>
SkipList<KEY_T, DATA_T>::Iterator::operator bool() {
	return CurrentList && CurrentPair;
}

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Iterator& SkipList<KEY_T, DATA_T>::Iterator::operator++() {
	if (CurrentPair)
		CurrentPair = CurrentPair->Next[0];
	return *this;
}

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Iterator& SkipList<KEY_T, DATA_T>::Iterator::operator--() {
	if (CurrentPair && CurrentPair != CurrentList->Start.Next[0])
		CurrentPair = CurrentPair->Previous;
	else
		CurrentPair = NULL;
	return *this;
}

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Iterator SkipList<KEY_T, DATA_T>::Iterator::operator++(int) {
	Iterator Old(*this);
	++*this;
	return Old;
}

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Iterator SkipList<KEY_T, DATA_T>::Iterator::operator--(int) {
	Iterator Old(*this);
	--*this;
	return Old;
}

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Iterator& SkipList<KEY_T, DATA_T>::Iterator::operator=(const SkipList<KEY_T, DATA_T>::Iterator& InIterator) {
	CurrentList = InIterator.CurrentList;
	CurrentPair = InIterator.CurrentPair;
	return *this;
}

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Iterator& SkipList<KEY_T, DATA_T>::Iterator::operator=(const KEY_T& InKey) {
	CurrentPair = CurrentList->PairByKey(InKey);
	return *this;
}

template <typename KEY_T, typename DATA_T>
DATA_T& SkipList<KEY_T, DATA_T>::Iterator::operator*() {
	if (!*this)
		throw String("Reading from bad iterator!");
	return CurrentPair->Data;
}

template <typename KEY_T, typename DATA_T>
void SkipList<KEY_T, DATA_T>::Iterator::Delete() {
	if (!*this)
		throw String("Deleting data of bad iterator!");
	delete CurrentPair;
	CurrentPair = NULL;
}

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Iterator& SkipList<KEY_T, DATA_T>::Iterator::operator+=(size_t n) {
	for (size_t Counter = 0; Counter<n && CurrentPair; Counter++)
		CurrentPair = CurrentPair->Next[0];
	return *this;
}

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Iterator& SkipList<KEY_T, DATA_T>::Iterator::operator-=(size_t n) {
	for (size_t Counter = 0; Counter<n && CurrentPair; Counter++)
		CurrentPair = CurrentPair->Previous;
	if (CurrentPair == &CurrentList->Start)
		return *this;
}

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Iterator SkipList<KEY_T, DATA_T>::GetBegin() {
	return Iterator(*this);
}

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Iterator SkipList<KEY_T, DATA_T>::GetEnd() {
	Iterator ReturnValue(*this);
	ReturnValue += ReturnValue.CurrentList->Count() - 1;
	return ReturnValue;
}

template <typename KEY_T, typename DATA_T>
typename SkipList<KEY_T, DATA_T>::Iterator SkipList<KEY_T, DATA_T>::Find(const DATA_T& Unknown) {
	Iterator Result(*this);
	while (Result && !(*Result == Unknown))
		++Result;
	return Result;
}

template <typename KEY_T, typename DATA_T>
bool SkipList<KEY_T, DATA_T>::IsEmpty() {
	typename Array<Pair*>::Iterator i(Start.Next);
	while (i)
		if (*i++)
			return false;
	return true;
}
