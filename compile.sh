if [ $# -ne 1 ]; then
    gcc -Wextra -Wall -O2 src/file_op.c src/sock_op.c src/sserver.c src/thread_op.c -o sserver
    gcc -Wextra -Wall -O2 src/file_op.c src/sock_op.c src/sclient.c src/thread_op.c -o sclient


elif [ "$1" == "s" ]; then
    clear
    gcc -Wextra -Wall -g src/file_op.c src/sock_op.c src/sserver.c src/thread_op.c -o sserver


elif [ "$1" == "c" ]; then
    clear
    gcc -Wextra -Wall -g src/file_op.c src/sock_op.c src/sclient.c src/thread_op.c -o sclient
fi 
