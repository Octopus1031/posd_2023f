#include "./iterator.h"
#include "./node.h"
// #include "./folder.h"

DfsIterator::DfsIterator(Node * composite): _composite(composite) {}

BfsIterator::BfsIterator(Node * composite): _composite(composite) {}