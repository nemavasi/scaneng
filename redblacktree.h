

typedef char * KeyType;
typedef int ValueType;

int size(); 

void put (KeyType key, ValueType value);
void printSorted();
void transfer(void (*fp)(int, char *));
