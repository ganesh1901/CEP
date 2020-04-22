// traces semaphores mutex etc 

valgrind --read-var-info=yes --track-origins=yes --leak-resolution=high --leak-check=full --show-reachable=yes ./a.out
