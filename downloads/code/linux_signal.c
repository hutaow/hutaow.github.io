#include <stdio.h>
#include <signal.h>

/* 信号处理函数 */
void sig_callback(int signum) {
    switch (signum) {
        case SIGINT:
            /* SIGINT: Ctrl+C 按下时触发 */
            printf("Get signal SIGINT. \r\n");
            break;
        /* 多个信号可以放到同一个函数中进行 通过信号值来区分 */
        default:
            /* 其它信号 */
            printf("Unknown signal %d. \r\n", signum);
            break;
    }

    return;
}

/* 主函数 */
int main(int argc, char *argv[]) {
    /* 注册SIGINT信号的处理函数 */
    signal(SIGINT, sig_callback);

    /* 阻塞在这里 等待信号触发 */
    do {
        sleep(1);
    } while (1);

    return 0;
}

