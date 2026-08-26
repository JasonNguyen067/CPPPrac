Very interesting to see what happens in a queue fixed based array, can only go forward

Only time the memory allocation is truly reset for the forward spot is when the entire array is deleted (front -1, rear -1)

Array queue — you commit to the capacity upfront. int arr[5] reserves 20 bytes for the entire lifetime whether you're holding 0 elements or 5. Run out and you're stuck (that's your isFull()).
Linked-list queue — one node allocated per enqueue, freed per dequeue. Memory tracks actual usage, and there's no fixed capacity at all — you're bounded only by available heap.