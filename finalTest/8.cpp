root: 104
garbage: 100, 103


A
D

/*
When a non-garbage cell is copied from the old memory partition to the new memory partition, a forwarding address is left to indicate that the cell has been copied and to provide the address of the new location. all references to the old location will see the forwarding address and can then be updated as appropriate. if we don't record this forwarding address cyclical data structures will not be copied correctly: the garbage collector will repeatedly copy the same cell resulting in an infinite loop!
*/
