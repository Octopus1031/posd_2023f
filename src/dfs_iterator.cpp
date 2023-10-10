#include "./iterator.h"
#include "./node.h"
// #include "./folder.h"

BfsIterator::BfsIterator(Node * composite): _composite(composite) {}

DfsIterator::DfsIterator(Node * composite): _composite(composite) {}